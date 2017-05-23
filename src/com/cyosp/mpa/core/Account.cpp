/*
 * Account.cpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/core/Account.hpp>

namespace mpa
{

bool Account::isAccountAlreadyExisting( string accountName )
{
	bool ret = false;

	// TODO : try to use BDD facilities
	// Get accounts list
	vector<mpapo::Account> accounts = all();
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

mpapo::Account & Account::add( string accountName )
{
	mpapo::Account * ret = NULL;

	ret = new mpapo::Account( MPA::getInstance()->getMPAPO() );
	ret->setName( accountName );
	//sleep(6);
	ret->balance = 0;
	ret->initializeVersion();
	ret->update();

	MPA_LOG_TRIVIAL(trace,"Account added, id=" + (* ret).id.value());

	return * ret;
}

vector<mpapo::Account> Account::all()
{
	return select<mpapo::Account>( MPA::getInstance()->getMPAPO() ).all();	//.orderBy(mpapo::Account::Name).all();
}


bool Account::del(int id , int version )
{
	bool ret = false;

	MPA_LOG_TRIVIAL(trace,"Account to delete:" + StrUtil::int2string( id )+" with version: " + StrUtil::int2string(version ));

	try
	{
		mpapo::Account accountToDel = get( id );

		if( accountToDel.isCorrectVersion( version ) )
		{
			MPA_LOG_TRIVIAL(trace,"Account found");

			if( accountToDel.operations().get().all().size() > 0 ) throw mpa_exception::MsgNotTranslated( IMPOSSIBLE_REMOVE_THERE_ARE_AGAIN_OPERATIONS );
			if( accountToDel.providers().get().all().size() > 0 ) throw mpa_exception::MsgNotTranslated( IMPOSSIBLE_REMOVE_THERE_ARE_AGAIN_PROVIDERS );
			if( accountToDel.categories().get().all().size() > 0 ) throw mpa_exception::MsgNotTranslated( IMPOSSIBLE_REMOVE_THERE_ARE_AGAIN_CATEGORIES );

			accountToDel.del();
		}
		else throw mpa_exception::MsgNotTranslated( OPERATION_IMPOSSIBLE_BECAUSE_DATA_HAVE_CHANGED );
	}
	catch (NotFound & e)
	{
		throw mpa_exception::MsgNotTranslated( ACCOUNT_DOESNT_EXIST );
	}

	return ret;
}

// Get acount by ID
mpapo::Account Account::get( int id )
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
		mpapo::Account account = get( accountId );

		if( account.isCorrectVersion(  accountVersionToRename ) )
		{
			account.setName( newAccountName );
			account.update();

			//MPA_LOG_TRIVIAL( trace , "End" );

			// Return is here because there is no empty constructor for mpapo::Account::Account()
			return account;
		}
		else throw mpa_exception::MsgNotTranslated( OPERATION_IMPOSSIBLE_BECAUSE_DATA_HAVE_CHANGED );
	}
	catch (NotFound & e)
	{
		throw mpa_exception::MsgNotTranslated( ACCOUNT_DOESNT_EXIST );
	}
}

Account::~Account()
{
}

} /* namespace mpa */
