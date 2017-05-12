/*
 * Provider.cpp
 *
 *  Created on: 17 April 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/core/Provider.hpp>

namespace mpapo
{

    // Check if a provider exists with the same name before to set the provider name
    // methode update() must be called manually after this method
    void Provider::setName(int accountId, string name)
    {
        int providerId = mpa::Provider::getProviderId(accountId, name);

        //MPA_LOG_TRIVIAL(trace,"setName1");
        //usleep( 10000000 );
        //MPA_LOG_TRIVIAL(trace,"setName2");

        if( providerId == 0 )
            this->name = name;
        else
            throw mpa_exception::MsgNotTranslated(CATEGORY_SAME_NAME_ALREADY_EXIST);
    }

    void Provider::setAmount(float amount)
    {
        this->amount = amount;
    }

    void Provider::addToAmount(float amount)
    {
        this->amount = this->amount + amount;
    }
}
