#ifndef __MPA_FILEHELPER__
#define __MPA_FILEHELPER__

#include <com/cyosp/mpa/MPA.hpp>
#include <iostream>
#include <string>
#include <sys/stat.h>

using std::endl;
using std::string;

class FileHelper
{
	public:
		const static int FILE_NOT_EXIST;

		static int existFile( string& input );
};
#endif
