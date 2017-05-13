/*
 * Provider.cpp
 *
 *  Created on: 17 April 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/api/rest/v1/Provider.hpp>

namespace mpa_api_rest_v1
{

    string Provider::URL_STRING_PATH_IDENTIFIER = "providers";

    Provider::Provider(HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals,
            vector<std::pair<string, int> > urlPairs) :
            MPAO(httpRequestType, actionType, argvals, urlPairs)
    {
        accountId = -1;
        id = -1;
    }

    bool Provider::isUrlPathValid()
    {
        bool ret = false;

        if( urlPairs.size() > 0 && urlPairs[0].first == Account::URL_STRING_PATH_IDENTIFIER )
        {
            accountId = urlPairs[0].second;
            ret = true;
        }

        return ret;
    }

    bool Provider::areGetParametersOk()
    {
        bool ret = isUrlPathValid();

        return ret;
    }

    bool Provider::arePostAddParametersOk()
    {
        bool ret = false;

        if( isUrlPathValid() && argvals.find("name") != argvals.end() )
            ret = true;

        return ret;
    }

    bool Provider::arePostDeleteParametersOk()
    {
        bool ret = false;

        if( urlPairs.size() > 0 && urlPairs[0].first == Provider::URL_STRING_PATH_IDENTIFIER )
        {
            id = urlPairs[0].second;
            if( MPAO::arePostDeleteParametersOk() )
                ret = true;
        }

        return ret;
    }

    bool Provider::arePostUpdateParametersOk()
    {
        bool ret = MPAO::arePostUpdateParametersOk();

        if( ret )
        {
            if( argvals.find("name") != argvals.end() )
                ret = true;
        }

        return ret;
    }

    string Provider::executeGetRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        // TODO: manage get for only one account
        ptree providersChildren;

        vector<mpapo::Provider> accounts = mpa::Provider::all(getAccountId());
        for(vector<mpapo::Provider>::iterator it = accounts.begin() ; it != accounts.end() ; it++)
        {
            ptree providerPtree;
            providerPtree.put("id", (*it).id);
            providerPtree.put("version", (*it).version);
            providerPtree.put("name", (*it).name);
            providerPtree.put("amount", StrUtil::float2string((*it).amount));

            providersChildren.push_back(std::make_pair("", providerPtree));
        }

        root.add_child("providers", providersChildren);

        return ret;
    }

    string Provider::executePostAddRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        string providerName = argvals.find("name")->second;

        //MPA_LOG_TRIVIAL(trace,"");

        mpapo::Provider provider = mpa::Provider::get(getAccountId(), providerName);

        //MPA_LOG_TRIVIAL(trace,"");

        // Get account ID
        ret = string(provider.id);

        MPA_LOG_TRIVIAL(trace, "Provider ID added: " + ret);

        // Generate Json output
        root.push_back(BoostHelper::make_pair("version", provider.version));
        root.push_back(BoostHelper::make_pair("amount", provider.amount));

        return ret;
    }

    string Provider::executePostDeleteRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        mpa::Provider::del(getAccountId(), getId(), getVersion());
        ret = MPAO::OK_JSON_ID;

        return ret;
    }

    string Provider::executePostUpdateRequest(ptree & root)
    {
        //MPA_LOG_TRIVIAL( trace , "Start" );

        string ret = MPAO::DEFAULT_JSON_ID;

        int providerId = urlPairs[1].second;
        int providerVersion = atoi(argvals.find("version")->second);
        string providerNewName = argvals.find("name")->second;

        mpapo::Provider provider = mpa::Provider::rename(getAccountId(), providerId, providerVersion, providerNewName);
        ret = StrUtil::int2string(providerId);

        // Generate Json output
        root.push_back(BoostHelper::make_pair("version", StrUtil::int2string(provider.version)));

        //MPA_LOG_TRIVIAL( trace , "End" );

        return ret;
    }

    int Provider::getAccountId()
    {
        return accountId;
    }

    int Provider::getId()
    {
        return id;
    }

    Provider::~Provider()
    {
    }

}
