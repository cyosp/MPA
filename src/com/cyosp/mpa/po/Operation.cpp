/*
 * Operation.cpp
 *
 *  Created on: 18 April 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/core/Operation.hpp>

namespace mpapo
{

void Operation::setDate( string date )
{
	this->date = date;
}

void Operation::setAmount( float amount )
{
	this->amount = amount;
}

void Operation::addToAmount( float amount )
{
	this->amount = this->amount + amount;

	litesql::DataSource<mpapo::Provider> providerDatasource = provider().get();
	if( providerDatasource.count() > 0  )
	{
		Provider provider = providerDatasource.one();
		provider.addToAmount( amount );
		provider.update();
	}
}

void Operation::setAccountBalance( float balance )
{
	this->accountBalance = balance;
}

void Operation::addToBalance( float amount )
{
	this->accountBalance = this->accountBalance + amount;
}

}
