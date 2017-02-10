#include "com/cyosp/rest/HTTPHandler.hpp"

int HTTPHandler::shouldNotExit = 1;

// Manage SIGTERM
void HTTPHandler::handle_sig_term( int signalNumber )
{
	shouldNotExit = 0;
}

void * HTTPHandler::http( void *arg )
{
	int * port = (int *) arg;

	struct MHD_Daemon *d;

	d = MHD_start_daemon(
			MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_POLL, *port, &on_client_connect,
			0, &url_handler, (void *) PAGE, MHD_OPTION_END);
	if (d == 0)
	{
		return 0;
	}

	while (shouldNotExit)
	{
		sleep(1);
	}

	MHD_stop_daemon(d);

	return 0;
}

#include "com/cyosp/helpers/NetHelper.hpp"
int HTTPHandler::on_client_connect (void *cls, const struct sockaddr *addr, socklen_t addrlen)
{
	// Another way to get client IP address with connection parameter

	MPA_LOG_TRIVIAL(info, "Client IP address: "+ NetHelper::getIpAddr(addr) );

	return MHD_YES;
}


int HTTPHandler::url_handler(void *cls, struct MHD_Connection *connection,
		const char *url, const char *method, const char *version,
		const char *upload_data, size_t *upload_data_size, void **con_cls)
{
	int ret = MHD_NO;

	const struct sockaddr *addr = MHD_get_connection_info (connection, MHD_CONNECTION_INFO_CLIENT_ADDRESS )->client_addr;
	string remoteIP = NetHelper::getIpAddr(addr);


	//const char *fmt = (const char *) cls;
	const char *val;
	char *me;

	struct MHD_Response *response = NULL;

	map<string, string> url_args;
	map<string, string>::iterator it;
	string respdata;

	string urlString = string( url );

	// Serve file
	if( strcmp(method, "GET") == 0 )
	{
		MPA_LOG_TRIVIAL(info, "Manage GET request: " + urlString );

		if (MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, get_url_args, &url_args) >= 0)
		{
			MPA_LOG_TRIVIAL(debug,"Parameters are ok");

			//string token = mpa_api_rest_v1::MPAOFactory::getInstance()->isTokenRegistered( url_args );
			//bool isAdmin = mpa_api_rest_v1::MPAOFactory::getInstance()->isTokenAdmin( token );
			// Session is not registered
			/*if( token.empty() )
			{
				if( urlString == "/" )
				{
					string filePath = MPA::getInstance()->getWWWFilePath() + urlString;
					if( ! MPA::getInstance()->isAdminRegistered() )	filePath += "users";
					else											filePath += "login";

					MPA_LOG_TRIVIAL(debug,string( basename( filePath.c_str() ) ) );

					filePath += "/" + string( basename( filePath.c_str() ) ) + ".html";

					ret = serveFile( filePath , & con_cls , & response );
				}
				// Serve www folder
				else if( ! boost::starts_with(url, "/api/") )
				{
					string filePath = MPA::getInstance()->getWWWFilePath() + urlString;
					// Serve file
					ret = serveFile( filePath , &con_cls , &response );
				}
				else
				{
					MPA_LOG_TRIVIAL(info,"Forbidden page => display not found");
					response = MHD_create_response_from_buffer( strlen(PAGE_NOT_FOUND), (void *) PAGE_NOT_FOUND, MHD_RESPMEM_PERSISTENT);
					ret = MHD_HTTP_NOT_FOUND;
				}
			}
			else
			{*/
				/*if( boost::starts_with(url, "/mpa/res-adm") )
				{
					MPA_LOG_TRIVIAL(trace,"JSON request to serve");

					if( isSessionAdmin( session ) )
					{
						HTTPHandler::getFactoryMPAObject( GET , url, url_args, isAdmin , respdata);

						MPA_LOG_TRIVIAL(trace,"callapi.getFactoryMPAObject: done");

						*con_cls = 0; // reset when done
						val = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "q");

						me = (char *) malloc(respdata.size() + 1);
						if( me != 0 )
						{
							strncpy(me, respdata.c_str(), respdata.size() + 1);
							response = MHD_create_response_from_buffer(strlen(me), me, MHD_RESPMEM_MUST_FREE);

							if( response == 0 )	free(me);
							else MHD_add_response_header(response, "Content-Type", "text");	//application/json;charset=UTF-8
							//MHD_add_response_header(response, "OurHeader", "json");
							ret = MHD_HTTP_OK;
						}
					}
				}
				else *//*if( urlString == "/disconnect" )
				{
					//mpa_api_rest_v1::MPAOFactory::getInstance()->deleteToken( token );


					respdata = "<html><head><meta http-equiv='refresh' content='0; url=..'/></head></html>";
					me = (char *) malloc(respdata.size() + 1);
					if( me == 0 )	return MHD_NO;

					strncpy( me , respdata.c_str() , respdata.size() + 1 );
					response = MHD_create_response_from_buffer( strlen( me ) , me , MHD_RESPMEM_MUST_FREE );

					if( response == 0 )	free(me);
					else MHD_add_response_header(response, "Content-Type", "text");	//application/json;charset=UTF-8

					ret = MHD_HTTP_OK;

				}
				else */if( boost::starts_with(url, "/api/rest/") )
				{
					MPA_LOG_TRIVIAL(trace,"JSON request to serve");

					// TODO Manage switch for API versions

					HTTPHandler::getFactoryMPAObject( GET , url, url_args , respdata);

					MPA_LOG_TRIVIAL(trace,"callapi.getFactoryMPAObject: done");

					*con_cls = 0; // reset when done
					val = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "q");

					me = (char *) malloc(respdata.size() + 1);
					if( me != 0 )
					{
						strncpy(me, respdata.c_str(), respdata.size() + 1);
						response = MHD_create_response_from_buffer(strlen(me), me, MHD_RESPMEM_MUST_FREE);

						if( response == 0 )	free(me);
						else MHD_add_response_header(response, "Content-Type", "text");	//application/json;charset=UTF-8
						//MHD_add_response_header(response, "OurHeader", "json");
						ret = MHD_HTTP_OK;
					}
				}
				else
				{
					string filePath = MPA::getInstance()->getWWWFilePath() + urlString;

					// If last character is / => ask for file <basename>.html
					// basename must use a real file path ! and the remove last character, ie the /
					if(  urlString.at( urlString.size() - 1 ) == '/' )	filePath += string( basename( filePath.substr(0,filePath.size()-1).c_str() ) ) + ".html";

					// Serve file
					ret = serveFile( filePath , &con_cls , &response );
				}
			//}
		}
		else
		{
			MPA_LOG_TRIVIAL(info,"Bad data");
			response = MHD_create_response_from_buffer( strlen(PAGE), (void *) PAGE, MHD_RESPMEM_PERSISTENT);
		}

		if( ret != MHD_NO )
		{
			ret = MHD_queue_response(connection, ret, response);
			MHD_destroy_response(response);
		}
	}
	else if( strcmp(method, "POST") == 0 )
	{
		MPA_LOG_TRIVIAL(info, "Manage POST request: " + urlString );

		if( *con_cls == NULL )
		{
			MPA_LOG_TRIVIAL(trace,"*con_cls == NULL");

			struct connection_info_struct *con_info;

			con_info = (connection_info_struct*) malloc(
					sizeof(struct connection_info_struct));

			if (NULL == con_info)
				return MHD_NO;

			con_info->datas = NULL;
			con_info->postprocessor = MHD_create_post_processor(connection,
					POSTBUFFERSIZE, iterate_post, (void*) con_info);
			con_info->connectiontype = POST;

			if (NULL == con_info->postprocessor)	free(con_info);
			else
			{
				*con_cls = (void*) con_info;
				ret = MHD_YES;
			}
		}
		else
		{
			MPA_LOG_TRIVIAL(info,"*con_cls != NULL");

			struct connection_info_struct *con_info =
					(connection_info_struct*) *con_cls;

			MPA_LOG_TRIVIAL(trace,"");

			if (*upload_data_size != 0)
			{
				MPA_LOG_TRIVIAL(trace,"*upload_data_size != 0");

				MHD_post_process(con_info->postprocessor, upload_data,
						*upload_data_size);

				MPA_LOG_TRIVIAL(trace,"");

				*upload_data_size = 0;

				MPA_LOG_TRIVIAL(trace,"");

				ret = MHD_YES;
			}
			else if (con_info->datas != NULL)
			{
				MPA_LOG_TRIVIAL(trace,"con_info->datas != NULL");

				// Display all parameters
				map<string, string>::iterator it = con_info->datas->begin();
				for (it = con_info->datas->begin();
						it != con_info->datas->end(); ++it)

				MPA_LOG_TRIVIAL(trace,it->first + " => " + it->second);

				//string session = mpa_api_rest_v1::MPAOFactory::getInstance()->isTokenRegistered( * con_info->datas );
				//bool isAdmin = mpa_api_rest_v1::MPAOFactory::getInstance()->isTokenAdmin( session );
				// Session is not registered
				//if( session.empty() && urlString != "/api/rest/v1/users/add" && urlString != "/api/rest/v1/users/login" )
				//{
				//	MPA_LOG_TRIVIAL(info,"Request without token");

				//	if( urlString == "/adminRegister/action" )
				//	{
				//		MPA_LOG_TRIVIAL(info,"Registrer administrator");

						//TODO : verify if arg exist before to take value
				//		string login = con_info->datas->find("login")->second;
				//		string pwd = con_info->datas->find("pwd")->second;
				//		string pwdCheck = con_info->datas->find("pwdCheck")->second;

				//		mpapo::User adminUser = MPA::getInstance()->getAdminUsers()[0];

				//		MPA_LOG_TRIVIAL(trace,"Administrator login: " + adminUser.login.value());
				//		MPA_LOG_TRIVIAL(trace,"Administrator password: " + adminUser.password.value());


				//		if( adminUser.login.value().compare(login) == 0 )
				//		{
				//			if( /*adminUser.password.value().compare(MPA::DEFAULT_ADMIN_PWD) == 0 &&*/ pwd.compare(pwdCheck) == 0 )
				//			{
				//				if( MPA::isSecurePwd(pwd ) )
				//				{
				//					MPA_LOG_TRIVIAL(info,"Administrator can be registered");

				//					adminUser.setPassword(pwd);
				//					adminUser.update();
				//					MPA::getInstance()->registerAdmin();

									//string token = mpa_api_rest_v1::MPAOFactory::getInstance()->registerNewToken( MPA::getInstance()->getUser( adminUser.login.value() ) ).getValue();

									//respdata = "<html><head><meta http-equiv='refresh' content='0; url=../mpa/admin/users/?token=" + token + "'/></head></html>";
				//				}
				//				else
				//				{
									// TODO : manage URL encoding
				//					MPA_LOG_TRIVIAL(trace,"Password security is too low");
				//					respdata = "<html><head><meta http-equiv='refresh' content='0; url=../?errMsg="+MPA::getErrMsg( 9 )+"&login="+login + "'/></head></html>";
				//				}
				//			}
				//			else
				//			{
								// Not managed : adminUser.password.value().compare(MPA::DEFAULT_ADMIN_PWD)
								// TODO : manage URL encoding
				//				MPA_LOG_TRIVIAL(trace,"Password doesn't match");
				//				respdata = "<html><head><meta http-equiv='refresh' content='0; url=../?errMsg="+MPA::getErrMsg( 8 )+"&login="+login + "'/></head></html>";
				//			}
				//		}
				//		else
				//		{
				//			MPA_LOG_TRIVIAL(trace,"Register administrator fails");
				//			// TODO : manage URL encoding
				//			respdata = "<html><head><meta http-equiv='refresh' content='0; url=../?errMsg="+MPA::getErrMsg( 6 )+"&login="+login + "'/></head></html>";
				//		}
				//	}
				//}
				//else
				//{
				//	MPA_LOG_TRIVIAL(info,"Request with valid token or login");

				//	bool canContinue = false;

					/*if( boost::starts_with(url, "/mpa/res-adm") )
					{
						MPA_LOG_TRIVIAL(info,"Ask for admin request");
						if( isAdmin )
						{
							MPA_LOG_TRIVIAL(info,"Admin request validated");
							canContinue = true;
						}
					}
				else *///canContinue = true;

				//	if( canContinue )	HTTPHandler::getFactoryMPAObject( POST , url, *con_info->datas, isAdmin , respdata );
				//}

				HTTPHandler::getFactoryMPAObject( POST , url, *con_info->datas , respdata );

				*con_cls = 0; /* reset when done */
				val = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "q");

				me = (char *) malloc(respdata.size() + 1);
				if (me == 0)
					return MHD_NO;

				strncpy(me, respdata.c_str(), respdata.size() + 1);
				response = MHD_create_response_from_buffer(strlen(me), me, MHD_RESPMEM_MUST_FREE);

				if (response == 0)	free(me);
				else
				{
					MPA_LOG_TRIVIAL(trace,"");
					MHD_add_response_header(response, "Content-Type", "text");//application/json;charset=UTF-8
					//MHD_add_response_header(response, "OurHeader", "json");

					MPA_LOG_TRIVIAL(trace,"");
					ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
					MHD_destroy_response(response);
				}
			}
		}
	}

	MPA_LOG_TRIVIAL(trace,"return value="+StrUtil::int2string( ret ));

	return ret;
}

