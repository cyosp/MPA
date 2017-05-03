/*
 * Operation.hpp
 *
 *  Created on: 18 April 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_API_REST_V1_OPERATION_HPP_
#define INCLUDES_MPA_API_REST_V1_OPERATION_HPP_

#include "com/cyosp/helpers/BoostHelper.hpp"
#include "com/cyosp/helpers/StrUtil.hpp"

#include "com/cyosp/mpa/core/Account.hpp"
#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"
#include "com/cyosp/mpa/po/MPAPO.hpp"
#include "com/cyosp/mpa/core/Provider.hpp"
#include "com/cyosp/mpa/core/Operation.hpp"
#include "com/cyosp/mpa/core/Category.hpp"
#include "com/cyosp/mpa/api/rest/v1/Account.hpp"

namespace mpa_api_rest_v1
{

class Operation: public MPAO
{
	private:
		int accountId;

		bool isUrlPathValid();

	public:
		static string URL_STRING_PATH_IDENTIFIER;

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
		Operation(HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals, vector<std::pair<string, int> > urlPairs );

		int getAccountId();

		virtual ~Operation();
};

} /* namespace mpa */

#endif
