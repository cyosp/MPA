/*
 * User.cpp
 *
 *  Created on: 21 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/api/rest/v1/User.hpp>

namespace mpa_api_rest_v1
{

User::User( HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals, vector<std::pair<string, int> > urlPairs ) : MPAO( httpRequestType, actionType, argvals, urlPairs )
{}

bool User::isValidAccess()
{
	MPA_LOG_TRIVIAL( info , "Start MPAO::isValidAccess" );
	bool ret =  MPAO::isValidAccess() || ! MPA::getInstance()->isAdminRegistered();
	MPA_LOG_TRIVIAL( info , "End MPAO::isValidAccess: " + StrUtil::bool2string(ret) );

	return ret;
}

bool User::areGetParametersOk()
{
	bool ret = true;
	return ret;
}

bool User::arePostAddParametersOk()
{
	bool ret = false;

	MPA_LOG_TRIVIAL(trace, "isAdminRegistered " + StrUtil::bool2string( MPA::getInstance()->isAdminRegistered() ) );

	//
	// There is no user defined as long as administrator account is not registered
	//
	string locale = MPA::DEFAULT_LOCALE;
	if( MPA::getInstance()->isAdminRegistered()  )	locale = MPA::getInstance()->getUser( login ).locale;
	MPA_LOG_TRIVIAL( info , "Locale used:" + locale );

	map<string, string>::iterator endIt = argvals.end();

	map<string, string>::iterator loginIt = argvals.find("login");
	map<string, string>::iterator passwordIt = argvals.find("password");
	map<string, string>::iterator passwordConfirmIt = argvals.find("passwordConfirm");
	map<string, string>::iterator localeIt = argvals.find("locale");

	// There are all parameters
	if(	loginIt != endIt &&	passwordIt != endIt && passwordConfirmIt != endIt && localeIt != endIt )
	{
		// Check password are same
		if( passwordIt->second.compare( passwordConfirmIt->second ) == 0 )
		{
			ret = true;
		}
		else	badParamsMsg = MPA::getInstance()->getResourceBundle().translate( "Passwords don't match" , locale );
	}
	else	badParamsMsg = MPA::getInstance()->getResourceBundle().translate( "There are missing parameters" , locale );

	MPA_LOG_TRIVIAL( info , "End User::arePostAddParametersOk: " + StrUtil::bool2string( ret ) );

	return ret;
}

bool User::arePostDeleteParametersOk()
{
	bool ret = false;

	if(			argvals.find("version") != argvals.end()
			&&	argvals.find("token") != argvals.end()		) ret = true;

	return ret;
}

bool User::arePostUpdateParametersOk()
{
	bool ret = false;

	if(			argvals.find("name") != argvals.end()
			&&	argvals.find("version") != argvals.end()
			&&	argvals.find("token") != argvals.end()		) ret = true;

	return ret;
}

string User::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	// Get user
	mpapo::User user = MPA::getInstance()->getUser( login );

	if( user.isAdmin )
	{
		if( urlPairs.size() == 1 )
		{
			ptree usersChildren;

			vector<mpapo::User> users = MPA::getInstance()->getUsers();
			for (vector<mpapo::User>::iterator it = users.begin(); it != users.end(); it++)
			{
				ptree userPtree;
				userPtree.put("id", (*it).id);
				userPtree.put("version", (*it).version);
				userPtree.put("login", (*it).login);
				userPtree.put("isAdmin", StrUtil::bool2string( (*it).isAdmin ) );
				userPtree.put("pwdErrNbr", StrUtil::int2string( (*it).pwdErrNbr ) );

				usersChildren.push_back(std::make_pair("", userPtree));
			}

			root.add_child("users", usersChildren);
		}
	}

	return ret;
}

string User::executePostAddRequest(ptree & root)
{
	MPA_LOG_TRIVIAL(trace, "User::executePostAddRequest" );

	string ret = MPAO::DEFAULT_JSON_ID;

	bool isAdminRegistered = MPA::getInstance()->isAdminRegistered();

	if( ! isAdminRegistered || MPA::getInstance()->getUser( login ).isAdmin )
	{
		string login = argvals.find("login")->second;
		string pwd = argvals.find("password")->second;
		string locale = argvals.find("locale")->second;

		if( ! MPA::getInstance()->existUser( login ) )
		{
			if( MPA::isSecurePwd( pwd ))
			{
				mpapo::User user( MPA::getInstance()->getMPAPO() );
				user = MPA::getInstance()->addUser( ! isAdminRegistered, login, pwd, locale );

				// Get account ID
				ret = string( user.id );

				MPA_LOG_TRIVIAL(trace,"User ID added: " + ret);

				// Generate Json output
				root.push_back(BoostHelper::make_pair("version", user.version ));
			}
			else ret = MPA::getErrMsg(9);
		}
		else	ret = MPA::getErrMsg(10);
	}

	return ret;
}

string User::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	// Get user
	mpapo::User user = MPA::getInstance()->getUser( login );

	if( user.isAdmin )
	{
		MPA::getInstance()->delUser( urlPairs[0].second, atoi( argvals.find("version")->second ) );
		ret = "0";
	}

	return ret;
}

string User::executePostUpdateRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	// Get user
	mpapo::User user = MPA::getInstance()->getUser( login );

	if( user.isAdmin )
	{
		//TODO
		mpapo::Account account = mpa::Account::renameAccount( urlPairs[0].second , atoi( argvals.find("version")->second ) , argvals.find("name")->second );
		ret = urlPairs[0].second ;

		// Generate Json output
		root.push_back(BoostHelper::make_pair("version", StrUtil::int2string( account.version ) ));
	}

	return ret;
}

bool User::isObjectAlreadyExisting( string objectName )
{
	bool ret = false;

	// TODO : implement check code !!!!

	return ret;
}


User::~User()
{
	//MPA_LOG_TRIVIAL( info , "User destroyed" );
}

} /* namespace mpa */
