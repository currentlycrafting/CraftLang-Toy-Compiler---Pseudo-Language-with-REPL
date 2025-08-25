# CraftLang: Toy Compiler & REPL 🧑‍💻

**CraftLang** is a lightweight, experimental pseudo-language compiler written in C++ with a REPL (Read-Eval-Print Loop). It demonstrates key compiler concepts such as **parsing**, **AST construction**, **runtime execution**, and **control structures**. The compiler uses **Boost.Spirit** for parsing and supports variables, functions, loops, return statements, and basic I/O.

----------

## Features

-   **Variable Management**: Assign and manipulate integers, floats, strings, and expressions. Supports local and global scope.
    
-   **Function Definitions & Calls**: Define functions with parameters, return values, and nested statements. Handles the function call stack.
    
-   **Loops & Repeat Statements**: Use `repeat <count> times ... end` loops to execute Abstract Syntax Tree (AST) blocks multiple times
    
-   **Return Statements**: Functions can return values using the `return <expression>` statement.
    
-   **Print & Exit Statements**: Print variables or literals to the console. Exit the REPL with `exit` or `exit program`.
    
-   **REPL Mode**: Interactive execution allows live parsing and execution of commands.
    

----------

## Project Structure

```
CraftLang/
├─ .vscode/
├─ include/
│  ├─ nodes/           # AST node headers
│  ├─ parser/          # Grammar definition
│  ├─ runtime/         # Runtime context and execution support
├─ src/
│  ├─ nodes/           # AST node implementations
│  ├─ parser/          # Grammar parser implementation
│  ├─ runtime/         # Runtime execution logic
│  ├─ main.cpp         # Entry point: REPL and script execution
├─ tests/
│  ├─ test_basic.cl    # Sample CraftLang scripts
│  ├─ tests.cpp        # Test harness
├─ CMakeLists.txt
├─ Makefile
├─ .gitignore
└─ init_craftLang.sh    # Setup script

```

----------

## Example Syntax

### Variable Assignment

```
assign integer variable x to 10
assign float variable pi to 3.14
assign string variable greeting to Hello World
assign variable sum with x

```

### Function Definition & Call

```
define function add with parameters a, b
  assign variable result with a
  assign variable next_result with b
  return result + next_result
end
call add using 10, 20

```

### Repeat Loops

```
repeat 5 times
  print x
end

```

### Exiting

```
exit
exit program

```

----------

## REPL Usage

To start the REPL:

Bash

```
./craftLangCompiler

```

Example session:

```
CraftLang REPL. Type 'exit' to quit.
> assign integer variable x to 5
> print x
5
> repeat 3 times
... print x
... end
5
5
5
> exit
Goodbye!

```

----------

## Building and Running

### Using CMake

Bash

```
mkdir build
cd build
cmake ..
make
./craftLangCompiler

```

### Using Makefile

Bash

```
make
./craftLangCompiler

```

----------

## Dependencies

-   C++17 or newer
    
-   Boost Libraries (Boost.Spirit & Boost.Phoenix)
    
-   Standard C++ libraries: `<iostream>`, `<vector>`, `<string>`, `<memory>`, `<variant>`
    

format it the way i have but expand

# CraftLang: A Toy Compiler & REPL

**CraftLang** is a lightweight, experimental pseudo-language compiler written in C++ with a REPL (Read-Eval-Print Loop). It's a project designed to explore and demonstrate key compiler concepts, including **parsing**, **AST construction**, **runtime execution**, and **control structures**. The compiler leverages **Boost.Spirit** for its parsing framework, providing a robust foundation for defining the language's grammar. It supports a variety of features, such as variable management, function definitions, loop structures, and basic I/O, making it a comprehensive learning tool for anyone interested in compiler design.

----------

## Features

-   **Variable Management**: Create, assign, and manipulate variables of various types, including integers, floats, and strings. The compiler manages variable scope, distinguishing between local variables within a function and global variables accessible throughout the program.
    
-   **Function Definitions & Calls**: Define custom functions with parameters and return values. The runtime handles the function call stack, allowing for nested and recursive calls just like a professional programming language.
    
