/*
 * Token.cpp
 *
 *  Created on: 2017-01-17
 *      Author: CYOSP
 */

#include <com/cyosp/mpa/api/rest/v1/Token.hpp>

namespace mpa_api_rest_v1
{

    Token::Token(string userLogin)
    {
        // Define created time
        time(&created);

        // Updated time is created one
        updated = created;

        // Token value is based on created time
        std::stringstream strm;
        strm << created;
        value = strm.str();

        // Store user
        this->userLogin = userLogin;
    }

    string & Token::getValue()
    {
        return value;
    }

    string & Token::getUserLogin()
    {
        return userLogin;
    }

}
