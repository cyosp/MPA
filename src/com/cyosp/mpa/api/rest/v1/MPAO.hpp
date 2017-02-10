/*
 * MPAO.hpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_API_REST_V1_MPAO_HPP_
#define INCLUDES_MPA_API_REST_V1_MPAO_HPP_

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

namespace mpa_api_rest_v1
{

class MPAO
{

public:
	static string DEFAULT_JSON_ID;

private:
	HttpRequestType httpRequestType;

protected:
	ActionType actionType;
	map<string, string> argvals;
	vector<std::pair<string, int> > urlPairs;

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

	string executeRequest(ptree & root);

	virtual ~MPAO();
};

} /* namespace mpa */

#endif
