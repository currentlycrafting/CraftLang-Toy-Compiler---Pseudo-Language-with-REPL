cmake_minimum_required(VERSION 3.16)
project(CraftLang VERSION 0.1 LANGUAGES CXX)

# Use modern C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Dependencies ----
find_package(Boost REQUIRED) # Keep this since Grammar.hpp uses Boost.Spirit

# ---- Include Directories ----
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

# ---- Source Files ----
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# ---- Main Compiler Executable ----
add_executable(craftlang ${SRC_FILES})
target_link_libraries(craftlang ${Boost_LIBRARIES})

# ---- Test Runner ----
set(TEST_SRC_FILES ${SRC_FILES})
list(REMOVE_ITEM TEST_SRC_FILES "${CMAKE_SOURCE_DIR}/src/main.cpp")

add_executable(craftlang_tests tests/tests.cpp ${TEST_SRC_FILES})
target_link_libraries(craftlang_tests ${Boost_LIBRARIES})
