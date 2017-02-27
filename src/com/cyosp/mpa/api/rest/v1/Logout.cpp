/*
 * Logout.cpp
 *
 *  Created on: 2017-01-14
 *      Author: CYOSP
 */

#include <com/cyosp/mpa/api/rest/v1/Logout.hpp>

namespace mpa_api_rest_v1
{

Logout::Logout( HttpRequestType httpRequestType, ActionType actionType , const map<string, string>& argvals, vector<std::pair<string, int> > urlPairs ) : MPAO( httpRequestType, actionType, argvals, urlPairs )
{}

bool Logout::areGetParametersOk()
{
	bool ret = false;

	if( argvals.find( "token" ) != argvals.end() ) ret = true;

	return ret;
}

bool Logout::arePostAddParametersOk()
{
	return false;
}

string Logout::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	map<string, string> tokenList = MPAOFactory::getInstance()->getTokenList();
	map<string, string>::iterator tokenIt = tokenList.find( argvals.find("token")->second );
	if( tokenIt != tokenList.end() )
	{
		tokenList.erase( tokenIt );
		ret = "0";
	}

	return ret;
}

string Logout::executePostAddRequest(ptree & root)
{
	return MPAO::DEFAULT_JSON_ID;
}

string Logout::executePostDeleteRequest(ptree & root)
{
	return MPAO::DEFAULT_JSON_ID;
}

string Logout::executePostUpdateRequest(ptree & root)
{
	return MPAO::DEFAULT_JSON_ID;
}

Logout::~Logout()
{
}

} /* namespace mpa */