-   **Loops & Repeat Statements**: The `repeat <count> times ... end` loop provides a simple yet powerful way to execute a block of code multiple times, offering a clear demonstration of control flow.
    
-   **Return Statements**: Functions can return values to the calling scope using the `return <expression>` statement, a fundamental part of function execution.
    
-   **Print & Exit Statements**: Basic I/O is supported through the `print` statement for outputting variables or literals. The `exit` or `exit program` commands provide a clean way to terminate the REPL session.
    
-   **REPL Mode**: The interactive REPL allows you to write and execute code on the fly, providing immediate feedback and a great environment for experimenting with the language's syntax and features.
    

----------

## Project Structure

The project is organized to be clean and easy to navigate.

```
CraftLang/
├─ .vscode/             # Visual Studio Code settings
├─ include/             # Header files for the project
│  ├─ nodes/            # Defines the AST (Abstract Syntax Tree) nodes for the language
│  ├─ parser/           # Contains the grammar definition for parsing
│  └─ runtime/          # Manages the runtime context and execution environment
├─ src/                 # Source files with implementation details
│  ├─ nodes/            # Implementations of the AST nodes
│  ├─ parser/           # The parser implementation
│  ├─ runtime/          # The core runtime execution logic
│  └─ main.cpp          # The program's entry point, which handles REPL and script execution
├─ tests/               # Unit and integration tests
│  ├─ test_basic.cl     # Sample scripts for testing
│  └─ tests.cpp         # Test harness
├─ CMakeLists.txt       # CMake build configuration
├─ Makefile             # A classic Makefile for building the project
├─ .gitignore           # Specifies files to ignore in Git
└─ init_craftLang.sh    # A helper script for initial setup

```

----------

## Example Syntax

### Variable Assignment

Variables are declared with an explicit type before their name.

```
assign integer variable x to 10
assign float variable pi to 3.14
assign string variable greeting to Hello World
assign variable sum with x

```

### Function Definition & Call

Functions can have multiple parameters and a single return value.

```
define function add with parameters a, b
  assign variable result with a
  assign variable next_result with b
  return result + next_result
end
call add using 10, 20

```

### Repeat Loops

The `repeat` loop is used for simple iteration.

```
repeat 5 times
  print x
end

```

### Exiting the Program

You can use a simple command to gracefully exit the REPL.

```
exit
exit program

```

----------

## REPL Usage

To start the interactive environment, simply run the compiled executable.

Bash

```
./craftLangCompiler

```

**Example session**:

```
CraftLang REPL. Type 'exit' to quit.
> assign integer variable x to 5
> print x
5
> repeat 3 times
... print x
... end
5
5
5
> exit
Goodbye!

```

----------

## Building and Running

### Using CMake

CMake is the recommended way to build the project. It handles dependencies and configurations across different platforms.

Bash

```
mkdir build
cd build
cmake ..
make
./craftLangCompiler

```

### Using Makefile

For a more traditional approach, you can use the provided Makefile.

Bash

```
make
./craftLangCompiler

```

----------

## Dependencies

-   **C++17 or newer**: The project uses modern C++ features.
    
-   **Boost Libraries**: Specifically **Boost.Spirit** for parsing and **Boost.Phoenix** for semantic actions. These libraries are crucial for the compiler's functionality.
    
-   **Standard C++ Libraries**: The project relies on standard headers such as `<iostream>`, `<vector>`, `<string>`, `<memory>`, and `<variant>`.
    

----------

## Contributing

We welcome contributions! To get started, fork the repository and then create a feature branch.

1.  **Create a new branch**:
    
    Bash
    
    ```
    git checkout -b feature/my-new-feature
    
    ```
    
2.  **Commit your changes**:
    
    Bash
    
    ```
    git commit -m "Add my new feature"
    
    ```
    
3.  **Push your branch**:
    
    Bash
    
    ```
    git push origin feature/my-new-feature
    
    ```
    
4.  **Open a Pull Request**: Submit a PR to the main repository for review.
