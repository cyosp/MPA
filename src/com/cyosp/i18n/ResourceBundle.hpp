/*
 * ResourceBundle.hpp
 *
 *  Created on: 2017-02-16
 *      Author: CYOSP
 */

#ifndef COM_CYOSP_I18N_RESOURCEBUNDLE_HPP_
#define COM_CYOSP_I18N_RESOURCEBUNDLE_HPP_

#include <map>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/regex.hpp>

using namespace std;
using namespace boost::filesystem;
using namespace boost::property_tree;

namespace cyosp_i18n
{

class ResourceBundle
{
	private:
		map<string, ptree> translationList;

	public:
		ResourceBundle( string i18nDirectory );
		string translate( string key , string locale );
		virtual ~ResourceBundle();
};

} /* namespace cyosp_i18n */

#endif /* COM_CYOSP_I18N_RESOURCEBUNDLE_HPP_ */
