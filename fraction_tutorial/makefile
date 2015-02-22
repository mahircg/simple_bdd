## Compiler and linker definitions (adjust definitions to your convenience!)
# -O0 : optimization level 0
# -g : adds debugging information to the executable file
# -Wall : activates most compiler warnings
# -std=c++11 : version 11 of the C++ standard
# -lcppunit : includes library of the CppUnit test framework
CXX = g++
CXXFLAGS = -O0 -Wall -g -D DEBUG -std=c++11
INCLUDES =
LDFLAGS = 
LIBS = -lcppunit

## list all source files
SRC = src/Fraction.cpp src/unittest/FractionTest.cpp test/testrunner.cpp

## Object files
# Below we are replacing the suffix .cpp of all source files with the .o suffix
OBJECTS = $(SRC:.cpp=.o)

## Default rule
all: unittest

## create target (executable)
test: $(OBJECTS) 
	 $(CXX) $(CXXFLAGS) $(INCLUDES) -o testrunner $(OBJECTS) $(LDFLAGS) $(LIBS)

## creates the target and the run the tests
unittest: test
	# Unit Test results:
	./testrunner

## add dependencies to ensure that Make rebuilds files if the included headers (*.hpp files) 
## change
src/Fraction.o: src/Fraction.hpp
src/unittest/FractionTest.o: src/unittest/FractionTest.hpp src/Fraction.hpp

## removes files produced by the compiler and the linker
clean:
	@rm -f testrunner
	@rm -f src/*.o
	@rm -f src/unittest/*.o
	@rm -f test/*.o

