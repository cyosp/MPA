/*
 * Token.hpp
 *
 *  Created on: 2017-01-17
 *      Author: CYOSP
 */

#ifndef INCLUDES_MPA_API_REST_V1_TOKEN_HPP_
#define INCLUDES_MPA_API_REST_V1_TOKEN_HPP_

#include "com/cyosp/mpa/core/MPA.hpp"

namespace mpa_api_rest_v1
{

	class Token
	{
		private:
			// Created timestamp
			int created;
			// Last token use value
			int updated;
			// Token value
			string value;

		public:

	};

}

#endif
