/*
 * Operation.hpp
 *
 *  Created on: 18 April 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_OPERATION_HPP_
#define INCLUDES_MPA_OPERATION_HPP_

#include "com/cyosp/helpers/StrUtil.hpp"

#include "com/cyosp/mpa/Account.hpp"
#include "com/cyosp/mpa/Category.hpp"
#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/MPAO.hpp"
#include "com/cyosp/mpa/MPAPO.hpp"
#include "com/cyosp/mpa/Provider.hpp"

namespace mpa
{

class Operation: public MPAO
{
private:
	static vector<mpapo::Operation> getOperations( int accountId );

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

	static mpapo::Operation getOperation( int operationId );

	virtual ~Operation();
};

} /* namespace mpa */

#endif /* INCLUDES_MPA_OPERATION_HPP_ */
