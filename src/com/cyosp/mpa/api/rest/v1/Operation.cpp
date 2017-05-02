/*
 * Operation.cpp
 *
 *  Created on: 18 April 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/api/rest/v1/Operation.hpp>

namespace mpa_api_rest_v1
{

string Operation::URL_STRING_PATH_IDENTIFIER = "operations";

Operation::Operation(HttpRequestType httpRequestType, ActionType actionType,
		const map<string, string>& argvals,
		vector<std::pair<string, int> > urlPairs) :
		MPAO(httpRequestType, actionType, argvals, urlPairs)
{}

bool Operation::areGetParametersOk()
{
	bool ret = true;
	return ret;
}

bool Operation::arePostAddParametersOk()
{
	bool ret = false;

	if( argvals.find("date") != argvals.end() && argvals.find("provider") != argvals.end() && argvals.find("amount") != argvals.end() && argvals.find("category") != argvals.end() && argvals.find("note") != argvals.end() ) ret = true;

	MPA_LOG_TRIVIAL(trace, "Return: " + StrUtil::bool2string( ret ) );

	return ret;
}

bool Operation::arePostDeleteParametersOk()
{
	bool ret = MPAO::arePostDeleteParametersOk();

	return ret;
}

bool Operation::arePostUpdateParametersOk()
{
	bool ret = MPAO::arePostUpdateParametersOk();

	if( ret )
	{
		if( argvals.find("date") != argvals.end() && argvals.find("provider") != argvals.end() && argvals.find("amount") != argvals.end() && argvals.find("category") != argvals.end() && argvals.find("note") != argvals.end() ) ret = true;
	}

	return ret;
}

string Operation::executeGetRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	//MPA_LOG_TRIVIAL(trace, "" );

	int accountId = urlPairs[0].second;

	ptree operationsChildren;

	vector<mpapo::Operation> operations = mpa::Operation::getOperations( accountId );
	for (vector<mpapo::Operation>::iterator it = operations.begin(); it != operations.end(); it++)
	{
		//MPA_LOG_TRIVIAL(trace, "" );

		// Get operation
		mpapo::Operation operation = (*it);
		// Get sub operations list
		vector<mpapo::SubOperation> subOperations = operation.subOperations().get().all();

		//MPA_LOG_TRIVIAL(trace, "" );
		ptree operationPtree;
		operationPtree.put("id", operation.id);
		operationPtree.put("version", operation.version);
		operationPtree.put("date", operation.date);
		//MPA_LOG_TRIVIAL(trace, "" );

		string providerString = "";
		litesql::DataSource<mpapo::Provider> providerDatasource = operation.provider().get();
		if( providerDatasource.count() > 0  )	providerString = providerDatasource.one().name;
		operationPtree.put("provider", providerString );

		//MPA_LOG_TRIVIAL(trace, "" );
		operationPtree.put("amount", StrUtil::float2string(operation.amount));
		//MPA_LOG_TRIVIAL(trace, "" );
		operationPtree.put("accountBalance", StrUtil::float2string(operation.accountBalance));

		ptree subOperationsChildren;

		//MPA_LOG_TRIVIAL(trace, "" );

		//For now there is only one suboperation
		for (vector<mpapo::SubOperation>::iterator itSub = subOperations.begin(); itSub != subOperations.end(); itSub++)
		{
			//MPA_LOG_TRIVIAL(trace, "" );
			mpapo::SubOperation subOperation = (*itSub);
			ptree subOperationPtree;
			subOperationPtree.put("id", subOperation.id);

			string categoryString = "";
			litesql::DataSource<mpapo::Category> categoryDatasource = subOperation.category().get();
			if( categoryDatasource.count() > 0  )	categoryString = categoryDatasource.one().name;
			subOperationPtree.put("category", categoryString );

			subOperationPtree.put("note", subOperation.note);
			subOperationPtree.put("amount", subOperation.amount);

			subOperationsChildren.push_back(std::make_pair("", subOperationPtree));
		}

		operationPtree.add_child("subOperations", subOperationsChildren);
		operationsChildren.push_back(std::make_pair("", operationPtree));

		ret = MPAO::OK_JSON_ID;
	}

	root.add_child("operations", operationsChildren);

	return ret;
}

string Operation::executePostAddRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	int accountId = urlPairs[0].second;
	string date = argvals.find("date")->second;
	string providerName = argvals.find("provider")->second;
	float amount = StrUtil::string2float( argvals.find("amount")->second );
	string categoryName = argvals.find("category")->second;
	string note = argvals.find("note")->second;

	// TODO : verify how it works in multithread
	MPA::getInstance()->getMPAPO().begin();

	// Get account balance
	float accountBalance = 0;
	vector<mpapo::Operation> accountOpSize = mpa::Account::getAccount( accountId ).operations().get().all();
	if( accountOpSize.size() > 0 )	accountBalance = accountOpSize[ accountOpSize.size() -1 ].accountBalance;

	// Update account balance
	accountBalance += amount;

	//MPA_LOG_TRIVIAL(trace,"");

	// Create SubOPeration
	mpapo::SubOperation subOperation( MPA::getInstance()->getMPAPO() );
	subOperation.initializeVersion();
	subOperation.setAmount( amount );
	subOperation.setNote( note );
	subOperation.update();

	// Create Operation
	mpapo::Operation operation( MPA::getInstance()->getMPAPO() );
	operation.initializeVersion();
	operation.setDate( date );
	operation.setAmount( amount );
	operation.setAccountBalance( accountBalance );
	operation.update();

	// Link SubOperation to Operation
	operation.subOperations().link( subOperation );

	// Get provider
	mpapo::Provider provider = mpa::Provider::getProvider( accountId , providerName );
	// Update provider amount
	provider.addToAmount( amount );
	provider.update();

	// Link provider to operation
	operation.provider().link( provider );

	// Get category
	mpapo::Category category = mpa::Category::getCategory( accountId , categoryName );
	// Update category amount
	category.addToAmount( amount );
	category.update();

	// Link category to subOperation
	subOperation.category().link( category );

	// Get account
	mpapo::Account account = mpa::Account::getAccount( accountId );
	// Update account balance
	account.addToBalance( amount );
	account.update();

	// Link operation to account
	account.operations().link(operation);

	MPA::getInstance()->getMPAPO().commit();

	//MPA_LOG_TRIVIAL(trace,"");

	// Get account ID
	ret = string( operation.id );

	MPA_LOG_TRIVIAL(trace,"Category ID added: " + ret);

	// Generate Json output
	root.push_back(BoostHelper::make_pair("version", operation.version ));
	root.push_back(BoostHelper::make_pair("accountBalance", operation.accountBalance ));

	return ret;
}

string Operation::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	/*int accountId = urlPairs[0].second;
	int categoryId = urlPairs[1].second;
	int categoryVersion = atoi( argvals.find("version")->second );

	try
	{
		mpapo::Category category = Category::getCategory(accountId , categoryId);

		if( category.isCorrectVersion( categoryVersion ) )
		{
			MPA_LOG_TRIVIAL(trace,"Category found");

			// TODO : check there is no reference to category : operations...
			Account::getAccount( accountId ).categories().unlink(category);

			MPA::getInstance()->getMPAPO().begin();
			category.del();
			MPA::getInstance()->getMPAPO().commit();
		}
		else throw MPA::getErrMsg( 4 );
	}
	catch (NotFound & e)
	{
		throw MPA::getErrMsg( 2 );
	}*/

	return ret;
}

string Operation::executePostUpdateRequest(ptree & root)
{
	MPA_LOG_TRIVIAL( trace , "Start" );

	string ret = MPAO::DEFAULT_JSON_ID;

	/*int accountId = urlPairs[0].second;
	int categoryId = urlPairs[1].second;
	int categoryVersion = atoi( argvals.find("version")->second );
	string categoryNewName = argvals.find("name")->second;

	mpapo::Category category = rename( accountId , categoryId , categoryVersion , categoryNewName );
	ret = StrUtil::int2string( categoryId );

	// Generate Json output
	root.push_back(make_pair("version", StrUtil::int2string( category.version ) ));

	MPA_LOG_TRIVIAL( trace , "End" );*/

	return ret;
}

Operation::~Operation()
{
}

} /* namespace mpa */
