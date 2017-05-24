/*
 * Account.cpp
 *
 *  Created on: 20 March 2015
 *      Author: cyosp
 */

#include "com/cyosp/mpa/core/Account.hpp"

namespace mpapo
{

    // Check if an account exist with the same name before to set the account name
    void Account::setName(string name)
    {
        bool find = mpa::Account::isAccountAlreadyExisting(name);

        //MPA_LOG_TRIVIAL(trace,"setName1");
        //usleep( 10000000 );
        //MPA_LOG_TRIVIAL(trace,"setName2");

        if( !find )
        {
            this->name = name;
            setUpdated();
        }
        else
            throw mpa_exception::MsgNotTranslated(ACCOUNT_SAME_NAME_ALREADY_EXIST);
    }

    void Account::addToBalance(float balance)
    {
        this->balance = this->balance + balance;
        setUpdated();
    }

}
