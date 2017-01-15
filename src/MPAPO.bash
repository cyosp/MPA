#!/bin/bash

###############################################################################
#                                                                             #
# Author: cyosp                                                               #
# Version: 1.0.1                                                              #
#                                                                             #
# --------------------------------------------------------------------------- #
#                                                                             #
# Generate C++ files using MPAPO.xml and litesql-gen                          #
#                                                                             #
# --------------------------------------------------------------------------- #
#                                                                             #
# 1.0.1 - 2017-01-15                                                          #
#  - Update class folder path                                                 #
# 1.0.0 - 2015-12-03                                                          #
#  - First version                                                            #
#                                                                             #
###############################################################################

SCRIPT_HOME=$(readlink -f "$0")
SCRIPT_DIR_NAME=$(dirname "$SCRIPT_HOME")

CLASS_NAME="MPAPO"
CLASS_FOLDER="com/cyosp/mpa/po"

cd "$SCRIPT_DIR_NAME"
# Generate C++ files
litesql-gen -t c++ ${CLASS_NAME}.xml

# Update header file
sed -i "s|${CLASS_NAME,,}\.hpp|${CLASS_FOLDER}/${CLASS_NAME}\.hpp|" ${CLASS_NAME,,}.cpp
# Move file to the right place
mv ${CLASS_NAME,,}.hpp ${CLASS_FOLDER}/${CLASS_NAME}.hpp
mv ${CLASS_NAME,,}.cpp ${CLASS_FOLDER}/${CLASS_NAME}.cpp

exit 0
