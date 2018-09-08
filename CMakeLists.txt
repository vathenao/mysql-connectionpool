CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(COMMON_DIR ${CMAKE_BINARY_DIR}/common)
PROJECT(common)
include(cmake/vth.cmake)

vth_add_subdirectory(base)
vth_add_subdirectory(xdbc)
