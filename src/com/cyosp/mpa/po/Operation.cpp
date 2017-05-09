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

// This method must be call after:
// * Link operation to:
//    * Provider
//    * Category
// * Set date
void Operation::addToAmount( float amount )
{
	litesql::DataSource<mpapo::Account> accountDatasource = account().get();
	if( accountDatasource.count() > 0 )
	{
		// Get account
		Account account = accountDatasource.one();

		// Default case if there is no operation
		float accountBalance = 0;

		// Get all operation where balance must be updated
		bool firstToGetBalance = false;
		bool orderAsc = true;
		vector<mpapo::Operation> operations = account.operations().get( mpapo::Operation::Date > date ).orderBy( mpapo::Operation::Date , orderAsc ).all();
		for( vector<mpapo::Operation>::iterator it = operations.begin(); it != operations.end(); it++ )
		{
			// Get operation
			mpapo::Operation operation = ( *it );
			if( ! firstToGetBalance )
			{
				accountBalance = operation.accountBalance - operation.amount;
				firstToGetBalance = true;
			}

			// Update balance
			operation.addToBalance( amount );
			operation.update();
		}

		// Update account balance with operation amount
		accountBalance += amount;

		// Update operation amount and account balance
		this->amount = this->amount + amount;
		setAccountBalance( accountBalance );
		this->update();

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
		account.addToBalance( amount );
		account.update();
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
