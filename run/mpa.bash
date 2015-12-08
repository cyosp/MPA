#/bin/bash

###############################################################################
#                                                                             #
# Author: cyosp                                                               #
# Version: 1.0.0                                                              #
#                                                                             #
# --------------------------------------------------------------------------- #
#                                                                             #
# Manage MPA start/stop/clean                                                 #
#                                                                             #
# --------------------------------------------------------------------------- #
#                                                                             #
# 1.0.0 - 08/12/2015                                                          #
#  - First version                                                            #
#                                                                             #
###############################################################################

SCRIPT_PATH=$(readlink -f $0)
HOME_SCRIPT=$(dirname "$SCRIPT_PATH")
RETVAL=0

# Configuration values
MPA_BIN_NAME="MPA"
MPA_TARGET="Release"
MPA_PORT="8080"

# MPA binary file path
MPA_BIN_PATH="${HOME_SCRIPT}/../$MPA_TARGET/$MPA_BIN_NAME"
MPA_DB_PATH="/tmp/${MPA_BIN_NAME,,}.db"
MPA_LOG_PATH="/tmp/${MPA_BIN_NAME,,}.log"

# Get MPA PID
MPA_PID=`netstat -apn -t $MPA_PORT 2>/dev/null | grep "$MPA_BIN_NAME" | tail -1 | tr -s ' ' | cut -d ' ' -f 7 | cut -d '/' -f 1`

case "$1" in
	'start')
		if [ -z "$MPA_PID" ]
		then
			INIT_ADMIN_LOGIN="$2"

			echo "Start MPA server"
			$MPA_BIN_PATH $MPA_PORT $MPA_DB_PATH $MPA_LOG_PATH $INIT_ADMIN_LOGIN
			RETVAL=$?

			MPA_PID=`netstat -apn -t $MPA_PORT 2>/dev/null | grep "$MPA_BIN_NAME" | tail -1 | tr -s ' ' | cut -d ' ' -f 7 | cut -d '/' -f 1`
			echo "Started with PID: "$MPA_PID
		else
			echo "Already running with PID: $MPA_PID"
		fi
	;;
	'stop')
		if [ -n "$MPA_PID" ]
		then
			kill $MPA_PID
			RETVAL=$?
		else
			echo "No MPA process running"
		fi
	;;
	'reset')
		# Remove database
		if [ -e "$MPA_DB_PATH" ]
		then
			rm "$MPA_DB_PATH"
			RETVAL=$?
		fi
	;;
	'restart')
		$0 stop && $0 start
		RETVAL=$?
	;;
	*)
		echo "Usage: $0 {start [init admin login] | stop | reset | restart}"
		RETVAL=1
	;;
esac

exit $RETVAL
