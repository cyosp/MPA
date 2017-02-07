/*
 * MPA.cpp
 *
 *  Created on: 7 February 2014
 *      Author: cyosp
 */

#include <com/cyosp/mpa/core/MPA.hpp>

#include <vector>
#include <string>
#include <algorithm>    // std::find
#include <iostream>     // std::cout

#include "litesql.hpp"
#include "com/cyosp/mpa/po/MPAPO.hpp"
// no name collisions expected
using namespace litesql;
using namespace mpapo;

using std::vector;
using std::find;

// log framework
#include <boost/log/trivial.hpp>
// For log into a file
#include <boost/log/utility/setup/file.hpp>
// For attributes
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
// For expressions
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
// Supporting headers
#include <boost/log/support/date_time.hpp>
// Thread headers
#include <boost/log/attributes/current_thread_id.hpp>
// Locale
#include <boost/locale.hpp>
// namespace alias
namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;
namespace expr = boost::log::expressions;

struct addResult
{
	int value;
	string objectId;
};

const string MPA::version = "In progress";
const string MPA::startMsg = "Starting MPA " + version;

// Security constraints
const int MPA::PWD_SECURITY_MIN_SIZE = 6;
const int MPA::PWD_SECURITY_UPPER_CASE_NBR = 1;
const int MPA::PWD_SECURITY_DIGIT_NBR = 1;
const int MPA::PWD_SECURITY_ERROR_NBR = 3;

// TODO : protect in multithread
map<string, bool> * MPA::tokenList = new map<string, bool>;


// Initialize static member
MPA * MPA::mpa = NULL;

MPA * MPA::getInstance()
{
	if (mpa == NULL)
		mpa = new MPA();

	return mpa;
}

// get debug mode
bool MPA::getDebugMode()
{
	return debugMode;
}

// Set debug mode
void MPA::setDebugMode(bool debugMode)
{
	this->debugMode = debugMode;
}

MPA::MPA()
{
	debugMode = false;
	mpa = NULL;
	mpapo = NULL;
	adminRegistered = false;
}

void MPA::initDatabase( string dbFilePath )
{
	// using SQLite3 as backend
	mpapo = new MPAPO( "sqlite3" , "database=" + dbFilePath );


	// create tables, sequences and indexes
	// db.verbose = true;

	// Update database scheme if needed
	if( getMPAPO().needsUpgrade() )	getMPAPO().upgrade();

	/*vector<mpapo::User> adminUsers = getAdminUsers();
	if( adminUsers.size() == 0 )
	{
		mpapo->~Database();
		throw string( "Database started in normal mode without administrator user set in database");
	}
	else	registerAdmin();*/
}

/*void MPA::initDatabase( string dbFilePath , string adminLogin )
{
	// using SQLite3 as backend
	mpapo = new MPAPO( "sqlite3" , "database=" + dbFilePath );

	// create tables, sequences and indexes
	// db.verbose = true;

	// Update database scheme if needed
	if( getMPAPO().needsUpgrade() )	getMPAPO().upgrade();

	vector<mpapo::User> adminUsers = getAdminUsers();
	if( adminUsers.size() == 0 )
	{
		MPA_LOG_TRIVIAL(info,"No administrator user set in database");
		addUser( true , adminLogin , DEFAULT_ADMIN_PWD );
	}
	// TODO : manage here is there is more than one admin account
	else
	{
		mpapo->~Database();
		throw string( "Database started with admin login whereas there is already one registered" );
	}
}*/

void MPA::initWWWFilePath( string wwwFilePath )
{
	this->wwwFilePath = wwwFilePath;
}


void MPA::initLogFilePath( string logFilePath )
{
	boost::shared_ptr< sinks::synchronous_sink< sinks::text_file_backend > > sink =  logging::add_file_log
	(
		keywords::file_name = logFilePath,	// "sample_%N.log",
		// Rotation file every 1Mo or at midnight
		keywords::rotation_size = 1 * 1024 * 1024,
		// Rotation file every 1Mo or at midnight
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
		keywords::auto_flush = true,
		keywords::open_mode = (std::ios::out | std::ios::app),

		keywords::format =
		(
			expr::stream << expr::format_date_time< boost::posix_time::ptime >( "TimeStamp" , "[%Y-%m-%d %H:%M:%S.%f]" )
						 << " " << logging::trivial::severity
						 << " : " << expr::smessage
		)
		//keywords::format = "%TimeStamp% [%Uptime%] <%Severity%>: %Message%"
	);

	// The sink will perform character code conversion as needed, according to the locale set with imbue()
	std::locale loc = boost::locale::generator()("fr_FR.UTF-8");
	sink->imbue(loc);

	logging::add_common_attributes();
	//logging::core::get()->add_global_attribute("Uptime", attrs::timer());

	if( ! getDebugMode() )
	{
		logging::core::get()->set_filter
		(
			logging::trivial::severity >= logging::trivial::info
		);
	}

	MPA_LOG_TRIVIAL(info,startMsg);
	MPA_LOG_TRIVIAL(info, "Logging system initialized");
}

MPAPO & MPA::getMPAPO()
{
	return * mpapo;
}

const string & MPA::getWWWFilePath() const
{
	return wwwFilePath;
}

