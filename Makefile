# files
SRC   = ${wildcard src/*.cc}
DEPS  = ${wildcard headers/*}
DEPS += ${wildcard src/*.hh}
OBJ   = ${addsuffix .o,${subst src/,bin/,${basename ${SRC}}}}

ifeq (${platform}, window)
APP = ./bin/yed.exe
else ifeq (${platform}, dos)
APP = ./bin/yed.com
else
APP = ./bin/yed
endif

DOS_SYS_INCLUDE = ~/app/

# compiler related
ifeq (${platform}, windows)
CXX = i686-w64-mingw32-g++
else ifeq (${platform}, dos)
CXX = i586-pc-msdosdjgpp-g++
else ifeq (${debug}, on)
CXX = g++
else
CXX = clang++
endif
CXXVER = c++17
CXXFLAGS = \
	-std=${CXXVER} \
	-g \
	-Wall \
	-Wextra \
	-pedantic \
	-Wno-deprecated-declarations


ifeq (${platform}, windows)
CXXFLAGS += -static -static-libgcc -static-libstdc++ -D_WIN32_WINNT
endif

# rules
compile: ./bin ${OBJ} ${SRC}
	${CXX} -o ${APP} ${OBJ} ${CXXFLAGS}

./bin:
	mkdir -p bin

bin/%.o: src/%.cc ${DEPS}
	${CXX} -c $< ${CXXFLAGS} -o $@

install:
	sudo cp ${APP} /usr/bin/

clean:
	rm bin/*.o $(APP)

all:
	@echo compile
	@echo clean
