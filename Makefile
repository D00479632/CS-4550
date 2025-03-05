# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11 -I.

# Source files
SRCS = Main.cpp Token.cpp Scanner.cpp StateMachine.cpp Symbol.cpp Node.cpp Parser.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = main

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
