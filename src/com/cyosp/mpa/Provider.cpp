/*
 * Provider.cpp
 *
 *  Created on: 17 April 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/Provider.hpp>

namespace mpapo
{

// Check if a provider exists with the same name before to set the provider name
// methode update() must be called manually after this method
void Provider::setName( int accountId, string name )
{
	int providerId = mpa::Provider::getProviderId( accountId, name );

	//MPA_LOG_TRIVIAL(trace,"setName1");
	//usleep( 10000000 );
	//MPA_LOG_TRIVIAL(trace,"setName2");

	if (providerId == 0)	this->name = name;
	else	throw MPA::getErrMsg( 20 );
}

void Provider::setAmount( float amount )
{
	this->amount = amount;
}

void Provider::addToAmount( float amount )
{
	this->amount = this->amount + amount;
}

}

namespace mpa
{

Provider::Provider(HttpRequestType httpRequestType, ActionType actionType,
		const map<string, string>& argvals, bool isAdmin,
		vector<std::pair<string, int> > urlPairs) :
		MPAO(httpRequestType, actionType, argvals, isAdmin, urlPairs)
{}

bool Provider::areGetParametersOk()
{
	bool ret = true;
	return ret;
}

bool Provider::arePostAddParametersOk()
{
	bool ret = false;

	if( argvals.find("name") != argvals.end() ) ret = true;

	return ret;
}

bool Provider::arePostDeleteParametersOk()
{
	bool ret = MPAO::arePostDeleteParametersOk();

	return ret;
}

bool Provider::arePostUpdateParametersOk()
{
	bool ret = MPAO::arePostUpdateParametersOk();

	if( ret )
	{
		if (argvals.find("name") != argvals.end() ) ret = true;
	}

	return ret;
}

string Provider::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	//MPA_LOG_TRIVIAL(trace, "" );

	int accountId = urlPairs[0].second;

	// TODO: manage get for only one account
	ptree providersChildren;

	vector<mpapo::Provider> accounts = getProviders( accountId );
	for (vector<mpapo::Provider>::iterator it = accounts.begin(); it != accounts.end(); it++)
	{
		ptree providerPtree;
		providerPtree.put("id", (*it).id);
		providerPtree.put("version", (*it).version);
		providerPtree.put("name", (*it).name);
		providerPtree.put("amount", StrUtil::float2string((*it).amount));

		providersChildren.push_back(std::make_pair("", providerPtree));
	}

	root.add_child("providers", providersChildren);

	return ret;
}

string Provider::executePostAddRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	string providerName = argvals.find("name")->second;

	//MPA_LOG_TRIVIAL(trace,"");

	mpapo::Provider provider = getProvider( accountId , providerName );

	//MPA_LOG_TRIVIAL(trace,"");

	// Get account ID
	ret = string( provider.id );

	MPA_LOG_TRIVIAL(trace,"Provider ID added: " + ret);

	// Generate Json output
	root.push_back(make_pair("version", provider.version ));
	root.push_back(make_pair("amount", provider.amount ));

	return ret;
}

string Provider::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	int providerId = urlPairs[1].second;
	int providerVersion = atoi( argvals.find("version")->second );

	remove( accountId , providerId , providerVersion );

	return ret;
}

string Provider::executePostUpdateRequest(ptree & root)
{
	//MPA_LOG_TRIVIAL( trace , "Start" );

	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	int providerId = urlPairs[1].second;
	int providerVersion = atoi( argvals.find("version")->second );
	string providerNewName = argvals.find("name")->second;

	mpapo::Provider provider = rename( accountId , providerId , providerVersion , providerNewName );
	ret = StrUtil::int2string( providerId );

	// Generate Json output
	root.push_back(make_pair("version", StrUtil::int2string( provider.version ) ));

	//MPA_LOG_TRIVIAL( trace , "End" );

	return ret;
}


// Return 0 if doesn't exist, Provider ID otherwise
int Provider::getProviderId( int accountId , string providerName )
{
	int ret = 0;

	vector<mpapo::Provider> providers = getProviders( accountId );
	// Get providers iterator
	vector<mpapo::Provider>::iterator it = providers.begin();

	while (it != providers.end() && ! ret )
	{
		mpapo::Provider provider = (*it);

		if (provider.name == providerName)
			ret = provider.id;
		else
			it++;
	}

	return ret;
}

// Get provider in all case
// Create one if no existing
mpapo::Provider Provider::getProvider( int accountId , string providerName )
{
	// Get provider Id
	int providerId = getProviderId( accountId , providerName);

	// Create it if it doesn't exist
	if( providerId == 0 )
	{
		MPA::getInstance()->getMPAPO().begin();
		mpapo::Provider provider( MPA::getInstance()->getMPAPO() );
		provider.initializeVersion();
		provider.setName( accountId , providerName);
		provider.setAmount( 0 );
		provider.update();

		Account::getAccount( accountId ).providers().link(provider);
		MPA::getInstance()->getMPAPO().commit();

		providerId = provider.id;
	}

	return getProvider( providerId );
}

// Get providers following an account identified by ID
vector<mpapo::Provider> Provider::getProviders( int accountId )
{
	return Account::getAccount( accountId ).providers().get().all();
}

mpapo::Provider Provider::getProvider( int providerId )
{
	return select<mpapo::Provider>( MPA::getInstance()->getMPAPO() , mpapo::Provider::Id == providerId ).one();
}

void Provider::remove( int accountId , int providerId , int version )
{
	try
	{
		mpapo::Provider provider = Provider::getProvider( providerId );

		if( provider.isCorrectVersion( version ) )
		{
			//MPA_LOG_TRIVIAL(trace,"Not found");

			if( provider.operations().get().all().size() > 0 ) throw MPA::getErrMsg( MSG_DEL_IMPOSSIBLE_OPERATIONS );

			MPA::getInstance()->getMPAPO().begin();
			Account::getAccount( accountId ).providers().unlink( provider );
			provider.del();
			MPA::getInstance()->getMPAPO().commit();
		}
		else throw MPA::getErrMsg( 4 );
	}
	catch (NotFound & e)
	{
		throw MPA::getErrMsg( 2 );
	}
}

// Rename provider
mpapo::Provider Provider::rename( int accountId , int providerId, int providerVersion , string newName )
{
	//MPA_LOG_TRIVIAL( trace , "Start" );

	try
	{
		mpapo::Provider provider = getProvider( providerId );

		if( provider.isCorrectVersion(  providerVersion ) )
		{
			provider.setName( accountId , newName );
			provider.updateVersion();
			provider.update();

			//MPA_LOG_TRIVIAL( trace , "End" );

			// Return is here because there is no empty constructor for mpapo::Provider::Provider()
			return provider;
		}
		else throw MPA::getErrMsg( 4 );
	}
	catch (NotFound & e)
	{
		throw MPA::getErrMsg( 2 );
	}
}

Provider::~Provider()
{
}

} /* namespace mpa */
