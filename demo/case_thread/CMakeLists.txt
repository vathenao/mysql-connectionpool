vth_add_definitions(
	-DUNICODE
	-D_UNICODE
	-DHAVE_STRUCT_TIMESPEC
	-DBASE_NO_EXPORTS
)
if(WIN32)
	vth_add_definitions(-D_AFXDLL)
	ADD_MSVC_PRECOMPILED_HEADER(${STDAFX_PCH_H} ${STDAFX_PCH_C} .)
endif()

vth_include_directories(
	.
	${XDBC_COMMON_INC}
	${XDBC_COMMON_INC}/xdbc
	${PTHREAD_INC_DIR}
)

vth_link_directories(
	${VTH_COMMON_TARGET_PATH}/xdbc
)

SET(PCH stdafx.cpp stdafx.h)
vth_add_sources(
	thread.cpp
	${PCH}
)

vth_add_executable(case_thread ${VTH_BIN_TARGET_PATH}/demo)


vth_add_packages(
	xdbc
	pthreadVC2
)