vth_add_definitions(
	-DUNICODE
	-D_UNICODE
)
if(WIN32)
	vth_add_definitions(-D_AFXDLL)
	ADD_MSVC_PRECOMPILED_HEADER(${STDAFX_PCH_H} ${STDAFX_PCH_C} .)
endif()

vth_include_directories(
.
./src
)

vth_add_sources(
	stdafx.cpp 
	stdafx.h

	src/BaseException.cpp 
	src/BaseException.h 
	src/ConfigHelper.cpp 
	src/ConfigHelper.h 
	src/CoreException.cpp 
	src/CoreException.h 
	src/date.cpp 
	src/date.h 
	src/date2038.cpp 
	src/date2038.h 
	src/libalgo.incl 
	src/libbase.h 
	src/libcommon.h 
	src/libconfig.h 
	src/libmarco.incl 
	src/pubfunc.h 
	src/stringBuffer.cpp 
	src/stringBuffer.h 
	src/stringUtils.cpp 
	src/stringUtils.h
)

vth_add_library(base STATIC ${VTH_COMMON_TARGET_PATH}/base)
