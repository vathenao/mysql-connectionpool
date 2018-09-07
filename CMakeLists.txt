CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(common)


include(cmake/vth.cmake)

vth_add_subdirectory(base)
vth_add_subdirectory(xdbc)
