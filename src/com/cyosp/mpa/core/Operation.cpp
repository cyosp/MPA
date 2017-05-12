/*
 * Operation.cpp
 *
 *  Created on: 18 April 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/core/Operation.hpp>

namespace mpa
{

    // Get operations following an account identified by ID
    vector<mpapo::Operation> Operation::all(int accountId)
    {
        return mpa::Account::get(accountId).operations().get().all();
    }

    mpapo::Operation Operation::get(int operationId)
    {
        return select<mpapo::Operation>(MPA::getInstance()->getMPAPO(), mpapo::Operation::Id == operationId).one();
    }

    bool Operation::del(int id, int version)
    {
        bool ret = false;

        MPA_LOG_TRIVIAL(trace,
                "Operation to delete:" + StrUtil::int2string(id) + " with version: " + StrUtil::int2string(version));

        try
        {
            mpapo::Operation operation = get(id);

            if( operation.isCorrectVersion(version) )
            {
                MPA_LOG_TRIVIAL(trace, "Operation found");

                MPA::getInstance()->beginTransaction();

                try
                {
                    // Update amounts (in order to remove it)
                    operation.addToAmount(operation.amount * -1.0);

                    if( operation.operationDetails().get().all().size() > 0 )
                    {
                        OperationDetail operationDetail = operation.operationDetails().get().one();
                        if( operationDetail.category().get().all().size() )
                        {
                            mpapo::Category category = operationDetail.category().get().one();
                            operationDetail.category().unlink(category);
                        }

                        operation.operationDetails().unlink(operationDetail);
                    }

                    if( operation.provider().get().all().size() > 0 )
                    {
                        mpapo::Provider provider = operation.provider().get().one();
                        operation.provider().unlink(provider);
                    }

                    if( operation.account().get().all().size() > 0 )
                    {
                        mpapo::Account account = operation.account().get().one();
                        operation.account().unlink(account);
                    }

                    // Delete operation
                    operation.del();

                    MPA::getInstance()->commitTransaction();
                }
                catch( Except & e )
                {
                    MPA::getInstance()->rollbackTransaction();
                }

                ret = true;
            }
            else
                throw mpa_exception::MsgNotTranslated(OPERATION_IMPOSSIBLE_BECAUSE_DATA_HAVE_CHANGED);
        }
        catch( NotFound & e )
        {
            // TODO : manage
            //throw mpa_exception::MsgNotTranslated( ACCOUNT_DOESNT_EXIST );
        }

        return ret;
    }

    Operation::~Operation()
    {
    }

} /* namespace mpa */
