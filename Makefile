CXX      ?= g++
CXXFLAGS ?= -std=c++20

#change these paths
CPPFLAGS ?= -O3 -Wall -Wno-conversion-null -Wno-deprecated-declarations -I. -I../../pacs-examples/Examples/include -I../../eigen/3.3.9/include/eigen3

EXEC     = main

#change this path
LDFLAGS ?= -L../../pacs-examples/Examples/lib/
LIBS  ?= -lmuparser 

# Get all files *.cpp
SRCS=$(wildcard *.cpp)
# Get the corresponding object file
OBJS = $(SRCS:.cpp=.o)
# Get all headers in the working directory
HEADERS=$(wildcard *.hpp)
#
exe_sources=$(filter main%.cpp,$(SRCS))
EXEC=$(exe_sources:.cpp=)

#========================== ORA LA DEFINIZIONE DEGLI OBIETTIVI
.PHONY: all clean distclean doc

.DEFAULT_GOAL = all

all: $(EXEC)

clean:
	-\rm -f $(EXEC) $(OBJS)

distclean: clean
	-\rm -f ./doc $(DEPEND)
	-\rm -f *.out *.bak *~

doc:
	doxygen $(DOXYFILE)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

# Compile each source file into an object file
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