ssize_t HTTPHandler::file_reader(void *cls, uint64_t pos, char *buf, size_t max)
{
	FILE *file = (FILE *) cls;

	(void) fseek(file, pos, SEEK_SET);
	return fread(buf, 1, max, file);
}

void HTTPHandler::free_callback(void *cls)
{
	FILE *file = (FILE *) cls;
	fclose(file);
}

/*
 * IN void *cls => arguments
 * ?? HD_ValueKind kind
 * IN const char *key =>
 *
 * */
int HTTPHandler::get_url_args(void *cls, MHD_ValueKind kind, const char *key, const char* value)
{
	map<string, string> * url_args = static_cast<map<string, string> *>(cls);

	if (url_args->find(key) == url_args->end())
	{
		if (!value)
			(*url_args)[key] = "";
		else
			(*url_args)[key] = value;
	}
	return MHD_YES;

}

/**
 * Iterator over key-value pairs where the value
 * maybe made available in increments and/or may
 * not be zero-terminated.  Used for processing
 * POST data.
 *
 * @param cls user-specified closure
 * @param kind type of the value
 * @param key 0-terminated key for the value
 * @param filename name of the uploaded file, NULL if not known
 * @param content_type mime-type of the data, NULL if not known
 * @param transfer_encoding encoding of the data, NULL if not known
 * @param data pointer to size bytes of data at the
 *              specified offset
 * @param off offset of data in the overall value
 * @param size number of bytes in data available
 * @return MHD_YES to continue iterating,
 *         MHD_NO to abort the iteration
 */
