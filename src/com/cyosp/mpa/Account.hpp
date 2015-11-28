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
#include "com/cyosp/mpa/MPAO.hpp"
#include "com/cyosp/mpa/MPAPO.hpp"

namespace mpa
{

class Account: public MPAO
{
	private:
		mpapo::Account & addAccount( string accountName );
		bool delAccount( int id , int version );

	protected:

		bool areGetParametersOk();
		bool arePostAddParametersOk();
		bool arePostDeleteParametersOk();
		bool arePostUpdateParametersOk();

		string executeGetRequest(ptree & root);
		string executePostAddRequest(ptree & root);
		string executePostDeleteRequest(ptree & root);
		string executePostUpdateRequest(ptree & root);

	public:
		Account( HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals, bool isAdmin, vector<std::pair<string, int> > urlPairs );

		static bool isAccountAlreadyExisting( string accountName );
		static vector<mpapo::Account> getAccounts();
		static mpapo::Account getAccount( int id );
		static mpapo::Account renameAccount( int accountId , int accountVersionToRename , string newAccountName );

	virtual ~Account();
};

} /* namespace mpa */

#endif /* INCLUDES_MPA_ACCOUNT_HPP_ */
