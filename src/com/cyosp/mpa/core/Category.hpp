/*
 * Category.hpp
 *
 *  Created on: 25 March 2015
 *      Author: cyosp
 */

#ifndef MPA_API_CATEGORY_HPP_
#define MPA_API_CATEGORY_HPP_

#include "com/cyosp/helpers/StrUtil.hpp"

#include "com/cyosp/mpa/core/Account.hpp"
#include "com/cyosp/mpa/core/MPA.hpp"
#include "com/cyosp/mpa/po/MPAPO.hpp"

namespace mpa
{

class Category
{
public:
	static vector<mpapo::Category> getCategories( int accountId );
	static void remove( int accountId , int categoryId , int version );
	static int getCategoryId( int accountId , string categoryName );
	static mpapo::Category getCategory( int accountId , string categoryName );
	static mpapo::Category getCategory( int categoryId );
	static mpapo::Category rename( int accountId , int categoryId, int categoryVersion , string newName );

	virtual ~Category();
};

} /* namespace mpa */

#endif
