# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude -Iinclude/CppUnitLite $(shell pkg-config --cflags opencv4)
LDFLAGS = $(shell pkg-config --libs opencv4)

# Directories
SRC_DIR = src/main
OBJ_DIR = obj
BIN_DIR = bin
CPPUNITLITE_DIR = include/CppUnitLite

# Files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/main

CPPUNITLITE_SOURCES = $(wildcard $(CPPUNITLITE_DIR)/*.cpp)
CPPUNITLITE_OBJECTS = $(CPPUNITLITE_SOURCES:$(CPPUNITLITE_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Test-related variables
TEST_DIR = src/test
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_EXECUTABLE = $(BIN_DIR)/test_main

# Main target
all: $(EXECUTABLE) $(TEST_EXECUTABLE)

# Test target
$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(filter-out $(OBJ_DIR)/main.o,$(OBJECTS)) $(CPPUNITLITE_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(CPPUNITLITE_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Make sure the 'clean' target does not refer to a file name
.PHONY: all clean
