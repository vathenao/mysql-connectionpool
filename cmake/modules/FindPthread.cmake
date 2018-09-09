##########################################################################
#
#   Copyright vathena. All rights reserved.
#
#		This file is used to find pthread libaray in win32 platform
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published
#   by the Free Software Foundation; version 2 of the License.
#
#   This program is distributed in the hope that it will be useful, but
#   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#   or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
#   for more details.
#
#   You should have received a copy of the GNU General Public License along
#   with this program; if not, write to the Free Software Foundation, Inc.,
#   51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
#
##########################################################################

##########################################################################
#
# Configuration variables, all optional, are
#
#		PTHREAD_DIR	 				- Set in environment or as parameter to "cmake",
#                       this is the top directory of the PTHREAD install
#
#   PTHREAD_INC_DIR - Set in environment or as parameter to "cmake",
#                       this is the include directory where to find
#                       the pthread library
#
#   PTHREAD_LIB_DIR			- Set in environment or as parameter to "cmake",
#                       this is the library directory where to find
#                       the pthread library
#
##########################################################################

set(PTHREAD_CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "pthread cmake script directory")

#find pthread libaray
SET(
  PTHREAD_INCLUDE_DIR
  PTHREAD_LIB_DIR
)

SET(_LIB_FALLBACK_PATH
		../../pthread/*/lib
    $ENV{ProgramFiles}/*pthread*/*/lib
    $ENV{SystemDrive}/*pthread*/*/lib
)

FIND_LIBRARY(PTHREAD_LIB_DIR
    NAMES
      ${PTHREAD_NAMES}
    PATHS
      ${_LIB_FALLBACK_PATH}
)

#find pthread.h
SET(_INC_FALLBACK_PATH
		${PTHREAD_CMAKE_DIR}/../../support/pthread/*/include
    $ENV{ProgramFiles}/*pthread*/*/include
    $ENV{SystemDrive}/*pthread*/*/include
)

FIND_PATH(PTHREAD_INC_DIR pthread.h ${_INC_FALLBACK_PATH})

if(NOT PTHREAD_INC_DIR)
    MESSAGE(FATAL_ERROR "PTHREAD_INC_DIR = \"${PTHREAD_INC_DIR}\",Could not find \"pthread.h\" from searching "
                        "\"${_INC_FALLBACK_PATH}\"")
endif()

MESSAGE(STATUS "  PTHREAD_INC_DIR             : ${PTHREAD_INC_DIR}")