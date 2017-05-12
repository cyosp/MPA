/*
 * Category.cpp
 *
 *  Created on: 25 March 2015
 *      Author: cyosp
 */

#include "com/cyosp/mpa/api/rest/v1/Category.hpp"

// URL managed:
//  * GET
//    * /mpa/res/accounts/10/categories
// * POST
//	  * /mpa/res/categories/add
//	  * /mpa/res/categories/20/upd?version=1
//	  * /mpa/res/categories/20/del?version=1

namespace mpa_api_rest_v1
{

    string Category::URL_STRING_PATH_IDENTIFIER = "categories";

    Category::Category(HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals,
            vector<std::pair<string, int> > urlPairs) :
            MPAO(httpRequestType, actionType, argvals, urlPairs), account(MPA::getInstance()->getMPAPO())
    {
        id = -1;
    }

    // /mpa/res/accounts/10/categories
    bool Category::areGetParametersOk()
    {
        bool ret = false;

        if( urlPairs.size() > 0 && urlPairs[0].first == Account::URL_STRING_PATH_IDENTIFIER )
        {
            int accountId = urlPairs[0].second;
            account = mpa::Account::get(accountId);

            ret = true;
        }

        return ret;
    }

    // /mpa/res/categories/add
    bool Category::arePostAddParametersOk()
    {
        bool ret = false;

        const string NAME_PARAM = "name";
        const string ACCOUNT_ID_PARAM = "accountId";

        if( argvals.find(NAME_PARAM) != argvals.end() && argvals.find(ACCOUNT_ID_PARAM) != argvals.end() )
        {
            name = argvals.find(NAME_PARAM)->second;

            int accountId = atoi(argvals.find(ACCOUNT_ID_PARAM)->second);
            account = mpa::Account::get(accountId);

            ret = true;
        }

        return ret;
    }

    // /mpa/res/categories/20/del
    bool Category::arePostDeleteParametersOk()
    {
        bool ret = false;

        if( urlPairs.size() > 0 && urlPairs[0].first == Category::URL_STRING_PATH_IDENTIFIER )
        {
            id = urlPairs[0].second;
            if( MPAO::arePostDeleteParametersOk() )
                ret = true;
        }

        return ret;
    }

    bool Category::arePostUpdateParametersOk()
    {
        bool ret = MPAO::arePostUpdateParametersOk();

        if( ret )
        {
            if( argvals.find("name") != argvals.end() )
                ret = true;
        }

        return ret;
    }

    string Category::executeGetRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        ptree categoriesChildren;

        vector<mpapo::Category> accounts = mpa::Category::all(getAccount().id);
        for(vector<mpapo::Category>::iterator it = accounts.begin() ; it != accounts.end() ; it++)
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

        //MPA_LOG_TRIVIAL(trace,"");

        mpapo::Category category = mpa::Category::get(getAccount().id, getName());

        //MPA_LOG_TRIVIAL(trace,"");

        // Get account ID
        ret = string(category.id);

        MPA_LOG_TRIVIAL(trace, "Category ID added: " + ret);

        // Generate Json output
        root.push_back(BoostHelper::make_pair("version", category.version));
        root.push_back(BoostHelper::make_pair("amount", category.amount));

        return ret;
    }

    string Category::executePostDeleteRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        mpa::Category::del(getId(), getVersion());
        ret = MPAO::OK_JSON_ID;

        return ret;
    }

    string Category::executePostUpdateRequest(ptree & root)
    {
        //MPA_LOG_TRIVIAL( trace , "Start" );

        string ret = MPAO::DEFAULT_JSON_ID;

        int categoryId = urlPairs[1].second;
        int categoryVersion = atoi(argvals.find("version")->second);
        string categoryNewName = argvals.find("name")->second;

        mpapo::Category category = mpa::Category::rename(getAccount().id, categoryId, categoryVersion, categoryNewName);
        ret = StrUtil::int2string(categoryId);

        // Generate Json output
        root.push_back(BoostHelper::make_pair("version", StrUtil::int2string(category.version)));

        //MPA_LOG_TRIVIAL( trace , "End" );

        return ret;
    }

    mpapo::Account & Category::getAccount()
    {
        return account;
    }

    string & Category::getName()
    {
        return name;
    }

    int Category::getId()
    {
        return id;
    }

    Category::~Category()
    {
    }

}
