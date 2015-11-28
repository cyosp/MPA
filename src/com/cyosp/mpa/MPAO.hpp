/*
 * MPAO.hpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_MPAO_HPP_
#define INCLUDES_MPA_MPAO_HPP_

#include "com/cyosp/mpa/MPA.hpp"

#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

#include <map>
using std::map;

#include <string>
using std::string;

#include <vector>
using std::vector;

enum HttpRequestType { GET, POST };
enum ActionType { ADD, DELETE, UPDATE };

namespace mpa
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
	bool isAdmin;
	vector<std::pair<string, int> > urlPairs;

	virtual bool areGetParametersOk() = 0;
	virtual bool arePostAddParametersOk() = 0;
	virtual bool arePostDeleteParametersOk();
	virtual bool arePostUpdateParametersOk();

	virtual string executeGetRequest(ptree & root) = 0;
	virtual string executePostAddRequest(ptree & root) = 0;
	virtual string executePostDeleteRequest(ptree & root) = 0;
	virtual string executePostUpdateRequest(ptree & root) = 0;

public:
	MPAO( HttpRequestType httpRequestType, ActionType actionType , const map<string, string>& argvals, bool isAdmin, vector<std::pair<string, int> > urlPairs );

	bool areParametersOk();

	string executeRequest(ptree & root);

	virtual ~MPAO();
};

} /* namespace mpa */

#endif /* INCLUDES_MPA_MPAO_HPP_ */
