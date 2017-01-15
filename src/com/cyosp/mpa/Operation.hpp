/*
 * Operation.hpp
 *
 *  Created on: 18 April 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_OPERATION_HPP_
#define INCLUDES_MPA_OPERATION_HPP_

#include "com/cyosp/helpers/StrUtil.hpp"

#include "com/cyosp/mpa/Account.hpp"
#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"
#include "com/cyosp/mpa/po/MPAPO.hpp"
#include "com/cyosp/mpa/Provider.hpp"
#include "com/cyosp/mpa/Category.hpp"

namespace mpa
{

	class Operation
	{
		public:
			static vector<mpapo::Operation> getOperations( int accountId );
			static mpapo::Operation getOperation( int operationId );

			virtual ~Operation();
	};

} /* namespace mpa */

#endif
