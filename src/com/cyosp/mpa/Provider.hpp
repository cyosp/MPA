/*
 * Provider.hpp
 *
 *  Created on: 17 April 2015
 *      Author: cyosp
 */

#ifndef INCLUDES_MPA_PROVIDER_HPP_
#define INCLUDES_MPA_PROVIDER_HPP_

#include "com/cyosp/helpers/StrUtil.hpp"

#include "com/cyosp/mpa/Account.hpp"
#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/MPAO.hpp"
#include "com/cyosp/mpa/MPAPO.hpp"

namespace mpa
{

class Provider: public MPAO
{
private:
	static vector<mpapo::Provider> getProviders( int accountId );
	void remove( int accountId , int providerId , int version );

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
	Provider(HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals , bool isAdmin, vector<std::pair<string, int> > urlPairs );

	static int getProviderId( int accountId , string providerName );
	static mpapo::Provider getProvider( int accountId , string providerName );
	static mpapo::Provider getProvider( int providerId );
	static mpapo::Provider rename( int accountId , int providerId, int providerVersion , string newName );

	virtual ~Provider();
};

} /* namespace mpa */

#endif /* INCLUDES_MPA_PROVIDER_HPP_ */
