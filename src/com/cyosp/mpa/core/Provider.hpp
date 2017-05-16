/*
 * Provider.hpp
 *
 *  Created on: 17 April 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_PROVIDER_HPP_
#define INCLUDES_MPA_PROVIDER_HPP_

#include "com/cyosp/helpers/StrUtil.hpp"

#include "com/cyosp/mpa/core/Account.hpp"
#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/po/MPAPO.hpp"

namespace mpa
{

    class Provider
    {
        public:
            static vector<mpapo::Provider> all(int accountId);
            // Delete an entry
            static void del( int id , int version );
            static mpapo::Provider get(int accountId, string providerName);
            static mpapo::Provider get(int providerId);
            static mpapo::Provider rename(int accountId, int providerId, int providerVersion, string newName);

            static int getProviderId(int accountId, string providerName);

            virtual ~Provider();
    };

}

#endif
