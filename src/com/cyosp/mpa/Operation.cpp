/*
 * Operation.cpp
 *
 *  Created on: 18 April 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/Operation.hpp>

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

void Operation::setAccountBalance( float balance )
{
	this->accountBalance = balance;
}

}

namespace mpa
{

// Get operations following an account identified by ID
vector<mpapo::Operation> Operation::getOperations( int accountId )
{
	return mpa::Account::getAccount( accountId ).operations().get().all();
}

mpapo::Operation Operation::getOperation( int operationId )
{
	return select<mpapo::Operation>( MPA::getInstance()->getMPAPO() , mpapo::Operation::Id == operationId ).one();
}
Operation::~Operation()
{
}

} /* namespace mpa */
