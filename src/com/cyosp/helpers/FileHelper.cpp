#include <com/cyosp/helpers/FileHelper.hpp>

const int FileHelper::FILE_NOT_EXIST = -1;

// Return file size if file exist, -1 otherwise
int FileHelper::existFile( string& filePath )
{
	int ret = FileHelper::FILE_NOT_EXIST;

	struct stat buf;

	string logMsg = string( __FUNCTION__ ) + string( " File " );


	if( stat( filePath.c_str(), & buf ) == 0 )
	{
		logMsg.append( "exists" );
		ret = buf.st_size;
	}
	else
	{
		logMsg.append( "doesn't exist" );
	}

	MPA_LOG_TRIVIAL(trace, logMsg + ": " + filePath );

	return ret;
}
