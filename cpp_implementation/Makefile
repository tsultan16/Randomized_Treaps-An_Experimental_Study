# specify the compiler
CXX = g++

# specify compiler flags
CXXFLAGS = -g -Wall -I include

# specify the build target
TARGET = driver

# list of source files
SRCS = src/Treap.cpp src/DynamicArray.cpp src/DataGenerator.cpp src/experiments.cpp

# default rule, to compile everything
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# rule to clean the workspace
clean:
	rm -f $(TARGET)
