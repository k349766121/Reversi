CXX = g++				# compiler
CXXFLAGS = -std=c++20  -Wall -g	 -I./Crow/include/ -I/opt/homebrew/opt/asio/include	# compiler flags /crow is where crow is lcoated
#. opt/homebrew/opt/asio/include is where asio is located
CXXFLAGSHEADER = -std=c++20 -fmodules-ts -c -x c++-system-header 

# Linker flags
LDFLAGS := 

# Target executable name
TARGET := program

# Find all cpp files in the current directory
SOURCES := $(wildcard *.cc)

# Convert the *.cpp files to *.o files
OBJECTS := $(SOURCES:.cc=.o)

# Default target
all: $(TARGET)

# Link all object files to make executable
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^
	rm -f $(OBJECTS)

# Rule to compile all cpp files to o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Target
clean:
	rm -f $(TARGET) $(OBJECTS)

# Phony targets
.PHONY: all clean
