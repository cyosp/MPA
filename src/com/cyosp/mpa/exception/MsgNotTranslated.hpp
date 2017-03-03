/*
 * MPAException.hpp
 *
 *  Created on: 2017-03-02
 *      Author: CYOSP
 */

#ifndef COM_CYOSP_MPA_EXCEPTION_MSGNOTTRANSLATED_HPP_
#define COM_CYOSP_MPA_EXCEPTION_MSGNOTTRANSLATED_HPP_

#include <exception>

using std::exception;
using std::string;

namespace mpa_exception
{

class MsgNotTranslated : public exception
{
	private:
		string msg;

	public:
		MsgNotTranslated(string msg) throw() : msg(msg) {}

		virtual const char* what() const throw() {
				return msg.c_str();
			}

};

}

#endif /* COM_CYOSP_MPA_EXCEPTION_MSGNOTTRANSLATED_HPP_ */
