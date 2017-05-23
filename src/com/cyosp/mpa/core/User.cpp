/*
 * User.cpp
 *
 *  Created on: 2017-05-23
 *      Author: CYOSP
 */

#include "User.hpp"

namespace mpa
{
    vector<mpapo::User> User::getAdminUsers()
    {
        return select<mpapo::User>(MPA::getInstance()->getMPAPO(), mpapo::User::IsAdmin == true).all();    //.orderBy(mpapo::Account::Name).all();
    }

    vector<mpapo::User> User::getUsers()
    {
        return select<mpapo::User>(MPA::getInstance()->getMPAPO()).all();
    }

    // There is an exception if user not found
    mpapo::User User::getUser(string login)
    {
        return select<mpapo::User>(MPA::getInstance()->getMPAPO(), mpapo::User::Login == login).one();
    }

    // Get user by ID
    mpapo::User User::getUser(int id)
    {
        return select<mpapo::User>(MPA::getInstance()->getMPAPO(), mpapo::User::Id == id).one();
    }

    bool User::existUser(string login)
    {
        return select<mpapo::User>(MPA::getInstance()->getMPAPO(), mpapo::User::Login == login).all().size() != 0;
    }

    mpapo::User & User::addUser(bool isAdmin, string login, string password, string locale)
    {
        mpapo::User * ret = NULL;

        ret = new mpapo::User(MPA::getInstance()->getMPAPO());
        ret->setIsAdmin(isAdmin);
        ret->setLogin(login);
        ret->setPassword(password);
        ret->setLocale(locale);
        ret->initializeVersion();
        ret->update();

        MPA_LOG_TRIVIAL(info, "User added, id=" + (*ret).id.value());

        return *ret;
    }

    bool User::delUser(int id, int version)
    {
        bool ret = false;

        MPA_LOG_TRIVIAL(trace,
                "User to delete:" + StrUtil::int2string(id) + " with version: " + StrUtil::int2string(version));

        try
        {
            mpapo::User userToDel = getUser(id);

            if( userToDel.isCorrectVersion(version) )
            {
                MPA_LOG_TRIVIAL(trace, "User found");

                MPA::getInstance()->beginTransaction();
                userToDel.del();
                MPA::getInstance()->commitTransaction();
            }
            else
                throw mpa_exception::MsgNotTranslated(OPERATION_IMPOSSIBLE_BECAUSE_DATA_HAVE_CHANGED);
        }
        catch( NotFound & e )
        {
            throw mpa_exception::MsgNotTranslated(ACCOUNT_DOESNT_EXIST);
        }

        return ret;
    }

    bool User::isSecurePwd(const string pwd)
    {
        bool ret = false;

        int pwdSize = pwd.size();

        if( pwdSize >= MPA::PWD_SECURITY_MIN_SIZE )
        {
            int pwdUpperNbr = 0;
            int pwdNDigitNbr = 0;
            for(int i = 0 ; i < pwdSize ; i++)
            {
                if( isupper(pwd[i]) )
                    pwdUpperNbr++;
                if( isdigit(pwd[i]) )
                    pwdNDigitNbr++;
            }

            if( pwdUpperNbr >= MPA::PWD_SECURITY_UPPER_CASE_NBR && pwdNDigitNbr >= MPA::PWD_SECURITY_DIGIT_NBR )
                ret = true;
        }

        return ret;
    }

    bool User::isAdminRegistered()
    {
        return getAdminUsers().size() > 0;
    }
    
    User::~User()
    {
    }
}
