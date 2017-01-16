/*
 * User.hpp
 *
 *  Created on: 21 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_API_REST_V1_USER_HPP_
#define INCLUDES_MPA_API_REST_V1_USER_HPP_

#include "com/cyosp/mpa/api/rest/v1/Account.hpp"
#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"

namespace mpa_api_rest_v1
{

class User : public MPAO
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


	bool isObjectAlreadyExisting( string objectName );

public:
	User( HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals , bool isAdmin, vector<std::pair<string, int> > urlPairs );

	virtual ~User();
};

} /* namespace mpa */

#endif
