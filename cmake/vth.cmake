set(VTH_CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "vth cmake script directory")
set(CMAKE_MODULE_PATH ${VTH_CMAKE_DIR}/modules)


include("${VTH_CMAKE_DIR}/vth_find.cmake")
