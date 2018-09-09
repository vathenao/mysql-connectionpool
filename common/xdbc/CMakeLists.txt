vth_add_definitions(
	-DUNICODE
	-D_UNICODE
	-DHAVE_STRUCT_TIMESPEC
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
)

vth_add_sources(
	stdafx.cpp 
	stdafx.h

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
	src/xdbc.conf
	src/xdbcdefs.h
	src/xdbcWrapper.cpp
	src/xdbcWrapper.h
	src/connfactory.cpp
	src/connfactory.h
	src/connpool.cpp
	src/connpool.h
	src/connpoolException.cpp
	src/connpoolException.h
	src/dbconnect.cpp
)

vth_add_library(xdbc STATIC ${VTH_COMMON_PATH}/xdbc)