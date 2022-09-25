# files
SRC   = ${wildcard src/*.cc}
DEPS  = ${wildcard headers/*}
DEPS += ${wildcard src/*.hh}
OBJ   = ${addsuffix .o,${subst src/,bin/,${basename ${SRC}}}}

APP = ./bin/yed

# compiler related
ifeq (${platform}, windows)
CXX = x86_64-w64-mingw32-g++
else
CXX = clang++
endif
CXXVER = c++17
CXXFLAGS = \
	-std=${CXXVER} \
	-Wall \
	-Wextra \
	-pedantic \
	-Wno-deprecated-declarations

ifeq (${platform}, windows)
CXXFLAGS += -static -static-libgcc -static-libstdc++
endif

# rules
compile: ./bin ${OBJ} ${SRC}
	${CXX} -s -o ${APP} ${OBJ} ${CXXFLAGS}

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
