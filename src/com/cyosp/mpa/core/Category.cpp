/*
 * Category.cpp
 *
 *  Created on: 25 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/core/Category.hpp>

namespace mpa
{
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

		mpa::Account::getAccount( accountId ).categories().link(category);
		MPA::getInstance()->getMPAPO().commit();

		categoryId = category.id;
	}

	return getCategory( categoryId );
}

// Get categories following an account identified by ID
vector<mpapo::Category> Category::getCategories( int accountId )
{
	return mpa::Account::getAccount( accountId ).categories().get().all();
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

			if( category.subOperations().get().all().size() > 0 ) throw mpa_exception::MsgNotTranslated( IMPOSSIBLE_REMOVE_THERE_ARE_AGAIN_OPERATIONS );

			MPA::getInstance()->getMPAPO().begin();
			mpa::Account::getAccount( accountId ).categories().unlink( category );
			category.del();
			MPA::getInstance()->getMPAPO().commit();
		}
		else throw mpa_exception::MsgNotTranslated( OPERATION_IMPOSSIBLE_BECAUSE_DATA_HAVE_CHANGED );
	}
	catch (NotFound & e)
	{
		throw mpa_exception::MsgNotTranslated( ACCOUNT_DOESNT_EXIST );
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
		else throw mpa_exception::MsgNotTranslated( OPERATION_IMPOSSIBLE_BECAUSE_DATA_HAVE_CHANGED );
	}
	catch (NotFound & e)
	{
		throw mpa_exception::MsgNotTranslated( ACCOUNT_DOESNT_EXIST );
	}
}

Category::~Category()
{
}

} /* namespace mpa */

