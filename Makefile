PROGRAM = RBTree

# Compilation command and flags
CXX=g++
CXXVERSION= -std=c++11
CXXFLAGS= $(CXXVERSION)

# Directories
SRC_DIR = src
SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

# Tool varialbes
STATIC_ANALYSIS = cppcheck
STYLE_CHECK = cpplint.py

# Default goal, used by Atom for local compilation
.DEFAULT_GOAL := RBTree

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean up all files that should NOT be submitted
.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o *.o \
	*.orig ???*/*.orig $(PROGRAM)

$(PROGRAM): $(SRC)
		$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(INCLUDE) \
		$(SRC_DIR)/*.cpp

memcheck: $(GTEST)
	valgrind --tool=memcheck --leak-check=full $(PROGRAM)

static: ${SRC_DIR} ${SRC_INCLUDE}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR} ${SRC_INCLUDE} --suppress=missingInclude

style: ${SRC_DIR}
	${STYLE_CHECK} ${SRC_DIR}/* ${SRC_INCLUDE}/*