int HTTPHandler::iterate_post(void *coninfo_cls, enum MHD_ValueKind kind,
		const char *key, const char *filename, const char *content_type,
		const char *transfer_encoding, const char *data, uint64_t off,
		size_t size)
{
	struct connection_info_struct *con_info =
			(connection_info_struct*) coninfo_cls;

	if (!con_info->datas)
		con_info->datas = new map<string, string>();

	//if (0 == strcmp(key, "name"))
	{
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			char *answerstring;
			answerstring = (char *) malloc(MAXANSWERSIZE);
			if (!answerstring)
				return MHD_NO;
			const char* greatingpage = "%s";
			snprintf(answerstring, MAXANSWERSIZE, greatingpage, data);

			MPA_LOG_TRIVIAL(trace,"Data received: " + string( answerstring ));

			con_info->datas->insert(pair<string, string>(key, answerstring));

		}
		else
			con_info->datas = NULL;

		return MHD_YES;
	}

	return MHD_YES;
}

// access => #include <unistd.h>
//if( access( "/home/cyosp/tmp/litesql/litesql-src-0.3.17/src/examples/example.db", F_OK ) != -1 ) => file exists

int HTTPHandler::serveFile( string filePath , void ***con_cls , MHD_Response **response )
{
	int ret = MHD_NO;

	MPA_LOG_TRIVIAL(info,"File to serve: " + filePath);

	(*(*con_cls)) = NULL; /* reset when done */

	int fp = FileHelper::existFile( filePath );

	if ( fp == FileHelper::FILE_NOT_EXIST  )
	{
		MPA_LOG_TRIVIAL(info,"404 - File not found");
		(* response) = MHD_create_response_from_buffer( strlen(PAGE_NOT_FOUND), (void *) PAGE_NOT_FOUND, MHD_RESPMEM_PERSISTENT);
		ret = MHD_HTTP_NOT_FOUND;
	}
	else
	{
		FILE * file = fopen(filePath.c_str(), "rb");
		if( file )
		{
			MPA_LOG_TRIVIAL(trace,"File opened");
			(* response) = MHD_create_response_from_callback(fp, 32 * 1024 /* 32k page size */, &file_reader, file, &free_callback);

			// TODO : When close file otherwise
			if (response == NULL)	fclose(file);
			ret = MHD_HTTP_OK;
		}
	}

	MPA_LOG_TRIVIAL(trace,"Return value: " + StrUtil::int2string( ret ) );

	return ret;
}

