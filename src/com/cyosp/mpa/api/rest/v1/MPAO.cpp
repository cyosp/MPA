/*
 * MPAO.cpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/api/rest/v1/MPAO.hpp>

namespace mpa_api_rest_v1
{

string MPAO::DEFAULT_JSON_ID = "-1";

MPAO::MPAO( HttpRequestType httpRequestType , ActionType actionType, const map<string, string>& argvals, vector<std::pair<string, int> > urlPairs)
{
	this->httpRequestType = httpRequestType;
	this->actionType = actionType;
	this->argvals = argvals;
	this->urlPairs = urlPairs;
}

bool MPAO::areParametersOk()
{
	bool ret = false;

	if( httpRequestType == GET ) ret = areGetParametersOk();
	else
	{
		switch (actionType)
		{
			case NONE:
				ret = false;
				break;
			case LOGIN:
				ret = arePostLoginParametersOk();
				break;
			case ADD:
				ret = arePostAddParametersOk();
				break;
			case DELETE:
				ret = arePostDeleteParametersOk();
				break;
			case UPDATE:
				ret = arePostUpdateParametersOk();
				break;
		}
	}

	return ret;
}

bool MPAO::arePostLoginParametersOk()
{
	return false;
}

bool MPAO::arePostDeleteParametersOk()
{
	bool ret = false;


	if( argvals.find("version") != argvals.end() ) ret = true;

	return ret;
}

bool MPAO::arePostUpdateParametersOk()
{
	bool ret = false;


	if( argvals.find("version") != argvals.end() ) ret = true;

	return ret;
}

string MPAO::executePostLoginRequest(ptree & root)
{
	return MPAO::DEFAULT_JSON_ID;
}

string MPAO::executeRequest(ptree & root)
{
	string ret = "";

	if( httpRequestType == GET ) ret = executeGetRequest( root );
	else
	{
		switch (actionType)
		{
			case NONE:
				ret = "";
				break;
			case LOGIN:
				MPA_LOG_TRIVIAL(trace," Execute post login request");
				ret = executePostLoginRequest( root );
				break;
			case ADD:
				MPA_LOG_TRIVIAL(trace," Execute post add request");
				ret = executePostAddRequest( root );
				break;
			case DELETE:
				MPA_LOG_TRIVIAL(trace," Execute post delete request");
				ret = executePostDeleteRequest( root );
				break;
			case UPDATE:
				MPA_LOG_TRIVIAL(trace," Execute post update request");
				ret = executePostUpdateRequest( root );
				break;
		}
	}

	return ret;
}

MPAO::~MPAO()
{
}

} /* namespace mpa */
