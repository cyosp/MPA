/*
 * Locale.cpp
 *
 *  Created on: 2017-02-17
 *      Author: CYOSP
 */

#include "Locale.hpp"

namespace mpa_api_rest_v1 {

string Locale::URL_STRING_PATH_IDENTIFIER = "locales";

Locale::Locale(HttpRequestType httpRequestType, ActionType actionType,
		const map<string, string>& argvals,
		vector<std::pair<string, int> > urlPairs) :
		MPAO(httpRequestType, actionType, argvals, urlPairs)
{
	restrictedAccess = false;
}


bool Locale::areGetParametersOk()
{
	bool ret = true;
	return ret;
}

bool Locale::arePostAddParametersOk()
{
	bool ret = false;

	return ret;
}

bool Locale::arePostDeleteParametersOk()
{
	bool ret = false;

	return ret;
}

bool Locale::arePostUpdateParametersOk()
{
	bool ret = false;

	return ret;
}

string Locale::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	ptree localesChildren;

	string locale;
	BOOST_FOREACH(locale, MPA::getInstance()->getResourceBundle().getLocales())
	{
		ptree localePtree;
		localePtree.put("name", locale);

		localesChildren.push_back(make_pair("", localePtree));
	}

	root.add_child("locales", localesChildren);

	ret = MPAO::OK_JSON_ID;

	return ret;
}

string Locale::executePostAddRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	return ret;
}

string Locale::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	return ret;
}

string Locale::executePostUpdateRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	return ret;
}

Locale::~Locale()
{
}

} /* namespace mpa_api_rest_v1 */
