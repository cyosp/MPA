#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include <com/cyosp/helpers/StrUtil.hpp>

void StrUtil::eraseWhiteSpace(string& val)
{
    boost::erase_all(val," ");
    boost::erase_all(val,"\n");
    boost::erase_all(val,"\t");
    boost::erase_all(val,"\r");
}

void StrUtil::eraseAllChars(string& val, const char *chars_to_erase)
{
    if (!chars_to_erase)
        return;

    vector<string> tokens;
    boost::split(tokens, val, boost::is_any_of(chars_to_erase), boost::token_compress_on ); 
    val = "";
    BOOST_FOREACH(string a, tokens) {
        val += a;
    }
}

void StrUtil::splitString(const string& input, const char* delims,
        vector <string>& tokens)
{
    string temp = input;
    boost::trim_if(temp, boost::is_any_of(delims));
    boost::split( tokens, temp, boost::is_any_of(delims), boost::token_compress_on ); 
}

string StrUtil::float2string(float f)
{
  ostringstream os;
  os << f;
  return os.str();
}

string StrUtil::int2string(int i)
{
  ostringstream os;
  os << i;
  return os.str();
}

string StrUtil::bool2string(bool b)
{
	return (b ? "true" : "false" );
}

float StrUtil::string2float( string s )
{
	std::stringstream ss;
	float f;
	ss.str( s );
	ss >> f;

	return f;
}

