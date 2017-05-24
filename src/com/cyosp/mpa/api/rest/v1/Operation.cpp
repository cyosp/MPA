/*
 * Operation.cpp
 *
 *  Created on: 18 April 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/api/rest/v1/Operation.hpp>

namespace mpa_api_rest_v1
{

    string Operation::URL_STRING_PATH_IDENTIFIER = "operations";

    Operation::Operation(HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals,
            vector<std::pair<string, int> > urlPairs) :
            MPAO(httpRequestType, actionType, argvals, urlPairs), provider(MPA::getInstance()->getMPAPO()), category(
                    MPA::getInstance()->getMPAPO())
    {
        accountId = -1;
        date = "";
        amount = 0;
        id = -1;
    }

    bool Operation::isUrlPathValid()
    {
        bool ret = false;

        if( urlPairs.size() > 0 && urlPairs[0].first == Account::URL_STRING_PATH_IDENTIFIER )
        {
            accountId = urlPairs[0].second;
            ret = true;
        }

        return ret;
    }

    bool Operation::areGetParametersOk()
    {
        bool ret = isUrlPathValid();

        return ret;
    }

    bool Operation::arePostAddParametersOk()
    {
        bool ret = false;

        if( isUrlPathValid() && argvals.find("date") != argvals.end() && argvals.find("provider") != argvals.end()
                && argvals.find("amount") != argvals.end() && argvals.find("category") != argvals.end()
                && argvals.find("note") != argvals.end() )
        {
            date = argvals.find("date")->second;

            string providerName = argvals.find("provider")->second;
            provider = mpa::Provider::get(getAccountId(), providerName);

            amount = StrUtil::string2float(argvals.find("amount")->second);

            string categoryName = argvals.find("category")->second;
            category = mpa::Category::get(getAccountId(), categoryName);

            note = argvals.find("note")->second;

            ret = true;
        }

        //MPA_LOG_TRIVIAL(trace, "Return: " + StrUtil::bool2string(ret));

        return ret;
    }

    bool Operation::arePostDeleteParametersOk()
    {
        bool ret = false;

        if( urlPairs.size() > 0 && urlPairs[0].first == Operation::URL_STRING_PATH_IDENTIFIER
                && MPAO::arePostDeleteParametersOk() )
        {
            id = urlPairs[0].second;
            ret = true;
        }
        return ret;
    }

    bool Operation::arePostUpdateParametersOk()
    {
        bool ret = MPAO::arePostUpdateParametersOk();

        if( ret )
        {
            if( argvals.find("date") != argvals.end() && argvals.find("provider") != argvals.end()
                    && argvals.find("amount") != argvals.end() && argvals.find("category") != argvals.end()
                    && argvals.find("note") != argvals.end() )
                ret = true;
        }

        return ret;
    }

    string Operation::executeGetRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        //MPA_LOG_TRIVIAL(trace, "" );

        ptree operationsChildren;

        bool orderAsc = true;
        vector<mpapo::Operation> operations = getAccount().operations().get(mpapo::Operation::Date > getDate()).orderBy(
                mpapo::Operation::Date, orderAsc).all();
        for(vector<mpapo::Operation>::iterator it = operations.begin() ; it != operations.end() ; it++)
        {
            //MPA_LOG_TRIVIAL(trace, "" );

            // Get operation
            mpapo::Operation operation = (*it);
            // Get sub operations list
            vector<mpapo::OperationDetail> OperationDetails = operation.operationDetails().get().all();

            //MPA_LOG_TRIVIAL(trace, "" );
            ptree operationPtree;
            operationPtree.put("id", operation.id);
            operationPtree.put("version", operation.version);
            operationPtree.put("date", operation.date);
            //MPA_LOG_TRIVIAL(trace, "" );

            string providerString = "";
            litesql::DataSource<mpapo::Provider> providerDatasource = operation.provider().get();
            if( providerDatasource.count() > 0 )
                providerString = providerDatasource.one().name;
            operationPtree.put("provider", providerString);

            //MPA_LOG_TRIVIAL(trace, "" );
            operationPtree.put("amount", StrUtil::float2string(operation.amount));
            //MPA_LOG_TRIVIAL(trace, "" );
            operationPtree.put("accountBalance", StrUtil::float2string(operation.accountBalance));

            ptree operationDetailsChildren;

            //MPA_LOG_TRIVIAL(trace, "" );

            //For now there is only one OperationDetail
            for(vector<mpapo::OperationDetail>::iterator itSub = OperationDetails.begin() ;
                    itSub != OperationDetails.end() ; itSub++)
            {
                //MPA_LOG_TRIVIAL(trace, "" );
                mpapo::OperationDetail OperationDetail = (*itSub);
                ptree OperationDetailPtree;
                OperationDetailPtree.put("id", OperationDetail.id);
                OperationDetailPtree.put("version", OperationDetail.version);

                string categoryString = "";
                litesql::DataSource<mpapo::Category> categoryDatasource = OperationDetail.category().get();
                if( categoryDatasource.count() > 0 )
                    categoryString = categoryDatasource.one().name;
                OperationDetailPtree.put("category", categoryString);

                OperationDetailPtree.put("note", OperationDetail.note);
                OperationDetailPtree.put("amount", OperationDetail.amount);

                operationDetailsChildren.push_back(std::make_pair("", OperationDetailPtree));
            }

            operationPtree.add_child("details", operationDetailsChildren);
            operationsChildren.push_back(std::make_pair("", operationPtree));

            ret = MPAO::OK_JSON_ID;
        }

        root.add_child("operations", operationsChildren);

        return ret;
    }

    string Operation::executePostAddRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        // Create OperationDetail
        mpapo::OperationDetail operationDetail(MPA::getInstance()->getMPAPO());
        operationDetail.setAmount(getAmount());
        operationDetail.setNote(getNote());
        operationDetail.initializeVersion();

        // Create Operation
        mpapo::Operation operation(MPA::getInstance()->getMPAPO());
        operation.setDate(getDate());

        MPA::getInstance()->beginTransaction();

        try
        {
            operationDetail.store();

            // Give operation available
            operation.store();

            // Link OperationDetail to Operation
            operation.operationDetails().link(operationDetail);
            // Link provider to operation
            operation.provider().link(getProvider());
            // Link category to OperationDetail
            operationDetail.category().link(getCategory());
            // Link operation to account
            getAccount().operations().link(operation);

            operation.initializeVersion();

            // Update amounts and balance
            operation.addToAmount(getAmount());

            MPA::getInstance()->commitTransaction();
        }
        catch( Except & e )
        {
            MPA::getInstance()->rollbackTransaction();
        }

        // Get operation Id
        ret = string(operation.id);

        // Generate Json output
        root.push_back(BoostHelper::make_pair("version", operation.version));
        // Following operation date insertion, operation balance is not account balance
        // Example: operation date is before last operation date
        root.push_back(BoostHelper::make_pair("accountBalance", getAccount().balance));

        return ret;
    }

    string Operation::executePostDeleteRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        mpa::Operation::del(getId(), getVersion());
        ret = MPAO::OK_JSON_ID;

        return ret;
    }

    string Operation::executePostUpdateRequest(ptree & root)
    {
        MPA_LOG_TRIVIAL(trace, "Start");

        string ret = MPAO::DEFAULT_JSON_ID;

        /*int accountId = urlPairs[0].second;
         int categoryId = urlPairs[1].second;
         int categoryVersion = atoi( argvals.find("version")->second );
         string categoryNewName = argvals.find("name")->second;

         mpapo::Category category = rename( accountId , categoryId , categoryVersion , categoryNewName );
         ret = StrUtil::int2string( categoryId );

         // Generate Json output
         root.push_back(make_pair("version", StrUtil::int2string( category.version ) ));

         MPA_LOG_TRIVIAL( trace , "End" );*/

        return ret;
    }

    int Operation::getAccountId()
    {
        return accountId;
    }

    // User account id to retrieve Account
    // This allow to have always an Account up to date
    mpapo::Account Operation::getAccount()
    {
        return mpa::Account::get(getAccountId());
    }

    string & Operation::getDate()
    {
        return date;
    }

    mpapo::Provider & Operation::getProvider()
    {
        return provider;
    }

    float Operation::getAmount()
    {
        return amount;
    }

    mpapo::Category & Operation::getCategory()
    {
        return category;
    }

    string & Operation::getNote()
    {
        return note;
    }

    int Operation::getId()
    {
        return id;
    }

    Operation::~Operation()
    {
    }
}
