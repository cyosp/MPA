/*
 * MPAO.hpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_API_REST_V1_MPAO_HPP_
#define INCLUDES_MPA_API_REST_V1_MPAO_HPP_

class MPAFactory;

#include "com/cyosp/mpa/core/MPA.hpp"

#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

#include <map>
using std::map;

#include <string>
using std::string;

#include <vector>
using std::vector;

enum HttpRequestType { GET, POST };
enum ActionType { NONE, LOGIN, ADD, DELETE, UPDATE };

static const string INVALID_TOKEN = "Invalid token";
static const string TOKEN_ARGUMENT_NOT_FOUND = "Token argument not found";
static const string THERE_ARE_MISSING_PARAMETERS = "There are missing parameters";
static const string PASSWORDS_DONT_MATCH = "Passwords don't match";
static const string BAD_IDENTIFIER = "Bad identifier";
static const string BAD_PASSWORD = "Bad password";
static const string PASSWORD_SECURITY_TOO_LOW = "Password security is too low";

namespace mpa_api_rest_v1
{

class MPAO
{

public:
	static string DEFAULT_JSON_ID;
	static string OK_JSON_ID;

private:
	HttpRequestType httpRequestType;

protected:
	ActionType actionType;
	// Request parameters received
	map<string, string> argvals;
	// URI stored in a vector
	vector<std::pair<string, int> > urlPairs;
	bool restrictedAccess;
	string badParamsMsg;

	string login;

	virtual bool isValidAccess();

	virtual bool areGetParametersOk() = 0;
	virtual bool arePostLoginParametersOk();
	virtual bool arePostAddParametersOk() = 0;
	virtual bool arePostDeleteParametersOk();
	virtual bool arePostUpdateParametersOk();

	virtual string executeGetRequest(ptree & root) = 0;
	virtual string executePostLoginRequest(ptree & root);
	virtual string executePostAddRequest(ptree & root) = 0;
	virtual string executePostDeleteRequest(ptree & root) = 0;
	virtual string executePostUpdateRequest(ptree & root) = 0;

public:
	MPAO( HttpRequestType httpRequestType, ActionType actionType , const map<string, string>& argvals, vector<std::pair<string, int> > urlPairs );

	bool areParametersOk();
	string getBadParamsMsg();

	string executeRequest(ptree & root);

	string & getLogin();

	virtual ~MPAO();
};

} /* namespace mpa */

#endif
