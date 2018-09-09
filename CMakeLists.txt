CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(VTH_BIN_PATH ${CMAKE_BINARY_DIR}/bin)
SET(VTH_COMMON_PATH ${VTH_BIN_PATH}/common)

PROJECT(connpool)
include(cmake/vth.cmake)

vth_add_subdirectory(common)
