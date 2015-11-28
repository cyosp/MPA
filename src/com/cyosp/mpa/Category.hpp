/*
 * Category.hpp
 *
 *  Created on: 25 March 2015
 *      Author: cyosp
 */

#ifndef MPA_CATEGORY_HPP_
#define MPA_CATEGORY_HPP_

#include "com/cyosp/helpers/StrUtil.hpp"

#include "com/cyosp/mpa/Account.hpp"
#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/MPAO.hpp"
#include "com/cyosp/mpa/MPAPO.hpp"

namespace mpa
{

class Category: public MPAO
{
private:
	static vector<mpapo::Category> getCategories( int accountId );
	void remove( int accountId , int categoryId , int version );

protected:
	bool areGetParametersOk();
	bool arePostAddParametersOk();
	bool arePostDeleteParametersOk();
	bool arePostUpdateParametersOk();

	string executeGetRequest(ptree & root);
	string executePostAddRequest(ptree & root);
	string executePostDeleteRequest(ptree & root);
	string executePostUpdateRequest(ptree & root);

public:
	Category(HttpRequestType httpRequestType, ActionType actionType, const map<string, string>& argvals , bool isAdmin, vector<std::pair<string, int> > urlPairs );

	static int getCategoryId( int accountId , string categoryName );
	static mpapo::Category getCategory( int accountId , string categoryName );
	static mpapo::Category getCategory( int categoryId );
	static mpapo::Category rename( int accountId , int categoryId, int categoryVersion , string newName );

	virtual ~Category();
};

} /* namespace mpa */

#endif /* MPA_CATEGORY_HPP_ */
