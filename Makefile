# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -O2

# Source and output names
SRC = $(wildcard problem*.cpp)
OUT = $(patsubst problem%.cpp,p%,$(SRC))

# Default target
all: $(OUT)

# Pattern rule for building each program
p%: problem%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean up compiled files
clean:
	rm -f $(OUT)