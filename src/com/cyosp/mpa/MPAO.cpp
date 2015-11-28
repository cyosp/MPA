/*
 * MPAO.cpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/MPAO.hpp>

namespace mpa
{

string MPAO::DEFAULT_JSON_ID = "-1";

MPAO::MPAO( HttpRequestType httpRequestType , ActionType actionType, const map<string, string>& argvals, bool isAdmin, vector<std::pair<string, int> > urlPairs)
{
	this->httpRequestType = httpRequestType;
	this->actionType = actionType;
	this->argvals = argvals;
	this->isAdmin = isAdmin;
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

string MPAO::executeRequest(ptree & root)
{
	string ret = "";

	if( httpRequestType == GET ) ret = executeGetRequest( root );
	else
	{
		switch (actionType)
		{
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
