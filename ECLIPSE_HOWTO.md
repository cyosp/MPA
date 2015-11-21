# Eclipse HowTo

## Configure Eclipse in order to build a Release

 * Right click on *MPA* project and select *Properties*

 * Then select *C/C++ Build*
	* Click on button *Manage Configuration...*
	* Select *Release*
	* Click on button *Set Active*
	* And *OK*

	* In *Behaviour* tab
	* Checked *Use parallel build*
	* In *Use parallel jobs* enter the processor core number which will compile [MPA](https://github.com/cyosp/MPA)

 * Deploy *C/C++ Build* and select *Settings*

	* In tab *Tool Settings*
		* Select *Miscellaneous* in *GCC C++ Compiler*
			* Add *-m64* in *Other flags*
		* Select *Miscellaneous* in *GCC C++ Linker*
			* Add *-m64* in *Linker flags*

 * Deploy *C/C++ General* and select *Paths and Symbols*

	* In tab *Includes* and language *GNU C++*
	* Click *Add* button
	* Enter */usr/local/include/boost* in *Directory:*
	* And *OK*

	* Click *Add* button
	* Enter */MPA/src* in *Directory:*
	* Check *Is a workspace path*
	* And *OK*

	* In tab *Symbols* and language *GNU C++*
	* Click *Add* button
	* Enter *BOOST_LOG_DYN_LINK* in *Name:*
	* And *OK*

	* In tab *Libraries*
	* Click *Add...* button
	* Enter *pthread* in *File:*
	* And *OK*
	* Repeat the operation for:
		* microhttpd
		* boost_thread
		* boost_system
		* boost_regex
		* boost_log
		* boost_log_setup
		* boost_locale
		* litesql
		* litesql-util

 * And *OK*
 * Select *Yes* for dialog box *Paths and Symbols* and message: *Changes to the include search paths or defined symbols will not be reflected in the index until it is rebuilt. Do you wish to rebuild it now ?*

## Build a Release

 * Right click on *MPA* project and select *Build Project*
OR
 * Select *MPA* project
 * In *Project* Eclipse menu select *Build Project*
