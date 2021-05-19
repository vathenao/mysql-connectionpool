SET(XDBC_CFG_PATH ${VTH_COMMON_TARGET_PATH}/xdbc/cfgs)

vth_add_definitions(
	-DUNICODE
	-D_UNICODE
	-DHAVE_STRUCT_TIMESPEC
	-DXDBC_LIB
	-DBASE_NO_EXPORTS
)
if(WIN32)
	vth_add_definitions(-D_AFXDLL)
	ADD_MSVC_PRECOMPILED_HEADER(${STDAFX_PCH_H} ${STDAFX_PCH_C} .)
endif()

vth_include_directories(
.
./src
../inc
${PTHREAD_INC_DIR}
${CMAKE_CURRENT_BINARY_DIR}/inc
)

vth_link_directories(
	${VTH_COMMON_TARGET_PATH}/base
	${PTHREAD_LIB_DIR}
)

vth_add_sources(
	stdafx.cpp 
	stdafx.h
	global.h
	
	src/dbconnect.h
	src/libxdbc.h
	src/mysqlConnection.cpp
	src/mysqlConnection.h
	src/mysqlPrepareStatement.cpp
	src/mysqlPrepareStatement.h
	src/mysqlResultSet.cpp
	src/mysqlResultSet.h
	src/sqlException.cpp
	src/sqlException.h
	src/x_connection.h
	src/x_prepareStatement.h
	src/x_resultset.h
	src/x_statement.h
	src/xdbcWrapper.cpp
	src/xdbcWrapper.h
	src/connfactory.cpp
	src/connfactory.h
	src/connpool.cpp
	src/connpool.h
	src/connpoolException.cpp
	src/connpoolException.h
	src/dbconnect.cpp
	src/xdbc.h
	src/xdbcdefs.h.in
	src/xdbc.cpp
)

vth_add_resource(./src/xdbc.cfg ${XDBC_CFG_PATH}/xdbc.cfg)
vth_add_resource(./src/xdbcdefs.h.in ${CMAKE_CURRENT_BINARY_DIR}/inc/xdbcdefs.h)
vth_add_library(xdbc SHARED ${VTH_COMMON_TARGET_PATH}/xdbc)

vth_add_packages(
	base
	mysqlclient
)

if(WIN32)
vth_add_packages(
	pthreadVC2
)
endif()