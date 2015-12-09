#!/bin/bash

HOME_SCRIPT=$(dirname $(readlink -f $0))

$HOME_SCRIPT/mpa_stop.bash \
&& \
$HOME_SCRIPT/mpa_reset.bash \
&& \
sleep 1 \
&& \
$HOME_SCRIPT/mpa_admin_start.bash

exit $?
