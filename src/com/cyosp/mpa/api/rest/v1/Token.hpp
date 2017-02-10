/*
 * Token.hpp
 *
 *  Created on: 2017-01-17
 *      Author: CYOSP
 */

#ifndef INCLUDES_MPA_API_REST_V1_TOKEN_HPP_
#define INCLUDES_MPA_API_REST_V1_TOKEN_HPP_

#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/po/MPAPO.hpp"

namespace mpa_api_rest_v1
{

	class Token
	{
		private:
			// Created timestamp
			time_t created;
			// Last token use value
			time_t updated;
			// Token value
			string value;
			//
			mpapo::User * user;


		public:
			Token( mpapo::User & user );
			string & getValue();
			mpapo::User & getUser();

	};

}

#endif
