CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(VTH_BIN_TARGET_PATH ${CMAKE_BINARY_DIR}/bin)
SET(VTH_COMMON_TARGET_PATH ${VTH_BIN_TARGET_PATH}/common)

PROJECT(connpool)
include(cmake/vth.cmake)

vth_add_subdirectory(common)
