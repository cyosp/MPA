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
