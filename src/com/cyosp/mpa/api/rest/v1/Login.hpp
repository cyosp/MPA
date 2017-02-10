/*
 * Login.hpp
 *
 *  Created on: 2017-01-04
 *      Author: CYOSP
 */

#ifndef INCLUDES_MPA_API_REST_V1_LOGIN_HPP_
#define INCLUDES_MPA_API_REST_V1_LOGIN_HPP_

#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"
#include "com/cyosp/rest/HTTPHandler.hpp"

namespace mpa_api_rest_v1
{

class Login: public MPAO
{

	protected:

		bool areGetParametersOk();
		bool arePostLoginParametersOk();
		bool arePostAddParametersOk();

		string executeGetRequest(ptree & root);
		string executePostLoginRequest(ptree & root);
		string executePostAddRequest(ptree & root);
		string executePostDeleteRequest(ptree & root);
		string executePostUpdateRequest(ptree & root);

	public:
		Login( HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals, vector<std::pair<string, int> > urlPairs );

	virtual ~Login();
};

} /* namespace mpa */

#endif
