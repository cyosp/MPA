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
		MPAO(httpRequestType, actionType, argvals, urlPairs),
			account( MPA::getInstance()->getMPAPO() ),
			provider( MPA::getInstance()->getMPAPO() ),
			category( MPA::getInstance()->getMPAPO() )
{
	date = "";
	amount = 0;
}

bool Operation::isUrlPathValid()
{
	bool ret = false;

	if( urlPairs.size() > 0 && urlPairs[0].first == Account::URL_STRING_PATH_IDENTIFIER	)
	{
		int accountId = urlPairs[0].second;
		account = mpa::Account::getAccount( accountId );

		ret = true;
	}

	return ret;
}


bool Operation::areGetParametersOk()
{
	bool ret = isUrlPathValid();

	return ret;
}

bool Operation::arePostAddParametersOk()
{
	bool ret = false;

	if( isUrlPathValid()
			&& argvals.find("date") != argvals.end()
			&& argvals.find("provider") != argvals.end()
			&& argvals.find("amount") != argvals.end()
			&& argvals.find("category") != argvals.end()
			&& argvals.find("note") != argvals.end() )
	{
		date = argvals.find("date")->second;

		string providerName = argvals.find("provider")->second;
		provider = mpa::Provider::getProvider( getAccount().id , providerName );

		amount = StrUtil::string2float( argvals.find("amount")->second );

		string categoryName = argvals.find("category")->second;
		category = mpa::Category::getCategory( getAccount().id , categoryName );

		ret = true;
	}

	//MPA_LOG_TRIVIAL(trace, "Return: " + StrUtil::bool2string( ret ) );

	return ret;
}

bool Operation::arePostDeleteParametersOk()
{
	bool ret = false;

	if( isUrlPathValid() && MPAO::arePostDeleteParametersOk() )	ret = true;

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

	ptree operationsChildren;

	bool orderAsc = true;
	vector<mpapo::Operation> operations = getAccount().operations().get( mpapo::Operation::Date > getDate() ).orderBy( mpapo::Operation::Date , orderAsc ).all();
	for (vector<mpapo::Operation>::iterator it = operations.begin(); it != operations.end(); it++)
	{
		//MPA_LOG_TRIVIAL(trace, "" );

		// Get operation
		mpapo::Operation operation = (*it);
		// Get sub operations list
		vector<mpapo::OperationDetail> OperationDetails = operation.operationDetails().get().all();

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

		ptree operationDetailsChildren;

		//MPA_LOG_TRIVIAL(trace, "" );

		//For now there is only one OperationDetail
		for (vector<mpapo::OperationDetail>::iterator itSub = OperationDetails.begin(); itSub != OperationDetails.end(); itSub++)
		{
			//MPA_LOG_TRIVIAL(trace, "" );
			mpapo::OperationDetail OperationDetail = (*itSub);
			ptree OperationDetailPtree;
			OperationDetailPtree.put("id", OperationDetail.id);
			OperationDetailPtree.put("version", OperationDetail.version);

			string categoryString = "";
			litesql::DataSource<mpapo::Category> categoryDatasource = OperationDetail.category().get();
			if( categoryDatasource.count() > 0  )	categoryString = categoryDatasource.one().name;
			OperationDetailPtree.put("category", categoryString );

			OperationDetailPtree.put("note", OperationDetail.note);
			OperationDetailPtree.put("amount", OperationDetail.amount);

			operationDetailsChildren.push_back(std::make_pair("", OperationDetailPtree));
		}

		operationPtree.add_child("details", operationDetailsChildren);
		operationsChildren.push_back(std::make_pair("", operationPtree));

		ret = MPAO::OK_JSON_ID;
	}

	root.add_child("operations", operationsChildren);

	return ret;
}

string Operation::executePostAddRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	string note = argvals.find("note")->second;

	// TODO : verify how it works in multithread
	MPA::getInstance()->getMPAPO().begin();

	// Default case if there is no operation
	float accountBalance = 0;

	// Get all operation where balance must be updated
	bool firstToGetBalance = false;
	bool orderAsc = true;
	vector<mpapo::Operation> operations = getAccount().operations().get( mpapo::Operation::Date > getDate() ).orderBy( mpapo::Operation::Date , orderAsc ).all();
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
		operation.addToBalance( getAmount() );
		operation.update();
	}

	// Update account balance with operation amount
	accountBalance += getAmount();

	//MPA_LOG_TRIVIAL(trace,"");

	// Create OperationDetail
	mpapo::OperationDetail OperationDetail( MPA::getInstance()->getMPAPO() );
	OperationDetail.initializeVersion();
	OperationDetail.setAmount( getAmount() );
	OperationDetail.setNote( note );
	OperationDetail.update();

	// Create Operation
	mpapo::Operation operation( MPA::getInstance()->getMPAPO() );
	operation.initializeVersion();
	operation.setDate( getDate() );
	operation.setAccountBalance( accountBalance );
	// Give operation available
	operation.update();

	// Link OperationDetail to Operation
	operation.operationDetails().link( OperationDetail );
	// Link provider to operation
	operation.provider().link( getProvider() );
	// Link category to OperationDetail
	OperationDetail.category().link( getCategory() );
	// Link operation to account
	getAccount().operations().link( operation );

	// Update amounts and balance
	operation.addToAmount( getAmount() );


	MPA::getInstance()->getMPAPO().commit();

	// Get account ID
	ret = string( operation.id );

	// Generate Json output
	root.push_back(BoostHelper::make_pair("version", operation.version ));
	root.push_back(BoostHelper::make_pair("accountBalance", operation.accountBalance ));

	return ret;
}

string Operation::executePostDeleteRequest(ptree & root)
{
	string ret = MPAO::DEFAULT_JSON_ID;

	/*int categoryId = urlPairs[1].second;
	int categoryVersion = atoi( argvals.find("version")->second );

	try
	{
		mpapo::Category category = Category::getCategory(getAccountId() , categoryId);

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

mpapo::Account & Operation::getAccount()
{
	return account;
}

string & Operation::getDate()
{
	return date;
}

mpapo::Provider & Operation::getProvider()
{
	return provider;
}

float Operation::getAmount()
{
	return amount;
}

mpapo::Category & Operation::getCategory()
{
	return category;
}

Operation::~Operation()
{
}

} /* namespace mpa */
