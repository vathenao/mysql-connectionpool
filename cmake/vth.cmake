set(VTH_CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "vth cmake script directory")
set(CMAKE_MODULE_PATH ${VTH_CMAKE_DIR}/modules)

set(STDAFX_PCH_H ${CMAKE_SOURCE_DIR}/stdafx.h)
set(STDAFX_PCH_C ${CMAKE_SOURCE_DIR}/stdafx.cpp)

include("${VTH_CMAKE_DIR}/vth_find.cmake")

if(WIN32)
	include("${VTH_CMAKE_DIR}/msvcpch.cmake")
endif()
