cmake_minimum_required(VERSION 3.10)

project(Sudoku)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(include)

file(GLOB SRC
    "src/*.cpp"
)

add_executable(sudoku sudoku.cpp ${SRC})

if(WIN32 AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    target_link_options(sudoku PRIVATE -Wl,--stack,16777216)
endif()
