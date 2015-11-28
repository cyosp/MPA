/*
 * Category.cpp
 *
 *  Created on: 25 March 2015
 *      Author: cyosp
 */

#include "com/cyosp/mpa/Category.hpp"

namespace mpapo
{

// Check if a category exists with the same name before to set the category name
// methode update() must be called manually after this method
void Category::setName( int accountId, string name )
{
	int categoryId = mpa::Category::getCategoryId( accountId, name );

	//MPA_LOG_TRIVIAL(trace,"setName1");
	//usleep( 10000000 );
	//MPA_LOG_TRIVIAL(trace,"setName2");

	if (categoryId == 0)	this->name = name;
	else	throw MPA::getErrMsg( 20 );
}

void Category::setAmount( float amount )
{
	this->amount = amount;
}

void Category::addToAmount( float amount )
{
	this->amount = this->amount + amount;
}

}

namespace mpa
{

Category::Category(HttpRequestType httpRequestType, ActionType actionType,
		const map<string, string>& argvals, bool isAdmin,
		vector<std::pair<string, int> > urlPairs) :
		MPAO(httpRequestType, actionType, argvals, isAdmin, urlPairs)
{}

bool Category::areGetParametersOk()
{
	bool ret = true;
	return ret;
}

bool Category::arePostAddParametersOk()
{
	bool ret = false;

	if( argvals.find("name") != argvals.end() ) ret = true;

	return ret;
}

bool Category::arePostDeleteParametersOk()
{
	bool ret = MPAO::arePostDeleteParametersOk();

	return ret;
}

bool Category::arePostUpdateParametersOk()
{
	bool ret = MPAO::arePostUpdateParametersOk();

	if( ret )
	{
		if (argvals.find("name") != argvals.end() ) ret = true;
	}

	return ret;
}

string Category::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	//MPA_LOG_TRIVIAL(trace, "" );

	int accountId = urlPairs[0].second;

	ptree categoriesChildren;

	vector<mpapo::Category> accounts = getCategories( accountId );
	for (vector<mpapo::Category>::iterator it = accounts.begin(); it != accounts.end(); it++)
	{
		ptree categoryPtree;
		categoryPtree.put("id", (*it).id);
		categoryPtree.put("version", (*it).version);
		categoryPtree.put("name", (*it).name);
		categoryPtree.put("amount", StrUtil::float2string((*it).amount));

		categoriesChildren.push_back(std::make_pair("", categoryPtree));
	}

	root.add_child("categories", categoriesChildren);

	return ret;
}

string Category::executePostAddRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	string categoryName = argvals.find("name")->second;

	//MPA_LOG_TRIVIAL(trace,"");

	mpapo::Category category = getCategory( accountId , categoryName );

	//MPA_LOG_TRIVIAL(trace,"");

	// Get account ID
	ret = string( category.id );

	MPA_LOG_TRIVIAL(trace,"Category ID added: " + ret);

	// Generate Json output
	root.push_back(make_pair("version", category.version ));
	root.push_back(make_pair("amount", category.amount ));

	return ret;
}

string Category::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	int categoryId = urlPairs[1].second;
	int categoryVersion = atoi( argvals.find("version")->second );

	remove( accountId , categoryId , categoryVersion );

	return ret;
}

string Category::executePostUpdateRequest(ptree & root)
{
	//MPA_LOG_TRIVIAL( trace , "Start" );

	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	int categoryId = urlPairs[1].second;
	int categoryVersion = atoi( argvals.find("version")->second );
	string categoryNewName = argvals.find("name")->second;

	mpapo::Category category = rename( accountId , categoryId , categoryVersion , categoryNewName );
	ret = StrUtil::int2string( categoryId );

	// Generate Json output
	root.push_back(make_pair("version", StrUtil::int2string( category.version ) ));

	//MPA_LOG_TRIVIAL( trace , "End" );

	return ret;
}


// Return 0 if doesn't exist, Category ID otherwise
int Category::getCategoryId( int accountId , string categoryName )
{
	int ret = 0;

	vector<mpapo::Category> categories = getCategories( accountId );
	// Get categories iterator
	vector<mpapo::Category>::iterator it = categories.begin();

	while (it != categories.end() && ! ret )
	{
		mpapo::Category category = (*it);

		if (category.name == categoryName)
			ret = category.id;
		else
			it++;
	}

	return ret;
}

// Get category in all case
// Create one if no existing
mpapo::Category Category::getCategory( int accountId , string categoryName )
{
	// Get category Id
	int categoryId = getCategoryId( accountId , categoryName);

	// Create it if it doesn't exist
	if( categoryId == 0 )
	{
		MPA::getInstance()->getMPAPO().begin();
		mpapo::Category category( MPA::getInstance()->getMPAPO() );
		category.initializeVersion();
		category.setName( accountId , categoryName);
		category.setAmount( 0 );
		category.update();

		Account::getAccount( accountId ).categories().link(category);
		MPA::getInstance()->getMPAPO().commit();

		categoryId = category.id;
	}

	return getCategory( categoryId );
}

// Get categories following an account identified by ID
vector<mpapo::Category> Category::getCategories( int accountId )
{
	return Account::getAccount( accountId ).categories().get().all();
}

mpapo::Category Category::getCategory( int categoryId )
{
	return select<mpapo::Category>( MPA::getInstance()->getMPAPO() , mpapo::Category::Id == categoryId ).one();
}

void Category::remove( int accountId , int categoryId , int version )
{
	try
	{
		mpapo::Category category = Category::getCategory( categoryId );

		if( category.isCorrectVersion( version ) )
		{
			//MPA_LOG_TRIVIAL(trace,"Not found");

			if( category.subOperations().get().all().size() > 0 ) throw MPA::getErrMsg( MSG_DEL_IMPOSSIBLE_OPERATIONS );

			MPA::getInstance()->getMPAPO().begin();
			Account::getAccount( accountId ).categories().unlink( category );
			category.del();
			MPA::getInstance()->getMPAPO().commit();
		}
		else throw MPA::getErrMsg( 4 );
	}
	catch (NotFound & e)
	{
		throw MPA::getErrMsg( 2 );
	}
}

// Rename category
mpapo::Category Category::rename( int accountId , int categoryId, int categoryVersion , string newName )
{
	//MPA_LOG_TRIVIAL( trace , "Start" );

	try
	{
		mpapo::Category category = getCategory( categoryId );

		if( category.isCorrectVersion(  categoryVersion ) )
		{
			category.setName( accountId , newName );
			category.updateVersion();
			category.update();

			//MPA_LOG_TRIVIAL( trace , "End" );

			// Return is here because there is no empty constructor for mpapo::Category::Category()
			return category;
		}
		else throw MPA::getErrMsg( 4 );
	}
	catch (NotFound & e)
	{
		throw MPA::getErrMsg( 2 );
	}
}

Category::~Category()
{
}

} /* namespace mpa */