vector<mpapo::User> MPA::getAdminUsers()
{
	return select<mpapo::User>( getMPAPO() , mpapo::User::IsAdmin == true ).all();	//.orderBy(mpapo::Account::Name).all();
}

vector<mpapo::User> MPA::getUsers()
{
	return select<mpapo::User>( getMPAPO() ).all();
}

// There is an exception if user not found
mpapo::User MPA::getUser( string login )
{
	return select<mpapo::User>( getMPAPO() , mpapo::User::Login == login ).one();
}

// Get user by ID
mpapo::User MPA::getUser( int id )
{
	return select<mpapo::User>( getMPAPO() , mpapo::User::Id == id ).one();
}

bool MPA::existUser( string login )
{
	return select<mpapo::User>( getMPAPO() , mpapo::User::Login == login ).all().size() != 0;
}

mpapo::User & MPA::addUser(bool isAdmin, string login , string password)
{
	mpapo::User * ret = NULL;

	ret = new mpapo::User( getMPAPO() );
	ret->initializeVersion();
	ret->setIsAdmin( isAdmin );
	ret->setLogin(login);
	ret->setPassword(password);
	ret->update();

	MPA_LOG_TRIVIAL(info,"User added, id=" + (* ret).id.value());

	if( isAdmin )	registerAdmin();

	return * ret;
}

bool MPA::delUser(int id , int version )
{
	bool ret = false;

	MPA_LOG_TRIVIAL(trace,"User to delete:" + StrUtil::int2string( id )+" with version: " + StrUtil::int2string(version ));

	try
	{
		mpapo::User userToDel = getUser( id );

		if( userToDel.isCorrectVersion( version ) )
		{
			MPA_LOG_TRIVIAL(trace,"User found");

			// Only non admin users can be deleted
			if( ! userToDel.isAdmin )
			{
				getMPAPO().begin();
				userToDel.del();
				getMPAPO().commit();
			}
			else  throw getErrMsg( 13 );
		}
		else throw getErrMsg( 4 );
	}
	catch (NotFound & e)
	{
		throw getErrMsg( 2 );
	}

	return ret;
}

//	mpapo::Object a =new mpapo::Object(getMPAPO() );
//a.getNextObject();


string MPA::getErrMsg(int code)
{
	string ret = "";

	switch (code)
	{
	case MSG_OK: ret = "Ok";
			break;

	case 1: ret = "Un compte avec le même nom existe déjà";
		break;
	case 2: ret = "Le compte n'existe pas";
		break;
	// System case => message in English
	case 3: ret = "Missing parameters";
		break;
	case 4: ret = "Opération impossible car les données ont changé depuis leur récupération";
		break;
	// System case => message in English
	case 5: ret = "URL conversion failure";
			break;
	case 6: ret = "Identifiant incorrect";
				break;
	case 7: ret = "Mot de passe incorrect";
			break;
	case 8: ret = "Les mots de passes ne correspondent pas";
			break;
	case 9: ret = "La sécurité du mot de passe est trop failble. Il doit respecter les critères suivants: taille >=" + StrUtil::int2string( MPA::PWD_SECURITY_MIN_SIZE ) + ", majuscule(s) >=" + StrUtil::int2string( MPA::PWD_SECURITY_UPPER_CASE_NBR ) + ", chiffre(s) >=" + StrUtil::int2string( MPA::PWD_SECURITY_DIGIT_NBR );
				break;
	case 10: ret = "L'utilisateur existe déjà";
				break;
	case 11: ret = "Le compte utilisateur est bloqué";
				break;
	case 12: ret = "L'utilisateur n'existe pas";
				break;
	case 13: ret = "L'utilisateur administrateur ne peut pas être supprimé";
				break;
	case 20: ret = "Une category avec le même nom existe déjà";
			break;
	// System case => message in English
	case 21: ret = "Bad URL";
		break;
	case MSG_DEL_IMPOSSIBLE_OPERATIONS: ret = "Suppression impossible car il existe encore des opérations";
		break;
	case MSG_DEL_IMPOSSIBLE_PROVIDERS: ret = "Suppression impossible car il existe encore des tiers";
		break;
	case MSG_DEL_IMPOSSIBLE_CATEGORIES: ret = "Suppression impossible car il existe encore des categories";
		break;
	case MSG_NO_SYSTEM_ACCOUNT: ret = "Administrator account is not defined";
		break;

	default:
		break;
	}

	return ret;
}

bool MPA::isSecurePwd( const string pwd )
{
	bool ret = false;

	int pwdSize = pwd.size();


	if( pwdSize >= MPA::PWD_SECURITY_MIN_SIZE )
	{
		int pwdUpperNbr = 0;
		int pwdNDigitNbr = 0;
		for (int i = 0; i < pwdSize; i++)
		{
			if( isupper( pwd[i] ) )	pwdUpperNbr++;
			if( isdigit( pwd[i] ) ) pwdNDigitNbr++;
		}

		if( pwdUpperNbr >= MPA::PWD_SECURITY_UPPER_CASE_NBR && pwdNDigitNbr >= MPA::PWD_SECURITY_DIGIT_NBR ) ret = true;
	}

	return ret;
}

bool MPA::isAdminRegistered() const
{
	return adminRegistered;
}

void MPA::registerAdmin()
{
	adminRegistered = true;
}
