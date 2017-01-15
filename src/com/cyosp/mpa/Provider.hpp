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
#include "com/cyosp/mpa/po/MPAPO.hpp"

namespace mpa
{

class Provider
{
public:
	static vector<mpapo::Provider> getProviders( int accountId );
	static void remove( int accountId , int providerId , int version );
	static int getProviderId( int accountId , string providerName );
	static mpapo::Provider getProvider( int accountId , string providerName );
	static mpapo::Provider getProvider( int providerId );
	static mpapo::Provider rename( int accountId , int providerId, int providerVersion , string newName );

	virtual ~Provider();
};

}

#endif
