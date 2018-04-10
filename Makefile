DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_LIB = ./lib
CPPSRC = $(wildcard ${DIR_SRC}/*.cpp)
CPPOBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${CPPSRC}))
CPPFLAGS = -g -Wall -std=gnu++11 -Wno-write-strings -Wformat=0 -I${DIR_INC} -I/usr/local/include
CPPLDFLAGS =-L/usr/local/lib -luuid -lssl -lcrypto -lz  

TARGET = libyyhonvif.so
LIB_TARGET = ${DIR_LIB}/${TARGET}

CXX = g++ -DDEBUG
${LIB_TARGET}:${CPPOBJ}
	$(CXX) ${CPPOBJ} $(CPP_LDFLAGS) -shared -fPIC -o  $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CXX) $(CPPFLAGS) -c -fPIC  $< -o $@



.PHONY:clean install
clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
	find ${DIR_LIB} -name *.so -exec rm -rf {} \;
install:
	cp ${DIR_LIB}/*.so /usr/lib/