/*
 * ResourceBundle.cpp
 *
 *  Created on: 2017-02-16
 *      Author: CYOSP
 */

#include "ResourceBundle.hpp"

namespace cyosp_i18n
{

ResourceBundle::ResourceBundle( string i18nDirectory )
{
	// Regular expression in order to select only info files
	const boost::regex i18nFilePathNameRegex( ".*/(.*)\.info$" );
	boost::smatch matches;

	// Check argument is a directory
	if( is_directory( i18nDirectory ) )
	{
		// Iterate directory content
		for( auto & entry : boost::make_iterator_range( directory_iterator( i18nDirectory ), {}) )
		{
			string entryFilePath = entry.path().string();

			// Check if it's an info file
			if( is_regular_file( entry ) && boost::regex_match( entryFilePath , matches, i18nFilePathNameRegex ) )
			{
				// Parse info file
				ptree pt;
				info_parser::read_info( entryFilePath , pt);

				// Add translation ptree to the list
				translationList.insert( pair<string, ptree>( matches[1] , pt ) );
			}
		}
	}
}

string ResourceBundle::translate( string key , string locale )
{
	string ret = key;

	try
	{
		map<string, ptree>::iterator it = translationList.find( locale );
		if( it != translationList.end() )
		{
			ret = it->second.get<string>( key );
		}
	}
	catch(exception & e)
	{
		// If there is no translation available, key is used as translated string
	}

	return ret;
}

vector<string> ResourceBundle::getLocales()
{
	vector<string> ret;

	pair<string, ptree> pairStringPtree;
	BOOST_FOREACH(pairStringPtree, translationList)	ret.push_back(pairStringPtree.first);

	return ret;
}

ResourceBundle::~ResourceBundle()
{}

} /* namespace cyosp_i18n */
