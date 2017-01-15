/*
 * Account.hpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_API_REST_V1_ACCOUNT_HPP_
#define INCLUDES_MPA_API_REST_V1_ACCOUNT_HPP_

#include "com/cyosp/mpa/Account.hpp"
#include "com/cyosp/mpa/Category.hpp"
#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"
#include "com/cyosp/mpa/po/MPAPO.hpp"


namespace mpa_api_rest_v1
{

class Account: public MPAO
{
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

	virtual ~Account();
};

} /* namespace mpa */

#endif
