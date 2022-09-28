.PHONY = all clean build test picture
CC = g++

# SRCS := $(shell find . -name "*.cpp")
# BINS := $(SRCS:%.cpp=%.o)
MATHSRC := $(wildcard src/math/*.cpp)
MATHBIN := $(MATHSRC:%.cpp=%.o)

clean:
	rm -rvf $(shell find . -name "*.o") *.exe *.out

all: build

math: ${MATHBIN}

# ray.o: src/math/ray.cpp vec3.o
# 	${CC} -c src/math/ray.cpp

# vec3.o: src/math/vec3.cpp
# 	${CC} -c src/math/vec3.cpp

# sphere.o: src/math/sphere.cpp vec3.o
# 	${CC} -c src/math/sphere.cpp

# hittablelist.o: src/math/hittablelist.cpp
# 	${CC} -c src/math/hittablelist.cpp

# picture: clean src/picture.o ${MATHBIN} 
# 	${CC} -o picture.out $(shell find . -name "*.o")

# test: clean src/test.o ${MATHBIN} 
# 	${CC} -o test.out $(shell find . -name "*.o")

# picture: clean sphere.o
# 	${CC} -o picture.out src/picture.cpp $(shell find . -name "*.o")

# test: clean vec3.o ray.o
# 	${CC} -o test.out src/test.cpp $(shell find . -name "*.o")
%.o: %.cpp
	${CC} -c $<

picture: clean src/picture.cpp ${MATHBIN} 
	${CC} -o picture.out src/picture.cpp $(shell find . -name "*.o")

test: clean src/test.cpp ${MATHBIN} 
	${CC} -o test.out src/test.cpp $(shell find . -name "*.o")