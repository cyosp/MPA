/*
 * Account.hpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_ACCOUNT_HPP_
#define INCLUDES_MPA_ACCOUNT_HPP_

#include "com/cyosp/mpa/core/Category.hpp"
#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/exception/MsgNotTranslated.hpp"

namespace mpa
{
    class Account
    {
        public:
            static mpapo::Account & add(string accountName);
            static bool del(int id, int version);
            static bool isAccountAlreadyExisting(string accountName);
            static vector<mpapo::Account> all();
            static mpapo::Account get(int id);
            static mpapo::Account renameAccount(int accountId, int accountVersionToRename, string newAccountName);

            virtual ~Account();
    };

} /* namespace mpa */

#endif
