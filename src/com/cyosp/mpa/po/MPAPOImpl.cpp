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

void mpapo::User::setIsAdmin( bool isAdmin )
{
	this->isAdmin = isAdmin;
}

void mpapo::User::setLogin( string login )
{
	this->login = login;
}

// TODO : check password is not empty
// Security password must be implemented here, it seems better
void mpapo::User::setPassword( string password )
{
	this->password  = password;
}

void mpapo::User::addPwdErr()
{
	this->pwdErrNbr = this->pwdErrNbr + 1;
}

void mpapo::User::resetPwdErr()
{
	this->pwdErrNbr = 0;
}


#include <unistd.h>
