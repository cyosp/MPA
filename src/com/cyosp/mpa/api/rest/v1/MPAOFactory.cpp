/*
 * MPAOFactory.cpp
 *
 *  Created on: 21 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/api/rest/v1/MPAOFactory.hpp>

namespace mpa
{

// Initialize static member
MPAOFactory * MPAOFactory::mpaofactory = NULL;

MPAOFactory * MPAOFactory::getInstance()
{
	if (mpaofactory == NULL)
		mpaofactory = new MPAOFactory();

	return mpaofactory;
}

MPAOFactory::MPAOFactory()
{
}

// Return NULL if URL is bad
// GET
//	/mpa/res-adm/users
//	/mpa/res/accounts
//	/mpa/res/accounts/10
//	/mpa/res/accounts/10/categories
//	/mpa/res/infos
// POST
//	/mpa/res/login
//	/mpa/res/users/add
//	/mpa/res/users/0/del
//	/mpa/res/users/10/upd?version=1
//	/mpa/res/accounts/add
//	/mpa/res/accounts/20/del?version=1
//	/mpa/res/accounts/20/upd?version=1
//	/mpa/res/accounts/20/categories/add
//	/mpa/res/accounts/20/categories/30/del?version=1
mpa::MPAO * MPAOFactory::getMPAO(HttpRequestType requestType, const string& url,
		const map<string, string>& argvals, bool isAdmin)
{
	mpa::MPAO * ret = NULL;

	//
	// Decode URL
	//

	ActionType actionType = NONE;
	vector<std::pair<string, int> > urlPairs;

	boost::smatch matches;

	const boost::regex startUrl("^/mpa/(res|res-adm)(/.*)$");
	if (boost::regex_match(url, matches, startUrl))
	{
		MPA_LOG_TRIVIAL(trace, "Match with start URL");

		// Remove start of URL
		string urlToAnalyse = matches[2];

		if( requestType == POST )
		{
			const boost::regex actionTypeRegex("(.*)/([a-z]+)$");
			if (boost::regex_match(urlToAnalyse, matches, actionTypeRegex))
			{
				MPA_LOG_TRIVIAL(trace, "Action type: " + matches[2]);

				// Remove URL action type
				urlToAnalyse = matches[1];

				if (matches[2] == "login")
				{
					actionType = LOGIN;

					// Update URL in order to be compliant to the standard others
					urlToAnalyse = "/login/0";
				}
				else if (matches[2] == "logout")
					actionType = LOGOUT;
				else if (matches[2] == "add")
				{
					actionType = ADD;

					// Update URL in order to be compliant to the standard others
					urlToAnalyse += "/0";
				}
				else if (matches[2] == "del")
					actionType = DELETE;
				else if (matches[2] == "upd")
					actionType = UPDATE;


				const boost::regex urlPairRegex("^/([a-z]+)/([0-9]+)(.*)$");
				// Fill vector starting by the beginning of URL
				while (boost::regex_match(urlToAnalyse, matches, urlPairRegex))
				{
					// Update URL
					string name = matches[1];
					string idString = matches[2];
					int id = atoi( idString );
					urlToAnalyse = matches[3];

					MPA_LOG_TRIVIAL(trace, "Name: " + name + ", id: " + idString );

					urlPairs.push_back(std::pair<string, int>(name, id));
				}

				MPA_LOG_TRIVIAL(trace, "End URL analyze");
			}
			else MPA_LOG_TRIVIAL(trace, "URL doesn't match action type");
		}
		else
		{
			MPA_LOG_TRIVIAL(trace, "URL to analyze: " + urlToAnalyse );

			// Manage URL like: GET /mpa/res/accounts
			const boost::regex urlStartRegex("^/([a-z]+)(.*)$");
			while( boost::regex_match(urlToAnalyse, matches, urlStartRegex) )
			{
				MPA_LOG_TRIVIAL(trace, "URL start match" );

				// Set values
				string name = matches[1];
				string idString = "";
				int id = 0;

				urlToAnalyse = matches[2];

				MPA_LOG_TRIVIAL(trace, "New URL to analyze: " + urlToAnalyse );

				// Manage URL like: GET /mpa/res/accounts/10
				const boost::regex urlIdRegex("^/([0-9]+)(.*)$");
				// Fill vector starting by beginning of URL
				if (boost::regex_match(urlToAnalyse, matches, urlIdRegex))
				{
					MPA_LOG_TRIVIAL(trace, "URL ID match" );

					idString = matches[1];
					id = atoi( idString );
					urlToAnalyse = matches[2];

				}

				MPA_LOG_TRIVIAL(trace, "Name: " + name + ", id: " + idString );

				urlPairs.push_back(std::pair<string, int>(name, id));
			}
		}

		// Manage case where URL doesn't match with an expected one
		if( urlPairs.size() > 0 )
		{

			int lastPosition = urlPairs.size()-1;
			string lastIdentifier = urlPairs[lastPosition].first;

			MPA_LOG_TRIVIAL(trace, "Last identifier: " + lastIdentifier );

			if( lastIdentifier == "login" )				ret = new mpa_api_rest_v1::Login( requestType , actionType, argvals , isAdmin, urlPairs );
			else if( lastIdentifier == "accounts" )		ret = new Account( requestType , actionType, argvals , isAdmin, urlPairs );
			else if ( lastIdentifier == "users" )		ret = new User( requestType , actionType , argvals , isAdmin, urlPairs );
			else if ( lastIdentifier == "infos" )		ret = new Info( requestType , actionType , argvals , isAdmin, urlPairs );
			else if ( lastIdentifier == "categories" )	ret = new Category( requestType , actionType , argvals , isAdmin, urlPairs );
			else if ( lastIdentifier == "providers" )	ret = new Provider( requestType , actionType , argvals , isAdmin, urlPairs );
			else if ( lastIdentifier == "operations" )	ret = new Operation( requestType , actionType , argvals , isAdmin, urlPairs );
		}
		else	MPA_LOG_TRIVIAL(info, MPA::getErrMsg( 21 ) );
	}
	else
		MPA_LOG_TRIVIAL(trace, "Doesn't match with POST start URL");

	return ret;
}

} /* namespace mpa */
