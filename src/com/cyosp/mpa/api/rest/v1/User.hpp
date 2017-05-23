/*
 * User.hpp
 *
 *  Created on: 21 March 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_API_REST_V1_USER_HPP_
#define INCLUDES_MPA_API_REST_V1_USER_HPP_

#include "com/cyosp/helpers/BoostHelper.hpp"

#include "com/cyosp/mpa/api/rest/v1/Account.hpp"
#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/core/User.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"
#include "com/cyosp/mpa/api/rest/v1/Token.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAOFactory.hpp"

namespace mpa_api_rest_v1
{

    class User : public MPAO
    {
        public:
            static string URL_STRING_PATH_IDENTIFIER;

        protected:
            bool isValidAccess();

            bool areGetParametersOk();
            bool arePostAddParametersOk();
            bool arePostDeleteParametersOk();
            bool arePostUpdateParametersOk();

            string executeGetRequest(ptree & root);
            string executePostAddRequest(ptree & root);
            string executePostDeleteRequest(ptree & root);
            string executePostUpdateRequest(ptree & root);

            bool isObjectAlreadyExisting(string objectName);

        public:
            User(HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals,
                    vector<std::pair<string, int> > urlPairs);

            virtual ~User();
    };

}

#endif
