.PHONY = all clean build test picture
CC = g++

# SRCS := $(shell find . -name "*.cpp")
# BINS := $(SRCS:%.cpp=%.o)
MATHSRC := $(wildcard src/math/*.cpp)
MATHBIN := $(MATHSRC:%.cpp=%.o)

clean:
	rm -rvf $(shell find . -name "*.o") *.exe

all: build

math: ${MATHBIN}

%.o: %.cpp
	${CC} -c $<

picture: clean src/picture.o ${MATHBIN} 
	${CC} -o picture.out $(shell find . -name "*.o")

test: clean src/test.o ${MATHBIN} 
	${CC} -o test.out $(shell find . -name "*.o")