void HTTPHandler::getFactoryMPAObject(HttpRequestType requestType, const string& url, const map<string, string>& argvals, string& response)
{
	string id = "-1";
	ptree root;

	MPA_LOG_TRIVIAL(trace,requestType + " URL to manage: " + url);


	mpa_api_rest_v1::MPAOFactory * mpaofactory = mpa_api_rest_v1::MPAOFactory::getInstance();

	mpa_api_rest_v1::MPAO * mpao = mpaofactory->getMPAO(requestType,url,argvals);
	if( mpao != NULL )
	{
		//
		// Check URL parameters
		//
		if( mpao->areParametersOk() )
		{
			//
			// Manage actions
			//
			try
			{
				id = mpao->executeRequest( root );
			}
			catch (string & e)
			{
				id = e;
			}
		}
		else	id = MPA::getErrMsg(3);
	}
	else id = MPA::getErrMsg(5);



	// Add id
	root.push_front( BoostHelper::make_pair( "id", id ) );
	// Add is administrator information
	//root.push_back( BoostHelper::make_pair( "isAdmin" , StrUtil::bool2string( isAdmin ) ) );

	// JSON response
	MPA_LOG_TRIVIAL(trace,"Start JSON generation");
	JSONHelper::generateJSON(&root, response);
	MPA_LOG_TRIVIAL(trace,"JSON generation ended");
}
