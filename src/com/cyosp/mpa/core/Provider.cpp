/*
 * Provider.cpp
 *
 *  Created on: 17 April 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/core/Provider.hpp>

namespace mpa
{
    // Return 0 if doesn't exist, Provider ID otherwise
    int Provider::getProviderId(int accountId, string providerName)
    {
        int ret = 0;

        vector<mpapo::Provider> providers = all(accountId);
        // Get providers iterator
        vector<mpapo::Provider>::iterator it = providers.begin();

        while( it != providers.end() && !ret )
        {
            mpapo::Provider provider = (*it);

            if( provider.name == providerName )
                ret = provider.id;
            else
                it++;
        }

        return ret;
    }

    // Get provider in all case
    // Create one if no existing
    mpapo::Provider Provider::get(int accountId, string providerName)
    {
        // Get provider Id
        int providerId = getProviderId(accountId, providerName);

        // Create it if it doesn't exist
        if( providerId == 0 )
        {
            mpapo::Provider provider(MPA::getInstance()->getMPAPO());
            provider.initializeVersion();
            provider.setName(accountId, providerName);
            provider.setAmount(0);

            mpapo::Account::ProvidersHandle providersHandle = Account::get(accountId).providers();

            // Transaction contains only database modification in order to reduce transaction time
            MPA::getInstance()->beginTransaction();
            try
            {
                provider.update();
                providersHandle.link(provider);
                MPA::getInstance()->commitTransaction();
            }
            catch( Except & e )
            {
                MPA::getInstance()->rollbackTransaction();
            }

            providerId = provider.id;
        }

        return get(providerId);
    }

    // Get providers following an account identified by ID
    vector<mpapo::Provider> Provider::all(int accountId)
    {
        return Account::get(accountId).providers().get().all();
    }

    mpapo::Provider Provider::get(int providerId)
    {
        return select<mpapo::Provider>(MPA::getInstance()->getMPAPO(), mpapo::Provider::Id == providerId).one();
    }

    void Provider::del(int id, int version)
    {
        try
        {
            mpapo::Provider provider = Provider::get(id);

            if( provider.isCorrectVersion(version) )
            {
                if( provider.account().get().all().size() > 0 )
                {
                    mpapo::Account account = provider.account().get().one();

                    MPA::getInstance()->beginTransaction();
                    try
                    {
                        provider.account().unlink(account);
                        provider.del();
                        MPA::getInstance()->commitTransaction();
                    }
                    catch( Except & e )
                    {
                        MPA::getInstance()->rollbackTransaction();
                    }
                }
            }
            else
                throw mpa_exception::MsgNotTranslated(OPERATION_IMPOSSIBLE_BECAUSE_DATA_HAVE_CHANGED);
        }
        catch( NotFound & e )
        {
            throw mpa_exception::MsgNotTranslated(ACCOUNT_DOESNT_EXIST);
        }
    }

    // Rename provider
    mpapo::Provider Provider::rename(int accountId, int providerId, int providerVersion, string newName)
    {
        //MPA_LOG_TRIVIAL( trace , "Start" );

        try
        {
            mpapo::Provider provider = get(providerId);

            if( provider.isCorrectVersion(providerVersion) )
            {
                provider.setName(accountId, newName);
                provider.updateVersion();
                provider.update();

                //MPA_LOG_TRIVIAL( trace , "End" );

                // Return is here because there is no empty constructor for mpapo::Provider::Provider()
                return provider;
            }
            else
                throw mpa_exception::MsgNotTranslated(OPERATION_IMPOSSIBLE_BECAUSE_DATA_HAVE_CHANGED);
        }
        catch( NotFound & e )
        {
            throw mpa_exception::MsgNotTranslated(ACCOUNT_DOESNT_EXIST);
        }
    }

    Provider::~Provider()
    {
    }

} /* namespace mpa */
