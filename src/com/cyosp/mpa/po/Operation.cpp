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
	// Update provider amount
	litesql::DataSource<mpapo::Provider> providerDatasource = provider().get();
	if( providerDatasource.count() > 0  )
	{
		Provider provider = providerDatasource.one();
		provider.addToAmount( amount );
		provider.update();
	}

	// Update category amount
	litesql::DataSource<mpapo::OperationDetail> operationDetailDatasource = operationDetails().get();
	if( operationDetailDatasource.count() > 0  )
	{
		OperationDetail operationDetail = operationDetailDatasource.one();

		litesql::DataSource<mpapo::Category> categoryDatasource = operationDetail.category().get();
		if( categoryDatasource.count() > 0 )
		{
			Category category = categoryDatasource.one();
			category.addToAmount( amount );
			category.update();
		}
	}

	// Update account balance
	litesql::DataSource<mpapo::Account> accountDatasource = account().get();
	if( accountDatasource.count() > 0 )
	{
		Account account = accountDatasource.one();

		account.addToBalance( amount );
		account.update();
	}

	// Update operation amount
	this->amount = this->amount + amount;
	this->update();
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
