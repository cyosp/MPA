/*
 * Login.hpp
 *
 *  Created on: 2017-01-04
 *      Author: CYOSP
 */

#ifndef INCLUDES_MPA_LOGIN_HPP_
#define INCLUDES_MPA_LOGIN_HPP_

#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/MPAO.hpp"
#include "com/cyosp/rest/HTTPHandler.hpp"

namespace mpa
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
		Login( HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals, bool isAdmin, vector<std::pair<string, int> > urlPairs );

	virtual ~Login();
};

} /* namespace mpa */

#endif /* INCLUDES_MPA_LOGIN_HPP_ */
