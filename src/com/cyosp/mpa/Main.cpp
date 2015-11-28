/*
 * Main.cpp
 *
 *  Created on: 2 June 2014
 *      Author: cyosp
 */

#include "com/cyosp/rest/HTTPHandler.hpp"

#include <iostream>
#include <libgen.h> // => dirname
#include <com/cyosp/rest/Platform.h>	// signal function
#include <string>

using std::cout;
using std::endl;
using std::string;


int main(int argc, char * const *argv)
{
	int returnCode = 0;

	if( argc != 4 && argc != 5 )
	{
		printf( "%s <PORT> <DB_FILE_PATH> <LOG_FILE_PATH> [ADMIN_LOGIN]\n" , argv[0] );
		exit( 1 );
	}

	cout << MPA::startMsg << endl;

	//string programName = argv[0];
	string portNumber = argv[1];
	int port = atoi( portNumber.c_str() );
	string dbFilePath = argv[2];
	string logFilePath = argv[3];

	string adminLogin = "";
	if( argc == 5 )
	{
		adminLogin = argv[4];
		cout << "Admin login: " << adminLogin << endl;
	}

	// Get program absolute path
	char programAbsoluteFilePath[1024];
	ssize_t prgFilePathLength = readlink("/proc/self/exe", programAbsoluteFilePath, sizeof(programAbsoluteFilePath)-1);
	programAbsoluteFilePath[prgFilePathLength] = '\0';
	// Get program directory
	string programDirectory = string( programAbsoluteFilePath );

	// Get www file path
	string wwwFilePath = string( dirname( programAbsoluteFilePath ) ) + "/" + ".." + "/" + "www" ;	//TODO : Generate dynamically FS following OS

	// Get debug file path
	string debugFilePath = programDirectory + ".debug";
	cout << "Search for debug file: " + debugFilePath << endl;

	bool debugMode = FileHelper::existFile( debugFilePath ) != FileHelper::FILE_NOT_EXIST;

	cout << "Debug mode: " << debugMode << endl;

	bool canContinue = false;
	try
	{
		MPA * mpa = MPA::getInstance();
		mpa->setDebugMode(debugMode);
		mpa->initLogFilePath( logFilePath );
		if( argc == 5 )			mpa->initDatabase( dbFilePath , adminLogin );
		else if( argc == 4 )	mpa->initDatabase( dbFilePath );
		mpa->initWWWFilePath( wwwFilePath );

		canContinue = true;
	}
	catch (const std::string & msg)
	{
		returnCode = 1;
		cout << "ERROR => " << msg << endl;
	}

	if( canContinue )
	{
		daemon( 0 , 0 );
		signal( SIGTERM , HTTPHandler::handle_sig_term );
		pthread_t thread;
		if (0 != pthread_create( & thread , 0 , HTTPHandler::http , & port ) )	exit( 2 );
		pthread_join(thread, 0);
	}

	return returnCode;
}
