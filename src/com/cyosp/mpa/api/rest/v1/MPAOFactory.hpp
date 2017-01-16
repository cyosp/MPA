/*
 * MPAOFactory.hpp
 *
 *  Created on: 21 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_API_REST_V1_MPAOFACTORY_HPP_
#define INCLUDES_MPA_API_REST_V1_MPAOFACTORY_HPP_

#include <boost/regex.hpp>

#include <map>
using std::map;

#include <string>
using std::string;

#include <vector>

#include "com/cyosp/mpa/api/rest/v1/Login.hpp"
#include "com/cyosp/mpa/api/rest/v1/Category.hpp"
#include "com/cyosp/mpa/api/rest/v1/Account.hpp"
#include "com/cyosp/mpa/api/rest/v1/Info.hpp"
#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"
#include "com/cyosp/mpa/api/rest/v1/Operation.hpp"
#include "com/cyosp/mpa/api/rest/v1/Provider.hpp"
#include "com/cyosp/mpa/api/rest/v1/User.hpp"

namespace mpa_api_rest_v1
{

class MPAOFactory
{
private:

	// Singleton member
	static MPAOFactory * mpaofactory;
	MPAOFactory();

public:

	// Singleton method
	static MPAOFactory * getInstance();

	static mpa_api_rest_v1::MPAO * getMPAO( HttpRequestType requestType, const string& url, const map<string, string>& argvals, bool isAdmin );
};

} /* namespace mpa */

#endif
