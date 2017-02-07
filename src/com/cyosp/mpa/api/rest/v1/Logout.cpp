/*
 * Logout.cpp
 *
 *  Created on: 2017-01-14
 *      Author: CYOSP
 */

#include <com/cyosp/mpa/api/rest/v1/Logout.hpp>

namespace mpa_api_rest_v1
{

Logout::Logout( HttpRequestType httpRequestType, ActionType actionType , const map<string, string>& argvals, bool isAdmin, vector<std::pair<string, int> > urlPairs ) : MPAO( httpRequestType, actionType, argvals, isAdmin, urlPairs )
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

	/*if( tokenList->find( token ) != tokenList->end() )
		{
			tokenList->erase( tokenList->find( token ) );

			ret = true;
		}*/

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
