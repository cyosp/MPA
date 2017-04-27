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
		const map<string, string>& argvals,
		vector<std::pair<string, int> > urlPairs) :
		MPAO(httpRequestType, actionType, argvals, urlPairs)
{
	accountId = -1;
}

bool Category::isUrlPathValid()
{
	bool ret = false;

	// TODO remove "hard coded" accounts string
	if( urlPairs.size() > 0 && urlPairs[0].first == "accounts"	)
	{
		accountId = urlPairs[0].second;
		ret = true;
	}

	return ret;
}

bool Category::areGetParametersOk()
{
	bool ret = isUrlPathValid();

	return ret;
}

bool Category::arePostAddParametersOk()
{
	bool ret = false;

	if( isUrlPathValid() && argvals.find("name") != argvals.end() ) ret = true;

	return ret;
}

bool Category::arePostDeleteParametersOk()
{
	bool ret = false;

	if( isUrlPathValid() && MPAO::arePostDeleteParametersOk() )	ret = true;

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

	ptree categoriesChildren;

	vector<mpapo::Category> accounts = mpa::Category::getCategories( getAccontId() );
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

	string categoryName = argvals.find("name")->second;

	//MPA_LOG_TRIVIAL(trace,"");

	mpapo::Category category = mpa::Category::getCategory( getAccontId() , categoryName );

	//MPA_LOG_TRIVIAL(trace,"");

	// Get account ID
	ret = string( category.id );

	MPA_LOG_TRIVIAL(trace,"Category ID added: " + ret);

	// Generate Json output
	root.push_back(BoostHelper::make_pair("version", category.version ));
	root.push_back(BoostHelper::make_pair("amount", category.amount ));

	return ret;
}

string Category::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	int categoryId = urlPairs[1].second;
	int categoryVersion = atoi( argvals.find("version")->second );

	mpa::Category::remove( getAccontId() , categoryId , categoryVersion );
	ret = MPAO::OK_JSON_ID;

	return ret;
}

string Category::executePostUpdateRequest(ptree & root)
{
	//MPA_LOG_TRIVIAL( trace , "Start" );

	string ret = MPAO::DEFAULT_JSON_ID;

	int categoryId = urlPairs[1].second;
	int categoryVersion = atoi( argvals.find("version")->second );
	string categoryNewName = argvals.find("name")->second;

	mpapo::Category category = mpa::Category::rename( getAccontId() , categoryId , categoryVersion , categoryNewName );
	ret = StrUtil::int2string( categoryId );

	// Generate Json output
	root.push_back(BoostHelper::make_pair("version", StrUtil::int2string( category.version ) ));

	//MPA_LOG_TRIVIAL( trace , "End" );

	return ret;
}

int Category::getAccontId()
{
	return accountId;
}

Category::~Category()
{
}

} /* namespace mpa */
