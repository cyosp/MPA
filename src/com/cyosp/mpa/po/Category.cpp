/*
 * Category.cpp
 *
 *  Created on: 25 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/Category.hpp>

namespace mpapo
{

// Check if a category exists with the same name before to set the category name
// methode update() must be called manually after this method
void Category::setName( int accountId, string name )
{
	int categoryId = mpa::Category::getCategoryId( accountId, name );

	//MPA_LOG_TRIVIAL(trace,"setName1");
	//usleep( 10000000 );
	//MPA_LOG_TRIVIAL(trace,"setName2");

	if (categoryId == 0)	this->name = name;
	else	throw MPA::getErrMsg( 20 );
}

void Category::setAmount( float amount )
{
	this->amount = amount;
}

void Category::addToAmount( float amount )
{
	this->amount = this->amount + amount;
}

}


