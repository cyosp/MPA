/*
 * Account.cpp
 *
 *  Created on: 2017-01-04
 *      Author: CYOSP
 */

#include <com/cyosp/mpa/api/rest/v1/Login.hpp>

namespace mpa_api_rest_v1
{

Login::Login( HttpRequestType httpRequestType, ActionType actionType , const map<string, string>& argvals, bool isAdmin, vector<std::pair<string, int> > urlPairs ) : MPAO( httpRequestType, actionType, argvals, isAdmin, urlPairs )
{}

bool Login::areGetParametersOk()
{
	return false;
}

bool Login::arePostLoginParametersOk()
{
	bool ret = false;

	if(			argvals.find("login") != argvals.end()
			&&	argvals.find("pwd") != argvals.end() ) ret = true;

	return ret;
}

bool Login::arePostAddParametersOk()
{
	return false;
}


string Login::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	return ret;
}

string Login::executePostLoginRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	string login = argvals.find("login")->second;
	string pwd   = argvals.find("pwd")->second;

	// There is an administrator user defined
	if( MPA::getInstance()->isAdminRegistered() )
	{
		try
		{
			mpapo::User user = MPA::getInstance()->getUser( login );
			if( user.pwdErrNbr < MPA::PWD_SECURITY_ERROR_NBR )
			{
				if( user.password.value().compare( pwd ) == 0 )
				{
					// Reset password error because password used is correct
					if( user.pwdErrNbr != 0 )
					{
						user.resetPwdErr();
						user.update();
					}
					MPA_LOG_TRIVIAL(info,"User is authenticated");
					ret = HTTPHandler::registerNewSession( user.isAdmin );
				}
				else
				{
					// TODO : Message for fail2ban or same program using remote IP
					MPA_LOG_TRIVIAL(info,"Account: " + user.login + " has password failed" );

					// Register this password error
					user.addPwdErr();
					user.update();

					ret = MPA::getErrMsg( 7 );
				}
			}
			else
			{
				// TODO : Message for fail2ban or same program using remote IP
				MPA_LOG_TRIVIAL(error,"Account: " + user.login + " blocked" );

				ret = MPA::getErrMsg( 11 );
			}
		}
		catch (NotFound & e)
		{
			MPA_LOG_TRIVIAL(trace,"User authentication fails due to login error");

			ret = MPA::getErrMsg( 6 );
		}
	}
	else
	{
		MPA_LOG_TRIVIAL(trace, "Administrator account is not defined" );

		ret = MPA::getErrMsg( MSG_NO_SYSTEM_ACCOUNT );
	}

	return ret;
}

string Login::executePostAddRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	return ret;
}

string Login::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	return ret;
}

string Login::executePostUpdateRequest(ptree & root)
{
	//MPA_LOG_TRIVIAL( trace , "Start" );

	string ret = MPAO::DEFAULT_JSON_ID;

	return ret;
}

Login::~Login()
{
}

} /* namespace mpa */
