/*
 * MPAPOImpl.cpp
 *
 *  Created on: 18 June 2014
 *      Author: cyosp
 */

#include "com/cyosp/mpa/po/MPAPO.hpp"

#include "com/cyosp/mpa/core/MPA.hpp"
#include <boost/log/trivial.hpp>

void mpapo::MPAO::initializeVersion()
{
	this->version = 0;
}

void mpapo::MPAO::updateVersion()
{
	this->version = this->version + 1;
}

bool mpapo::MPAO::isCorrectVersion(int versionToCheck)
{
	return this->version == versionToCheck;
}

#include <unistd.h>
