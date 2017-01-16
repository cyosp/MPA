/*
 * Logout.hpp
 *
 *  Created on: 2017-01-14
 *      Author: CYOSP
 */

#ifndef INCLUDES_MPA_API_REST_V1_LOGOUT_HPP_
#define INCLUDES_MPA_API_REST_V1_LOGOUT_HPP_

#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"
#include "com/cyosp/rest/HTTPHandler.hpp"

using namespace mpa;

namespace mpa_api_rest_v1
{

class Logout: public MPAO
{

	protected:

		bool areGetParametersOk();
		bool arePostLogoutParametersOk();
		bool arePostAddParametersOk();

		string executeGetRequest(ptree & root);
		string executePostLogoutRequest(ptree & root);
		string executePostAddRequest(ptree & root);
		string executePostDeleteRequest(ptree & root);
		string executePostUpdateRequest(ptree & root);

	public:
		Logout( HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals, bool isAdmin, vector<std::pair<string, int> > urlPairs );

	virtual ~Logout();
};

} /* namespace mpa */

#endif
