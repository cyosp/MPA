/*
 * NetHelper.hpp
 *
 *  Created on: 22 November 2014
 *      Author: cyosp
 */

#ifndef NETHELPER_H_
#define NETHELPER_H_

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <string>
using namespace std;
using std::string;

#include <boost/function_output_iterator.hpp>

#include <com/cyosp/mpa/MPA.hpp>

class NetHelper
{
public:
	//static string getMacAddr(const struct sockaddr *addr);
	static string getIpAddr(const struct sockaddr *addr);
};

#endif /* NETHELPER_H_ */
