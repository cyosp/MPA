/*
 * Account.cpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/api/rest/v1/Account.hpp>

namespace mpa_api_rest_v1
{

string MPAO::URL_STRING_PATH_IDENTIFIER = "accounts";

Account::Account( HttpRequestType httpRequestType, ActionType actionType , const map<string, string>& argvals, vector<std::pair<string, int> > urlPairs ) : MPAO( httpRequestType, actionType, argvals, urlPairs )
{}

bool Account::areGetParametersOk()
{
	bool ret = true;
	return ret;
}

bool Account::arePostAddParametersOk()
{
	bool ret = false;

	if( argvals.find("name") != argvals.end() ) ret = true;

	return ret;
}

bool Account::arePostDeleteParametersOk()
{
	bool ret = MPAO::arePostDeleteParametersOk();

	return ret;
}

bool Account::arePostUpdateParametersOk()
{
	bool ret = MPAO::arePostUpdateParametersOk();

	if( ret )
	{
		if (	argvals.find("name") != argvals.end()
			&&	argvals.find("token") != argvals.end()
			) ret = true;
	}

	return ret;
}

string Account::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	//MPA_LOG_TRIVIAL(trace, "" );

	ptree accountsChildren;

	vector<mpapo::Account> accounts = mpa::Account::getAccounts();
	for (vector<mpapo::Account>::iterator it = accounts.begin(); it != accounts.end(); it++)
	{
		ptree accountPtree;
		accountPtree.put("id", (*it).id);
		accountPtree.put("version", (*it).version);
		accountPtree.put("name", (*it).name);
		accountPtree.put("balance", StrUtil::float2string((*it).balance));

		accountsChildren.push_back(std::make_pair("", accountPtree));
	}

	root.add_child("accounts", accountsChildren);

	return ret;
}

string Account::executePostAddRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	MPA_LOG_TRIVIAL(trace,"Account name to add: " + argvals.find("name")->second );

	mpapo::Account account( MPA::getInstance()->getMPAPO() );
	account = mpa::Account::addAccount( argvals.find("name")->second );

	// Get account ID
	ret = string( account.id );

	MPA_LOG_TRIVIAL(trace,"Account ID added: " + ret);

	// Generate Json output
	root.push_back(BoostHelper::make_pair("version", account.version ));
	root.push_back(BoostHelper::make_pair("balance", account.balance ));

	return ret;
}

string Account::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	mpa::Account::delAccount( urlPairs[0].second , atoi( argvals.find("version")->second ) );
	ret = MPAO::OK_JSON_ID;

	return ret;
}

string Account::executePostUpdateRequest(ptree & root)
{
	//MPA_LOG_TRIVIAL( trace , "Start" );

	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	int accountVersion = atoi( argvals.find("version")->second );
	string accountNewName = argvals.find("name")->second;

	mpapo::Account account = mpa::Account::renameAccount( accountId , accountVersion , accountNewName );
	ret = StrUtil::int2string( accountId );

	// Generate Json output
	root.push_back(BoostHelper::make_pair("version", StrUtil::int2string( account.version ) ));

	//MPA_LOG_TRIVIAL( trace , "End" );

	return ret;
}

Account::~Account()
{
}

} /* namespace mpa */
