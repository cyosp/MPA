/*
 * Category.cpp
 *
 *  Created on: 25 March 2015
 *      Author: cyosp
 */

#include "com/cyosp/mpa/api/rest/v1/Category.hpp"

namespace mpa_api_rest_v1
{

Category::Category(HttpRequestType httpRequestType, ActionType actionType,
		const map<string, string>& argvals, bool isAdmin,
		vector<std::pair<string, int> > urlPairs) :
		MPAO(httpRequestType, actionType, argvals, isAdmin, urlPairs)
{}

bool Category::areGetParametersOk()
{
	bool ret = true;
	return ret;
}

bool Category::arePostAddParametersOk()
{
	bool ret = false;

	if( argvals.find("name") != argvals.end() ) ret = true;

	return ret;
}

bool Category::arePostDeleteParametersOk()
{
	bool ret = MPAO::arePostDeleteParametersOk();

	return ret;
}

bool Category::arePostUpdateParametersOk()
{
	bool ret = MPAO::arePostUpdateParametersOk();

	if( ret )
	{
		if (argvals.find("name") != argvals.end() ) ret = true;
	}

	return ret;
}

string Category::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	//MPA_LOG_TRIVIAL(trace, "" );

	int accountId = urlPairs[0].second;

	ptree categoriesChildren;

	vector<mpapo::Category> accounts = mpa::Category::getCategories( accountId );
	for (vector<mpapo::Category>::iterator it = accounts.begin(); it != accounts.end(); it++)
	{
		ptree categoryPtree;
		categoryPtree.put("id", (*it).id);
		categoryPtree.put("version", (*it).version);
		categoryPtree.put("name", (*it).name);
		categoryPtree.put("amount", StrUtil::float2string((*it).amount));

		categoriesChildren.push_back(std::make_pair("", categoryPtree));
	}

	root.add_child("categories", categoriesChildren);

	return ret;
}

string Category::executePostAddRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	string categoryName = argvals.find("name")->second;

	//MPA_LOG_TRIVIAL(trace,"");

	mpapo::Category category = mpa::Category::getCategory( accountId , categoryName );

	//MPA_LOG_TRIVIAL(trace,"");

	// Get account ID
	ret = string( category.id );

	MPA_LOG_TRIVIAL(trace,"Category ID added: " + ret);

	// Generate Json output
	root.push_back(make_pair("version", category.version ));
	root.push_back(make_pair("amount", category.amount ));

	return ret;
}

string Category::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	int categoryId = urlPairs[1].second;
	int categoryVersion = atoi( argvals.find("version")->second );

	mpa::Category::remove( accountId , categoryId , categoryVersion );

	return ret;
}

string Category::executePostUpdateRequest(ptree & root)
{
	//MPA_LOG_TRIVIAL( trace , "Start" );

	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	int categoryId = urlPairs[1].second;
	int categoryVersion = atoi( argvals.find("version")->second );
	string categoryNewName = argvals.find("name")->second;

	mpapo::Category category = mpa::Category::rename( accountId , categoryId , categoryVersion , categoryNewName );
	ret = StrUtil::int2string( categoryId );

	// Generate Json output
	root.push_back(make_pair("version", StrUtil::int2string( category.version ) ));

	//MPA_LOG_TRIVIAL( trace , "End" );

	return ret;
}

Category::~Category()
{
}

} /* namespace mpa */
