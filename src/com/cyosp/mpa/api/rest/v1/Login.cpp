/*
 * Login.cpp
 *
 *  Created on: 2017-01-04
 *      Author: CYOSP
 */

#include <com/cyosp/mpa/api/rest/v1/Login.hpp>

namespace mpa_api_rest_v1
{

    string Login::URL_STRING_PATH_IDENTIFIER = "login";

    Login::Login(HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals,
            vector<std::pair<string, int> > urlPairs) :
            MPAO(httpRequestType, actionType, argvals, urlPairs)
    {
        restrictedAccess = false;
    }

    bool Login::areGetParametersOk()
    {
        return false;
    }

    bool Login::arePostLoginParametersOk()
    {
        bool ret = false;

        if( argvals.find("login") != argvals.end() && argvals.find("pwd") != argvals.end() )
            ret = true;

        return ret;
    }

    bool Login::arePostAddParametersOk()
    {
        return false;
    }

    string Login::executeGetRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        return ret;
    }

    string Login::executePostLoginRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        string login = argvals.find("login")->second;
        string pwd = argvals.find("pwd")->second;

        string locale = MPA::DEFAULT_LOCALE;
        if( argvals.find("locale") != argvals.end() )
            locale = argvals.find("locale")->second;

        // There is an administrator user defined
        if( MPA::getInstance()->isAdminRegistered() )
        {
            try
            {
                mpapo::User user = MPA::getInstance()->getUser(login);
                if( user.pwdErrNbr < MPA::PWD_SECURITY_ERROR_NBR )
                {
                    if( user.password.value().compare(pwd) == 0 )
                    {
                        // Reset password error because password used is correct
                        if( user.pwdErrNbr != 0 )
                        {
                            user.resetPwdErr();
                            user.update();
                        }

                        // Create and register token
                        Token token = Token(user.login);
                        MPAOFactory::getInstance()->getTokenList().insert(
                                std::pair<string, string>(token.getValue(), token.getUserLogin()));

                        ret = token.getValue();
                    }
                    else
                    {
                        // TODO : Message for fail2ban or same program using remote IP
                        MPA_LOG_TRIVIAL(info, "Account: " + user.login + " has password failed");

                        // Register this password error
                        user.addPwdErr();
                        user.update();

                        ret = MPA::getInstance()->getResourceBundle().translate(BAD_PASSWORD, locale);
                    }
                }
                else
                {
                    // TODO : Message for fail2ban or same program using remote IP
                    MPA_LOG_TRIVIAL(error, "Account: " + user.login + " blocked");

                    ret = MPA::getInstance()->getResourceBundle().translate(USER_ACCOUNT_BLOCKED, locale);
                }
            }
            catch( NotFound & e )
            {
                MPA_LOG_TRIVIAL(trace, "User authentication fails due to login error");

                ret = BAD_IDENTIFIER;
            }
        }
        else
        {
            MPA_LOG_TRIVIAL(trace, ADMIN_ACCOUNT_NOT_DEFINED);

            ret = MPA::getInstance()->getResourceBundle().translate(ADMIN_ACCOUNT_NOT_DEFINED, locale);
        }

        return ret;
    }

    string Login::executePostAddRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        return ret;
    }

    string Login::executePostDeleteRequest(ptree & root)
    {
        string ret = MPAO::DEFAULT_JSON_ID;

        return ret;
    }

    string Login::executePostUpdateRequest(ptree & root)
    {
        //MPA_LOG_TRIVIAL( trace , "Start" );

        string ret = MPAO::DEFAULT_JSON_ID;

        return ret;
    }

    Login::~Login()
    {
    }

}
