##-------------------------------------##
#- 		COMPILER  COMMON  SETTING	   -#
##-------------------------------------##
CC=gcc
COMP_OPT= -g
AR=ar
AR_OPT=-rc
COMP_EXEC=$(CC) $(COMP_OPT)
ARLIB_EXEC=$(AR) $(AR_OPT)
##########################################
##########################################
COMMON_HOME=..
BASE_INC=$(COMMON_HOME)/inc
MYSQL_PATH=/alidata/server/mysql-5.6.15
LIB_PATH=/usr/local/lib64
OBJC_DIR=.
ARLIB_PATH=$(COMMON_HOME)/lib

ALL_INC=-I$(BASE_INC) -I$(MYSQL_PATH)/include
ALL_LIB=-L$(MYSQL_PATH)/lib -lmysqlclient -L$(ARLIB_PATH) -lbase
ARLIB_FILE=libxdbc.a
OBJ_DIR=.obj

SRCS = $(wildcard *.cpp)
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))
$(OBJ_DIR)/%.o: %.cpp
	@echo "$(OBJC_DIR)/$<"
	@$(COMP_EXEC) $(ALL_INC) $(ALL_LIB) -c $< -o $@
	@rm -f $(OBJ_DIR)/*.d
	
all:$(OBJS)
	@echo "link all obj file ..."
	$(ARLIB_EXEC) $(ARLIB_PATH)/$(ARLIB_FILE) $(OBJ_DIR)/*.o
	
obj:$(OBJS)
	
clean:
	@echo "clean all obj file ..."
	@rm -f $(OBJ_DIR)/*.o
	@rm -f $(ARLIB_PATH)/$(ARLIB_FILE)

