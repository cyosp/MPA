/*
 * HTTPHandler.hpp
 *
 *  Created on: 2 June 2014
 *      Author: cyosp
 */

#ifndef INCLUDES_HTTPHANDLER_HPP_
#define INCLUDES_HTTPHANDLER_HPP_

#include "com/cyosp/helpers/StrUtil.hpp"

#include "com/cyosp/json/JSONHelper.hpp"

#include "com/cyosp/mpa/MPA.hpp"
#include "com/cyosp/mpa/MPAO.hpp"
#include "com/cyosp/mpa/api/rest/v1/MPAOFactory.hpp"

using namespace mpa;

#include <pthread.h>
#include <microhttpd.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <boost/algorithm/string/predicate.hpp> //boost::starts_with

// struct stat buf;
 #include <sys/stat.h>

using std::map;
using std::string;
using std::cout;

// Very generic : to remove
using namespace std;

#include <boost/log/trivial.hpp>

#include <map>
using std::map;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>



#include <unistd.h>	// basename
//#include <libgen.h> // => dirname


// ssize_t
#include <sys/types.h>

// uint64_t
#include <stdint.h>

// MHD declaration
#include <microhttpd.h>

#include "arpa/inet.h"

#include "com/cyosp/helpers/FileHelper.hpp"

// With a value > 1 => enable multithread activation
#define MHD_OPTION_THREAD_POOL_SIZE 1

#define MAXNAMESIZE     1024
#define POSTBUFFERSIZE  1024
#define MAXANSWERSIZE   1024
//#define GET             0
//#define POST            1

#define PAGE "<html><head><title>Error</title></head><body>Bad data</body></html>"
#define PAGE_NOT_FOUND "<html><head><title>404 - File not found</title></head><body>404 - File not found</body></html>"

struct connection_info_struct
{
	int connectiontype;
	map<string, string> * datas;
	struct MHD_PostProcessor *postprocessor;
};

class HTTPHandler
{
private :
	static int shouldNotExit;
	static map<string, bool> * tokenList;

public:
	static void handle_sig_term(int signo);

	static void* http(void *arg);

	static int url_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls);

	static ssize_t file_reader(void *cls, uint64_t pos, char *buf, size_t max);
	static void free_callback(void *cls);
	static int get_url_args(void *cls, MHD_ValueKind kind, const char *key, const char* value);
	static int iterate_post(void *coninfo_cls, enum MHD_ValueKind kind, const char *key, const char *filename, const char *content_type, const char *transfer_encoding, const char *data, uint64_t off, size_t size);

	static int on_client_connect (void *cls, const struct sockaddr *addr, socklen_t addrlen);

	static int serveFile( string filePath , void ***con_cls , MHD_Response **response );
	static string isSessionRegistered(const map<string, string>& argvals);
	static string registerNewSession( bool isAdmin );
	static bool deleteSession( string token );
	static bool isSessionAdmin(string token);

	static void getFactoryMPAObject(HttpRequestType requestType, const string& url, const map<string, string>& argvals, bool isAdmin, string& response );
};

#endif /* HTTPHANDLER_HPP_ */
