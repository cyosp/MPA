/*
 * JSONHelper.cpp
 *
 *  Created on: 2 June 2014
 *      Author: cyosp
 */
#include "com/cyosp/json/JSONHelper.hpp"

#include <sstream>
using std::ostringstream;

// Allow to have JSON in UTF-8 instead of UTF-16
#include "com/cyosp/boost/JSON_PARSER_WRITE.hpp"

void JSONHelper::generateJSON( ptree * propertyTree ,  string & jsonString )
{
	ostringstream ostr;

	write_json( ostr , * propertyTree , false );

	jsonString = ostr.str();
}




