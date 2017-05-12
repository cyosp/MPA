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
		//Category( int id );

		// Get all entries linked to an account
		static vector<mpapo::Category> all( int accountId );
		// Delete an entry
		static void del( int categoryId , int version );

		// Get an entry and create it if necessary
		static mpapo::Category get( int accountId , string name );
		// Get an entry
		static mpapo::Category get( int id );


		static mpapo::Category rename( int accountId , int id , int version , string newName );

		virtual ~Category();

	//private:
		static int getCategoryId( int accountId , string categoryName );
};

} /* namespace mpa */

#endif
