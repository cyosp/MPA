/*
 * User.hpp
 *
 *  Created on: 21 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_USER_HPP_
#define INCLUDES_MPA_USER_HPP_

#include "com/cyosp/mpa/Account.hpp"
#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/MPAO.hpp"

namespace mpa_api_rest_v1
{

class User : public mpa::MPAO
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

#endif /* INCLUDES_MPA_USER_HPP_ */
