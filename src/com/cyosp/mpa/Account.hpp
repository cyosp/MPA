/*
 * Account.hpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_ACCOUNT_HPP_
#define INCLUDES_MPA_ACCOUNT_HPP_

#include "com/cyosp/mpa/Category.hpp"
#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/MPAPO.hpp"

namespace mpa
{

class Account
{
	public:
		static mpapo::Account & addAccount( string accountName );
		static bool delAccount( int id , int version );
		static bool isAccountAlreadyExisting( string accountName );
		static vector<mpapo::Account> getAccounts();
		static mpapo::Account getAccount( int id );
		static mpapo::Account renameAccount( int accountId , int accountVersionToRename , string newAccountName );

	virtual ~Account();
};

} /* namespace mpa */

#endif
