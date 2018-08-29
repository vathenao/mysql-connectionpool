include_directories(
.
../inc
)

AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_LIBRARY(xdbc STATIC ${SRC_LIST})
