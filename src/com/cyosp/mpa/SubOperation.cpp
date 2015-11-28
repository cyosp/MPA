/*
 * SubOperation.cpp
 *
 *  Created on: 20 April 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/SubOperation.hpp>


namespace mpapo
{

void SubOperation::setAmount( float amount )
{
	this->amount = amount;
}

void SubOperation::setNote( string note )
{
	this->note = note;
}

}

namespace mpa
{

SubOperation::~SubOperation()
{
}

} /* namespace mpa */
