#ifndef __MPA_BOOSTHELPER__
#define __MPA_BOOSTHELPER__

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <utility>

using boost::property_tree::basic_ptree;
using std::string;
using std::pair;

class BoostHelper
{
	public:
		static pair<const string, basic_ptree<string, string>> make_pair(const string & key, const string & data);
};

#endif
