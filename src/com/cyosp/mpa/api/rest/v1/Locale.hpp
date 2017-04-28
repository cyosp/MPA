/*
 * Locale.hpp
 *
 *  Created on: 2017-02-17
 *      Author: CYOSP
 */

#ifndef COM_CYOSP_MPA_API_REST_V1_LOCALE_HPP_
#define COM_CYOSP_MPA_API_REST_V1_LOCALE_HPP_

#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAO.hpp"

namespace mpa_api_rest_v1
{

class Locale: public MPAO
{
	public:
		static string URL_STRING_PATH_IDENTIFIER;

	protected:
		bool areGetParametersOk();
		bool arePostAddParametersOk();
		bool arePostDeleteParametersOk();
		bool arePostUpdateParametersOk();

		string executeGetRequest(ptree & root);
		string executePostAddRequest(ptree & root);
		string executePostDeleteRequest(ptree & root);
		string executePostUpdateRequest(ptree & root);

	public:
		Locale( HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals, vector<std::pair<string, int> > urlPairs );;
		virtual ~Locale();
};

} /* namespace mpa_api_rest_v1 */

#endif /* COM_CYOSP_MPA_API_REST_V1_LOCALE_HPP_ */
