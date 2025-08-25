# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Iinclude -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lboost_system -lboost_filesystem

# Source files
SRC = $(wildcard src/*.cpp tests/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Executables
REPL_EXE = craftLangCompiler
TEST_EXE = test_runner

# Default target
all: $(REPL_EXE) $(TEST_EXE)

# Compile REPL
$(REPL_EXE): src/main.cpp $(filter-out tests/test_runner.cpp, $(OBJ))
	$(CXX) $(CXXFLAGS) -o $@ src/main.cpp $(filter-out tests/test_runner.cpp, $(OBJ)) $(LDFLAGS)

# Compile test runner
$(TEST_EXE): tests/test_runner.cpp $(filter-out src/main.cpp, $(OBJ))
	$(CXX) $(CXXFLAGS) -o $@ tests/test_runner.cpp $(filter-out src/main.cpp, $(OBJ)) $(LDFLAGS)

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ) $(REPL_EXE) $(TEST_EXE)
