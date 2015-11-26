/*
 * JSONHelper.hpp
 *
 *  Created on: 2 June 2014
 *      Author: cyosp
 */

#ifndef JSONHELPER_HPP_
#define JSONHELPER_HPP_

#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

#include <boost/property_tree/json_parser.hpp>

#include <string.h>
using std::string;

class JSONHelper
{
public :
	static void generateJSON( ptree * propertyTree ,  string & jsonString );
};


#endif /* JSONHELPER_HPP_ */
