#!/bin/bash
# init_craftLang.sh
# Bash script to bootstrap craftLang project with placeholders for if, function, and class statements

PROJECT_NAME="craftLangCompiler"
EXECUTABLE="craftLangCompilerExecutable"

# Folder structure
FOLDERS=(
  "$PROJECT_NAME/include/ast_nodes"
  "$PROJECT_NAME/include/parser_modules"
  "$PROJECT_NAME/include/runtime_engine"
  "$PROJECT_NAME/include/utilities"
  "$PROJECT_NAME/tests"

)

# Create folders
for folder in "${FOLDERS[@]}"; do
  mkdir -p "$folder"
done

# Create Makefile
cat <<EOL > "$PROJECT_NAME/Makefile"
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = 

SRC = \$(wildcard src/**/*.cpp src/*.cpp)
OBJ = \$(SRC:.cpp=.o)

all: $EXECUTABLE

$EXECUTABLE: \$(OBJ)
	\$(CXX) \$(CXXFLAGS) -o \$@ \$(OBJ) \$(LDFLAGS)

clean:
	rm -f \$(OBJ) $EXECUTABLE
EOL

# Create main.cpp stub
cat <<EOL > "$PROJECT_NAME/src/main.cpp"
#include <iostream>
int main() {
    std::cout << "craftLangCompiler is running..." << std::endl;
    return 0;
}
EOL

# Create descriptive stub AST node files
AST_FILES=("AstNode" "ExitNode" "FunctionCallNode" "FunctionDefinitionNode"  "PrintStatementNode" "VariableAssignmentNode)
for f in "${AST_FILES[@]}"; do
  cat <<EOL > "$PROJECT_NAME/include/ast_nodes/$f.hpp"
#pragma once
class $f {
public:
    $f() {}
    virtual ~$f() {}
    // TODO: Implement $f behavior
};
EOL

  cat <<EOL > "$PROJECT_NAME/src/ast_nodes/$f.cpp"
#include "$f.hpp"
// TODO: Implement $f methods
EOL
done

# Create descriptive parser module stubs
PARSER_FILES=("CraftLangGrammar" "WhitespaceSkipper")
for f in "${PARSER_FILES[@]}"; do
  cat <<EOL > "$PROJECT_NAME/include/parser_modules/$f.hpp"
#pragma once
class $f {
public:
    $f() {}
    // TODO: Implement parsing rules for $f
};
EOL

  cat <<EOL > "$PROJECT_NAME/src/parser_modules/$f.cpp"
#include "$f.hpp"
// TODO: Implement $f methods
EOL
done

# Create runtime engine stubs
RUNTIME_FILES=("RuntimeContext" "AstExecutor")
for f in "${RUNTIME_FILES[@]}"; do
  cat <<EOL > "$PROJECT_NAME/include/runtime_engine/$f.hpp"
#pragma once
class $f {
public:
    $f() {}
    // TODO: Implement runtime behavior for $f
};
EOL

  cat <<EOL > "$PROJECT_NAME/src/runtime_engine/$f.cpp"
#include "$f.hpp"
// TODO: Implement $f methods
EOL
done

# Create utilities stub
cat <<EOL > "$PROJECT_NAME/include/utilities/LoggerUtility.hpp"
#pragma once
#include <iostream>
inline void logMessage(const std::string &msg) {
    std::cout << "[LOG] " << msg << std::endl;
}
EOL

cat <<EOL > "$PROJECT_NAME/src/utilities/LoggerUtility.cpp"
#include "LoggerUtility.hpp"
// TODO: Expand logger features
EOL
