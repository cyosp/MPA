/*
 * MPA.hpp
 *
 *  Created on: 7 February 2014
 *      Author: cyosp
 */

#ifndef MPA_HPP_
#define MPA_HPP_

#include <vector>
#include <string>
#include <fstream>		// std::ofstream


#include "litesql.hpp"
#include "com/cyosp/mpa/MPAPO.hpp"
#include "com/cyosp/helpers/StrUtil.hpp"
// no name collisions expected
using namespace litesql;
using namespace mpapo;

using std::vector;
using std::string;
using std::ofstream;

#include "boost/log/trivial.hpp"
#define MPA_LOG_TRIVIAL( level , msg ) \
	do \
		if( MPA::getInstance()->getDebugMode() ) BOOST_LOG_TRIVIAL( level ) << __FILE__ << "@line=" << __LINE__ << " : " << msg << endl; \
		else BOOST_LOG_TRIVIAL( level ) << msg << endl;\
	while(0)
// Can be used if needed: __FUNCTION__ => give method name

// Define messages code
static const int MSG_OK = 0;
static const int MSG_DEL_IMPOSSIBLE_OPERATIONS = 22;
static const int MSG_DEL_IMPOSSIBLE_PROVIDERS = 23;
static const int MSG_DEL_IMPOSSIBLE_CATEGORIES = 24;
static const int MSG_NO_SYSTEM_ACCOUNT = 25;

class MPA
{
	public:

		const static string version;
		const static string startMsg;

		const static string DEFAULT_ADMIN_PWD;

		const static int PWD_SECURITY_MIN_SIZE;
		const static int PWD_SECURITY_UPPER_CASE_NBR;
		const static int PWD_SECURITY_DIGIT_NBR;

		// Number of bad password tried
		const static int PWD_SECURITY_ERROR_NBR;

		// Singleton method
		static MPA * getInstance();

		// Get debug mode
		bool getDebugMode();
		// Set debug mode
		void setDebugMode(bool debugMode);

		// Initialize SQL database
		void initDatabase( string dbFilePath );
		void initDatabase( string dbFilePath , string adminLogin );
		// initialize www file path
		void initWWWFilePath( string wwwFilePath );
		// initialize log file path
		void initLogFilePath( string logFilePath);

		// Get persistence object
		MPAPO & getMPAPO();
		// Get WWW file path
		const string & getWWWFilePath() const;

		// Get administrator user
		vector<mpapo::User> getAdminUsers();
		// Get users
		vector<mpapo::User> getUsers();
		// Get user by login
		mpapo::User getUser( string login );
		// Get user by id
		mpapo::User getUser( int id );
		// Del an user
		bool delUser( int id , int version );
		// Check if user exist by login
		bool existUser( string login );
		// Add a user
		mpapo::User & addUser(bool isAdmin, string login , string password);


		static string getErrMsg(int code);

		static bool isSecurePwd( const string pwd );

		bool isAdminRegistered() const;
		void registerAdmin();

	private:
		// Debug mode
		bool debugMode;
		// Singleton member
		static MPA * mpa;
		// administrator is it registered
		bool adminRegistered;
		// Singleton constructor
		MPA();

		// MPA persistence object
		MPAPO * mpapo;
		// WWW file path
		string wwwFilePath;
};

#endif /* MPA_HPP_ */
