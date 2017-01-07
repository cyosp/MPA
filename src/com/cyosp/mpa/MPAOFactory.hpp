/*
 * MPAOFactory.hpp
 *
 *  Created on: 21 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_MPAOFACTORY_HPP_
#define INCLUDES_MPA_MPAOFACTORY_HPP_

#include <boost/regex.hpp>

#include <map>
using std::map;

#include <string>
using std::string;

#include <vector>

#include "com/cyosp/mpa/Login.hpp"
#include "com/cyosp/mpa/Category.hpp"
#include "com/cyosp/mpa/Account.hpp"
#include "com/cyosp/mpa/Info.hpp"
#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/MPAO.hpp"
#include "com/cyosp/mpa/Operation.hpp"
#include "com/cyosp/mpa/Provider.hpp"
#include "com/cyosp/mpa/User.hpp"

namespace mpa
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

	static mpa::MPAO * getMPAO( HttpRequestType requestType, const string& url, const map<string, string>& argvals, bool isAdmin );
};

} /* namespace mpa */

#endif /* INCLUDES_MPA_MPAOFACTORY_HPP_ */
