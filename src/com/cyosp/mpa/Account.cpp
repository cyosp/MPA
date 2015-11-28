/*
 * Account.cpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/Account.hpp>

namespace mpapo
{

// Check if an account exist with the same name before to set the account name
// methode update() must be called manually after this method
void Account::setName( string name )
{
	bool find = mpa::Account::isAccountAlreadyExisting( name );

	//MPA_LOG_TRIVIAL(trace,"setName1");
	//usleep( 10000000 );
	//MPA_LOG_TRIVIAL(trace,"setName2");

	if (!find)	this->name = name;
	else	throw MPA::getErrMsg( 1 );
}

void Account::addToBalance( float balance )
{
	this->balance = this->balance + balance;
}

}

namespace mpa
{

Account::Account( HttpRequestType httpRequestType, ActionType actionType , const map<string, string>& argvals, bool isAdmin, vector<std::pair<string, int> > urlPairs ) : MPAO( httpRequestType, actionType, argvals, isAdmin, urlPairs )
{}

bool Account::areGetParametersOk()
{
	bool ret = true;
	return ret;
}

bool Account::arePostAddParametersOk()
{
	bool ret = false;

	if( argvals.find("name") != argvals.end() ) ret = true;

	return ret;
}

bool Account::arePostDeleteParametersOk()
{
	bool ret = MPAO::arePostDeleteParametersOk();

	return ret;
}

bool Account::arePostUpdateParametersOk()
{
	bool ret = MPAO::arePostUpdateParametersOk();

	if( ret )
	{
		if (argvals.find("name") != argvals.end() ) ret = true;
	}

	return ret;
}

string Account::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	//MPA_LOG_TRIVIAL(trace, "" );

	ptree accountsChildren;

	vector<mpapo::Account> accounts = getAccounts();
	for (vector<mpapo::Account>::iterator it = accounts.begin(); it != accounts.end(); it++)
	{
		ptree accountPtree;
		accountPtree.put("id", (*it).id);
		accountPtree.put("version", (*it).version);
		accountPtree.put("name", (*it).name);
		accountPtree.put("balance", StrUtil::float2string((*it).balance));

		accountsChildren.push_back(std::make_pair("", accountPtree));
	}

	root.add_child("accounts", accountsChildren);

	return ret;
}

string Account::executePostAddRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	MPA_LOG_TRIVIAL(trace,"Account name to add: " + argvals.find("name")->second );

	mpapo::Account account( MPA::getInstance()->getMPAPO() );
	account = addAccount( argvals.find("name")->second );

	// Get account ID
	ret = string( account.id );

	MPA_LOG_TRIVIAL(trace,"Account ID added: " + ret);

	// Generate Json output
	root.push_back(make_pair("version", account.version ));
	root.push_back(make_pair("balance", account.balance ));

	return ret;
}

string Account::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	delAccount( urlPairs[0].second , atoi( argvals.find("version")->second ) );

	return ret;
}

string Account::executePostUpdateRequest(ptree & root)
{
	//MPA_LOG_TRIVIAL( trace , "Start" );

	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	int accountVersion = atoi( argvals.find("version")->second );
	string accountNewName = argvals.find("name")->second;

	mpapo::Account account = renameAccount( accountId , accountVersion , accountNewName );
	ret = StrUtil::int2string( accountId );

	// Generate Json output
	root.push_back(make_pair("version", StrUtil::int2string( account.version ) ));

	//MPA_LOG_TRIVIAL( trace , "End" );

	return ret;
}

bool Account::isAccountAlreadyExisting( string accountName )
{
	bool ret = false;

	// TODO : try to use BDD facilities
	// Get accounts list
	vector<mpapo::Account> accounts = getAccounts();
	// Get accounts iterator
	vector<mpapo::Account>::iterator it = accounts.begin();

	while (it != accounts.end() && ! ret )
	{
		if ((*it).name == accountName)
			ret = true;
		else
			it++;
	}

	return ret;
}

mpapo::Account & Account::addAccount( string accountName )
{
	mpapo::Account * ret = NULL;

	// TODO : One insertion at time
	// Perform a lock

	//getMPAPO().begin();
	ret = new mpapo::Account( MPA::getInstance()->getMPAPO() );
	ret->initializeVersion();
	ret->setName( accountName );
	//sleep(6);
	ret->balance = 0;
	ret->update();
	//getMPAPO().commit();

	MPA_LOG_TRIVIAL(trace,"Account added, id=" + (* ret).id.value());

	return * ret;
}

vector<mpapo::Account> Account::getAccounts()
{
	return select<mpapo::Account>( MPA::getInstance()->getMPAPO() ).all();	//.orderBy(mpapo::Account::Name).all();
}


bool Account::delAccount(int id , int version )
{
	bool ret = false;

	MPA_LOG_TRIVIAL(trace,"Account to delete:" + StrUtil::int2string( id )+" with version: " + StrUtil::int2string(version ));

	try
	{
		mpapo::Account accountToDel = getAccount( id );

		if( accountToDel.isCorrectVersion( version ) )
		{
			MPA_LOG_TRIVIAL(trace,"Account found");

			if( accountToDel.operations().get().all().size() > 0 ) throw MPA::getErrMsg( MSG_DEL_IMPOSSIBLE_OPERATIONS );
			if( accountToDel.providers().get().all().size() > 0 ) throw MPA::getErrMsg( MSG_DEL_IMPOSSIBLE_PROVIDERS );
			if( accountToDel.categories().get().all().size() > 0 ) throw MPA::getErrMsg( MSG_DEL_IMPOSSIBLE_CATEGORIES );

			MPA::getInstance()->getMPAPO().begin();
			accountToDel.del();
			MPA::getInstance()->getMPAPO().commit();
		}
		else throw MPA::getErrMsg( 4 );
	}
	catch (NotFound & e)
	{
		throw MPA::getErrMsg( 2 );
	}

	return ret;
}

// Get acount by ID
mpapo::Account Account::getAccount( int id )
{
	// BOOST_LOG_TRIVIAL(trace) << "Account retrieved" << std::endl;
	return select<mpapo::Account>( MPA::getInstance()->getMPAPO() , mpapo::Account::Id == id ).one();
}

// Rename account
mpapo::Account Account::renameAccount( int accountId , int accountVersionToRename , string newAccountName )
{
	//MPA_LOG_TRIVIAL( trace , "Start" );

	try
	{
		mpapo::Account account = getAccount( accountId );

		if( account.isCorrectVersion(  accountVersionToRename ) )
		{
			account.setName( newAccountName );
			account.updateVersion();
			account.update();

			//MPA_LOG_TRIVIAL( trace , "End" );

			// Return is here because there is no empty constructor for mpapo::Account::Account()
			return account;
		}
		else throw MPA::getErrMsg( 4 );
	}
	catch (NotFound & e)
	{
		throw MPA::getErrMsg( 2 );
	}
}

Account::~Account()
{
}

} /* namespace mpa */
