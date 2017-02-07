#include <com/cyosp/helpers/BoostHelper.hpp>

pair<const string, basic_ptree<string, string>> BoostHelper::make_pair(const string & key, const string & data)
{
	pair<const string, basic_ptree<string, string>> ret( key , data );

    return ret;
}
