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

bool User::areGetParametersOk()
{
	bool ret = true;
	return ret;
}

bool User::arePostAddParametersOk()
{
	bool ret = false;

	MPA_LOG_TRIVIAL(trace, "isAdminRegistered " + StrUtil::bool2string( MPA::getInstance()->isAdminRegistered() ) );

	if(	! MPA::getInstance()->isAdminRegistered()
			|| (		argvals.find("login") != argvals.end()
					&&	argvals.find("password") != argvals.end()
					&&	argvals.find("passwordConfirm") != argvals.end()
					&&	argvals.find("token") != argvals.end() )
		) ret = true;

	return ret;
}

bool User::arePostDeleteParametersOk()
{
	bool ret = false;

	if( argvals.find("version") != argvals.end() && argvals.find("id") != argvals.end() ) ret = true;

	return ret;
}

bool User::arePostUpdateParametersOk()
{
	bool ret = false;

	if(	argvals.find("name") != argvals.end() && argvals.find("version") != argvals.end() ) ret = true;

	return ret;
}

string User::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	map<string, Token> tokenList = MPAOFactory::getInstance()->getTokenList();
	map<string, Token>::iterator tokenIt = tokenList.find( argvals.find("token")->second );

	if( tokenIt != tokenList.end() && tokenIt->second.getUser().isAdmin )
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
	string ret = MPAO::DEFAULT_JSON_ID;

	bool isAdminRegistered = MPA::getInstance()->isAdminRegistered();


	map<string, Token> tokenList = MPAOFactory::getInstance()->getTokenList();
	map<string, Token>::iterator tokenIt = tokenList.find( argvals.find("token")->second );

	if( ! isAdminRegistered || (tokenIt != tokenList.end() && tokenIt->second.getUser().isAdmin) )
	{
		string login = argvals.find("login")->second;
		string pwd = argvals.find("password")->second;

		if( pwd.compare( argvals.find("passwordConfirm")->second ) == 0 )
		{
			if( ! MPA::getInstance()->existUser( login ) )
			{
				if( MPA::isSecurePwd( pwd ))
				{
					mpapo::User user( MPA::getInstance()->getMPAPO() );
					user = MPA::getInstance()->addUser( ! isAdminRegistered , login , pwd );

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
		else	ret = MPA::getErrMsg(8);

	}

	return ret;
}

string User::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	map<string, Token> tokenList = MPAOFactory::getInstance()->getTokenList();
	map<string, Token>::iterator tokenIt = tokenList.find( argvals.find("token")->second );

	if( tokenIt != tokenList.end() && tokenIt->second.getUser().isAdmin )
	{
		MPA::getInstance()->delUser( urlPairs[0].second, atoi( argvals.find("version")->second ) );
	}

	return ret;
}

string User::executePostUpdateRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	map<string, Token> tokenList = MPAOFactory::getInstance()->getTokenList();
	map<string, Token>::iterator tokenIt = tokenList.find( argvals.find("token")->second );

	if( tokenIt != tokenList.end() && tokenIt->second.getUser().isAdmin )
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
}

} /* namespace mpa */
