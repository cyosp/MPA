/*
 * Info.hpp
 *
 *  Created on: 27 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_INFO_HPP_
#define INCLUDES_MPA_INFO_HPP_

#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/MPAO.hpp"

namespace mpa
{

class Info: public MPAO
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
	Info( HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals , bool isAdmin, vector<std::pair<string, int> > urlPairs );

	virtual ~Info();
};

} /* namespace mpa */

#endif /* INCLUDES_MPA_INFO_HPP_ */
