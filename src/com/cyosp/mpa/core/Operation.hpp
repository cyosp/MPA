/*
 * Operation.hpp
 *
 *  Created on: 18 April 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_OPERATION_HPP_
#define INCLUDES_MPA_OPERATION_HPP_

#include "com/cyosp/helpers/StrUtil.hpp"

#include "com/cyosp/mpa/core/Account.hpp"
#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"
#include "com/cyosp/mpa/po/MPAPO.hpp"
#include "com/cyosp/mpa/core/Provider.hpp"
#include "com/cyosp/mpa/core/Category.hpp"

namespace mpa
{

    class Operation
    {
        public:
            static vector<mpapo::Operation> all(int accountId);
            static mpapo::Operation get(int operationId);
            static bool del(int id, int version);

            virtual ~Operation();
    };

} /* namespace mpa */

#endif
