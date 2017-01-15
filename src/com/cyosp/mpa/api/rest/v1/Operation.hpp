/*
 * Operation.hpp
 *
 *  Created on: 18 April 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_API_REST_V1_OPERATION_HPP_
#define INCLUDES_MPA_API_REST_V1_OPERATION_HPP_

#include "com/cyosp/helpers/StrUtil.hpp"

#include "com/cyosp/mpa/Account.hpp"
#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"
#include "com/cyosp/mpa/MPAPO.hpp"
#include "com/cyosp/mpa/Provider.hpp"
#include "com/cyosp/mpa/Operation.hpp"
#include "com/cyosp/mpa/Category.hpp"

namespace mpa_api_rest_v1
{

class Operation: public MPAO
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
	Operation(HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals , bool isAdmin, vector<std::pair<string, int> > urlPairs );

	virtual ~Operation();
};

} /* namespace mpa */

#endif
