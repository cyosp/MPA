/*
 * User.cpp
 *
 *  Created on: 2017-02-08
 *      Author: CYOSP
 */

#include "com/cyosp/mpa/po/MPAPO.hpp"

namespace mpapo
{

    void mpapo::User::setIsAdmin(bool isAdmin)
    {
        this->isAdmin = isAdmin;
        updateVersion();
    }

    void mpapo::User::setLocale(string locale)
    {
        this->locale = locale;
        updateVersion();
    }

    void mpapo::User::setLogin(string login)
    {
        this->login = login;
        updateVersion();
    }

    // TODO : check password is not empty
    // Security password must be implemented here, it seems better
    void mpapo::User::setPassword(string password)
    {
        this->password = password;
        updateVersion();
    }

    void mpapo::User::addPwdErr()
    {
        this->pwdErrNbr = this->pwdErrNbr + 1;
        updateVersion();
    }

    void mpapo::User::resetPwdErr()
    {
        this->pwdErrNbr = 0;
        updateVersion();
    }
}

