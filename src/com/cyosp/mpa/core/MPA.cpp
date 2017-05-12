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

const string MPA::DEFAULT_LOCALE = "en";

// Security constraints
const int MPA::PWD_SECURITY_MIN_SIZE = 6;
const int MPA::PWD_SECURITY_UPPER_CASE_NBR = 1;
const int MPA::PWD_SECURITY_DIGIT_NBR = 1;
const int MPA::PWD_SECURITY_ERROR_NBR = 3;

// Initialize static member
MPA * MPA::mpa = NULL;

MPA * MPA::getInstance()
{
    if( mpa == NULL )
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
    resourceBundle = NULL;
}

void MPA::initDatabase(string dbFilePath)
{
    // using SQLite3 as backend
    mpapo = new MPAPO("sqlite3", "database=" + dbFilePath);

    // create tables, sequences and indexes
    // db.verbose = true;

    // Update database scheme if needed
    if( getMPAPO().needsUpgrade() )
        getMPAPO().upgrade();
}

void MPA::initWWWFilePath(string wwwFilePath)
{
    this->wwwFilePath = wwwFilePath;
}

void MPA::initLogFilePath(string logFilePath)
{
    boost::shared_ptr<sinks::synchronous_sink<sinks::text_file_backend> > sink = logging::add_file_log(
            keywords::file_name = logFilePath,    // "sample_%N.log",
            // Rotation file every 1Mo or at midnight
            keywords::rotation_size = 1 * 1024 * 1024,
            // Rotation file every 1Mo or at midnight
            keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), keywords::auto_flush = true,
            keywords::open_mode = (std::ios::out | std::ios::app),

            keywords::format = (expr::stream
                    << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "[%Y-%m-%d %H:%M:%S.%f]") << " "
                    << logging::trivial::severity << " : " << expr::smessage)
            //keywords::format = "%TimeStamp% [%Uptime%] <%Severity%>: %Message%"
                    );

    // The sink will perform character code conversion as needed, according to the locale set with imbue()
    std::locale loc = boost::locale::generator()("fr_FR.UTF-8");
    sink->imbue(loc);

    logging::add_common_attributes();
    //logging::core::get()->add_global_attribute("Uptime", attrs::timer());

    if( !getDebugMode() )
    {
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
    }

    MPA_LOG_TRIVIAL(info, startMsg);
    MPA_LOG_TRIVIAL(info, "Logging system initialized");
}

void MPA::initI18n(string i18nDirectory)
{
    resourceBundle = new ResourceBundle(i18nDirectory);
}

MPAPO & MPA::getMPAPO()
{
    return *mpapo;
}

const string & MPA::getWWWFilePath() const
{
    return wwwFilePath;
}

vector<mpapo::User> MPA::getAdminUsers()
{
    return select<mpapo::User>(getMPAPO(), mpapo::User::IsAdmin == true).all();    //.orderBy(mpapo::Account::Name).all();
}

vector<mpapo::User> MPA::getUsers()
{
    return select<mpapo::User>(getMPAPO()).all();
}

// There is an exception if user not found
mpapo::User MPA::getUser(string login)
{
    return select<mpapo::User>(getMPAPO(), mpapo::User::Login == login).one();
}

// Get user by ID
mpapo::User MPA::getUser(int id)
{
    return select<mpapo::User>(getMPAPO(), mpapo::User::Id == id).one();
}

bool MPA::existUser(string login)
{
    return select<mpapo::User>(getMPAPO(), mpapo::User::Login == login).all().size() != 0;
}

mpapo::User & MPA::addUser(bool isAdmin, string login, string password, string locale)
{
    mpapo::User * ret = NULL;

    ret = new mpapo::User(getMPAPO());
    ret->initializeVersion();
    ret->setIsAdmin(isAdmin);
    ret->setLogin(login);
    ret->setPassword(password);
    ret->setLocale(locale);
    ret->update();

    MPA_LOG_TRIVIAL(info, "User added, id=" + (*ret).id.value());

    return *ret;
}

bool MPA::delUser(int id, int version)
{
    bool ret = false;

    MPA_LOG_TRIVIAL(trace,
            "User to delete:" + StrUtil::int2string(id) + " with version: " + StrUtil::int2string(version));

    try
    {
        mpapo::User userToDel = getUser(id);

        if( userToDel.isCorrectVersion(version) )
        {
            MPA_LOG_TRIVIAL(trace, "User found");

            beginTransaction();
            userToDel.del();
            commitTransaction();
        }
        else
            throw mpa_exception::MsgNotTranslated(OPERATION_IMPOSSIBLE_BECAUSE_DATA_HAVE_CHANGED);
    }
    catch( NotFound & e )
    {
        throw mpa_exception::MsgNotTranslated(ACCOUNT_DOESNT_EXIST);
    }

    return ret;
}

bool MPA::isSecurePwd(const string pwd)
{
    bool ret = false;

    int pwdSize = pwd.size();

    if( pwdSize >= MPA::PWD_SECURITY_MIN_SIZE )
    {
        int pwdUpperNbr = 0;
        int pwdNDigitNbr = 0;
        for(int i = 0 ; i < pwdSize ; i++)
        {
            if( isupper(pwd[i]) )
                pwdUpperNbr++;
            if( isdigit(pwd[i]) )
                pwdNDigitNbr++;
        }

        if( pwdUpperNbr >= MPA::PWD_SECURITY_UPPER_CASE_NBR && pwdNDigitNbr >= MPA::PWD_SECURITY_DIGIT_NBR )
            ret = true;
    }

    return ret;
}

bool MPA::isAdminRegistered() const
{
    return MPA::getInstance()->getAdminUsers().size() > 0;
}

ResourceBundle & MPA::getResourceBundle()
{
    return *resourceBundle;
}
