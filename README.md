1、Abstract:
	Xdbc connection pool is a database connection-pool writing by c++ wish to provide unified interfaces to access mainstream database so that you not need to pay attention to the difference of diffrent databases like MYSQL,ORACLE,SQL SERVER etc. but now it can support MySQL only.
It package the base operation of database and manage the database connection itself. So you not need to pay attention to how to get or release the database connection. With using xdbc ,you can operate database conveniently and high-performance by using database connection repeatly and using preparedstament to access database.It can also support transaction.

2、Requirements
Platform：
	Linux
	Windows
	
Other: 
	MySQL 5.6 or aboven
	cmake 2.8 or aboven
	visual studio 13 or aboven(only Windows)

3、Getting Started
3.1 clone this repo to your computer
	git clone git clone https://github.com:vathenao/mysql-connectionpool.git

3.2 installation
	install mysql and cmake for your computer,for more information,see Requirements.

3.3 compile the project
	a) xdbc using cmake for supporting out-of-source builds,so you need to create a folder for compiling.
		$mkdir ~/build
	
 	b) create your builds,with this step, you can also configure you database-connection information by specifying corresponding option of cmake command line parameters.
	for more informatin,see Configuration.
		$cd ~/build
		cmake code-path      (your code path of xdbc eg:cmake /home/staff/conncetionpool)

 	c) make the target libbase.a and libxdbc.a
		$cd ~/build
		$make

4.Configuration
	xdbc use configuration file to connect to the database.Befor using it, you must configure the connection information of your database in the configuration file 'xdbc.cfg'.
to settings you dabatase-connection infomation by the following ways:
	a) edit the xdbc.cfg file in you build path. after cmake,it was written to: ~/build/bin/common/xdbc/cfgs/xdbc.cfg
	
	b) configure database with cmake command line option
		-DXDBC_HOST=<host>
		-DXDBC_USER=<user>
		-DXDBC_PASSWD=<password>
		-DXDBC_DATABASE=<database>

	eg:cmake /home/staff/conncetionpool -DXDBC_HOST="localhost" -DXDBC_USER="test" -DXDBC_PASSWD="passwordoftest" -DXDBC_DATABASE="dbtest"

	remark: only support database-connection information settings with cmake cmd-line option.
to change other settings,you must change it in xdbc.cfg manually,or change the cmakelists.txt and configuration file to support customer cmd-line option.

xdbc.cfg looks like below.
[ConnInfo]
#database host
#your can configure this session by using XDBC_HOST option in cmake command line
HOST		=	${XDBC_HOST}

#database user name,using for login the database
#your can configure this session by using XDBC_USER option in cmake command line
#remark: make sure this user has right to access your database specified by DATABASE session
USER  		=	${XDBC_USER}

#password of USER
#your can configure this session by using XDBC_PASSWD option in cmake command line
PASSWD		=	${XDBC_PASSWD}

#database name, the database that you want to access
#our can configure this session by using XDBC_DATABASE option in cmake command line
DATABASE	=	${XDBC_DATABASE}

#configuration of connection pool
[ConnPoolConf]
#max connection of xdbc connection pool,between 1 and 200
#this count is the setting of xdbc connection pool and it is under the control of 
#connection limit of database itseft
MAXCONNSIZE =	5

#database type,now it support MYSQL only
DBTYPE		= MYSQL

#timeout for getting connection in the conncetion pool (unit:minute)
TIMEOUT = 5
