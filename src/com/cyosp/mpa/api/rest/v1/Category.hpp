/*
 * Category.hpp
 *
 *  Created on: 25 March 2015
 *      Author: cyosp
 */

#ifndef MPA_API_REST_V1_CATEGORY_HPP_
#define MPA_API_REST_V1_CATEGORY_HPP_

#include "com/cyosp/helpers/BoostHelper.hpp"
#include "com/cyosp/helpers/StrUtil.hpp"

#include "com/cyosp/mpa/core/Account.hpp"
#include "com/cyosp/mpa/core/Category.hpp"
#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"
#include "com/cyosp/mpa/po/MPAPO.hpp"
#include "com/cyosp/mpa/api/rest/v1/Account.hpp"


namespace mpa_api_rest_v1
{

class Category: public MPAO
{
	private:
		int accountId;

		bool isUrlPathValid();

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
	Category(HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals, vector<std::pair<string, int> > urlPairs );

	int getAccontId();

	virtual ~Category();
};

} /* namespace mpa */

#endif
