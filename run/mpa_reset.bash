#!/bin/bash

$(dirname $(readlink -f $0))/mpa.bash reset

exit $?
