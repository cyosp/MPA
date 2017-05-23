/*
 * User.hpp
 *
 *  Created on: 2017-05-23
 *      Author: CYOSP
 */

#ifndef COM_CYOSP_MPA_CORE_USER_HPP_
#define COM_CYOSP_MPA_CORE_USER_HPP_

#include <vector>
#include <string>

#include "MPA.hpp"

#include "litesql.hpp"
#include "com/cyosp/mpa/po/MPAPO.hpp"

// no name collisions expected
using namespace litesql;
using namespace mpapo;

using std::vector;
using std::string;

namespace mpa
{
    
    class User
    {
        public:
            // Get administrator user
            static vector<mpapo::User> getAdminUsers();
            // Get users
            static vector<mpapo::User> getUsers();
            // Get user by login
            static mpapo::User getUser(string login);
            // Get user by id
            static mpapo::User getUser(int id);
            // Del an user
            static bool delUser(int id, int version);
            // Check if user exist by login
            static bool existUser(string login);
            // Add a user
            static mpapo::User & addUser(bool isAdmin, string login, string password, string locale);

            static bool isSecurePwd(const string pwd);

            static bool isAdminRegistered();

            virtual ~User();
    };

}

#endif
