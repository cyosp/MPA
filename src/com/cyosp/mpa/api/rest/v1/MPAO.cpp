/*
 * MPAO.cpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/api/rest/v1/MPAO.hpp>

#include "com/cyosp/mpa/api/rest/v1/MPAOFactory.hpp"

namespace mpa_api_rest_v1
{

string MPAO::DEFAULT_JSON_ID = "-1";
string MPAO::OK_JSON_ID		 = "0";

MPAO::MPAO( HttpRequestType httpRequestType , ActionType actionType, const map<string, string>& argvals, vector<std::pair<string, int> > urlPairs)
{
	this->httpRequestType = httpRequestType;
	this->actionType = actionType;
	this->argvals = argvals;
	this->urlPairs = urlPairs;
	restrictedAccess = true;
	badParamsMsg = "";
	login = "";
}

bool MPAO::isValidAccess()
{
	bool ret = false;

	MPA_LOG_TRIVIAL( info , "Start MPAO::isValidAccess" );

	if( restrictedAccess )
	{
		map<string, string>::iterator tokenIt = argvals.find( "token" );
		// Check in request parameters there is a token parameter
		if( tokenIt != argvals.end() )
		{
			// Get token value
			string token = tokenIt->second;

			map<string, string>::iterator it = MPAOFactory::getInstance()->getTokenList().find( token );

			// Check token value is registered
			if( it != MPAOFactory::getInstance()->getTokenList().end() )
			{
				// Update login member value
				login = it->second;
				ret = true;
			}
			else badParamsMsg = MPA::getInstance()->getResourceBundle().translate( "Invalid token" , MPA::DEFAULT_LOCALE );
		}
		else badParamsMsg = MPA::getInstance()->getResourceBundle().translate( "Token argument no found" , MPA::DEFAULT_LOCALE );
	}
	else ret = true;

	MPA_LOG_TRIVIAL( info , "End MPAO::isValidAccess: " + StrUtil::bool2string( ret ) );

	return ret;
}

bool MPAO::areParametersOk()
{
	bool ret = false;

	if( httpRequestType == GET )
	{
		MPA_LOG_TRIVIAL(trace," Execute check get parameters");
		ret = isValidAccess() && areGetParametersOk();
	}
	else
	{
		switch (actionType)
		{
			case NONE:
				ret = false;
				break;
			case LOGIN:
				MPA_LOG_TRIVIAL(trace," Execute check post login parameters");
				ret = isValidAccess() && arePostLoginParametersOk();
				break;
			case ADD:
				MPA_LOG_TRIVIAL(trace," Execute check post add parameters");
				ret = isValidAccess() && arePostAddParametersOk();
				break;
			case DELETE:
				MPA_LOG_TRIVIAL(trace," Execute check post delete parameters");
				ret = isValidAccess() && arePostDeleteParametersOk();
				break;
			case UPDATE:
				MPA_LOG_TRIVIAL(trace," Execute check post update parameters");
				ret = isValidAccess() && arePostUpdateParametersOk();
				break;
		}
	}

	return ret;
}

string MPAO::getBadParamsMsg()
{
	return badParamsMsg;
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
	MPA_LOG_TRIVIAL(trace," MPAO::executeRequest");

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

string & MPAO::getLogin()
{
	return login;
}

MPAO::~MPAO()
{
}

} /* namespace mpa */
