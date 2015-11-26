#ifndef __OUR_STRUTILS__
#define __OUR_STRUTILS__

#include <string>
#include <vector>

#include <sstream>
#include <string>
using std::ostringstream;

using std::vector;
using std::string;

class StrUtil
{
public:
	static void eraseWhiteSpace(string& input);
	static void eraseAllChars(string& input, const char *chars_to_erase);
	static void splitString(const string& input, const char* delims,
			vector<string>& tokens);
	static string float2string(float f);
	static string int2string(int i);
	static string bool2string(bool b);
	static float string2float( string s );
};
#endif
