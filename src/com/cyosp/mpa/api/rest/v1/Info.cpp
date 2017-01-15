/*
 * Info.cpp
 *
 *  Created on: 27 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/api/rest/v1/Info.hpp>

namespace mpa_api_rest_v1
{

Info::Info(HttpRequestType httpRequestType, ActionType actionType,
		const map<string, string>& argvals, bool isAdmin,
		vector<std::pair<string, int> > urlPairs) :
		MPAO(httpRequestType, actionType, argvals, isAdmin, urlPairs)
{}


bool Info::areGetParametersOk()
{
	bool ret = true;
	return ret;
}

bool Info::arePostAddParametersOk()
{
	bool ret = false;

	return ret;
}

bool Info::arePostDeleteParametersOk()
{
	bool ret = false;

	return ret;
}

bool Info::arePostUpdateParametersOk()
{
	bool ret = false;

	return ret;
}

string Info::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	if( urlPairs.size() == 1 )
	{
		ptree versionPtree;
		versionPtree.put("version", MPA::version);
		root.push_back(std::make_pair("infos", versionPtree));
	}

	return ret;
}

string Info::executePostAddRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	return ret;
}

string Info::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	return ret;
}

string Info::executePostUpdateRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	return ret;
}


bool Info::isObjectAlreadyExisting( string objectName )
{
	bool ret = false;

	return ret;
}

Info::~Info()
{
}

} /* namespace mpa */
