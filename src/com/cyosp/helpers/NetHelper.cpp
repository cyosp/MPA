/*
 * NetHelper.cpp
 *
 *  Created on: 22 November 2014
 *      Author: cyosp
 */

#include "com/cyosp/helpers/NetHelper.hpp"

/* Works only for server MAC addr
string NetHelper::getMacAddr(const struct sockaddr *addr)
{
	string ret = "";

	char buf[8192] = { 0 };
	struct ifconf ifc =	{ 0 };
	struct ifreq *ifr = NULL;
	int sck = 0;
	int nInterfaces = 0;
	int i = 0;
	char ip[INET6_ADDRSTRLEN] = { 0 };
	char macp[19];
	struct ifreq *item;

	//Get a socket handle.
	sck = socket(PF_INET, SOCK_DGRAM, 0);
	if (sck >= 0)
	{
		//Query available interfaces.
		ifc.ifc_len = sizeof(buf);
		ifc.ifc_buf = buf;
		if (ioctl(sck, SIOCGIFCONF, &ifc) >= 0)
		{
			//Iterate through the list of interfaces.
			ifr = ifc.ifc_req;
			nInterfaces = ifc.ifc_len / sizeof(struct ifreq);

			for (i = 0; i < nInterfaces; i++)
			{
				item = &ifr[i];

				//addr = &(item->ifr_addr);

				//Get the IP address
				if (ioctl(sck, SIOCGIFADDR, item) < 0)
				{
					perror("ioctl(OSIOCGIFADDR)");
				}

				if (inet_ntop(AF_INET, &(((struct sockaddr_in *) addr)->sin_addr), ip,
						sizeof ip) == NULL) //vracia adresu interf
				{
					perror("inet_ntop");
					continue;
				}

				// Get the MAC address
				if (ioctl(sck, SIOCGIFHWADDR, item) >= 0)
				{
					sprintf(macp, "%02x:%02x:%02x:%02x:%02x:%02x",
											(unsigned char) item->ifr_hwaddr.sa_data[0],
											(unsigned char) item->ifr_hwaddr.sa_data[1],
											(unsigned char) item->ifr_hwaddr.sa_data[2],
											(unsigned char) item->ifr_hwaddr.sa_data[3],
											(unsigned char) item->ifr_hwaddr.sa_data[4],
											(unsigned char) item->ifr_hwaddr.sa_data[5]);

					ret = string( macp );

				}
			}
		}
	}

	return ret;
}*/

string NetHelper::getIpAddr(const struct sockaddr *addr)
{
	string ret = "";

	char buf[INET6_ADDRSTRLEN];

	ret = string( inet_ntop(addr->sa_family, addr->sa_data + 2, buf, INET6_ADDRSTRLEN) );

	return ret;
}

/*
std::string urlencode(const std::string& url) {
  // Find the start of the query string
  const std::string::const_iterator start = std::find(url.begin(), url.end(), '?');

  // If there isn't one there's nothing to do!
  if (start == url.end())
    return url;

  // store the modified query string
  std::string qstr;

  std::transform(start+1, url.end(),
                 // Append the transform result to qstr
                 boost::make_function_output_iterator(boost::bind(static_cast<std::string& (std::string::*)(const std::string&)>(&std::string::append),&qstr,_1)),
                 encimpl);
  return std::string(url.begin(), start+1) + qstr;
}*/

