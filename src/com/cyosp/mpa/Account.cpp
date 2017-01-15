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

} /* namespace mpapo */


namespace mpa
{

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
