cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0091 NEW)

project(kub)
file(GLOB_RECURSE kub_src CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${kub_src}
        src/kub.h
        src/lexer.h
        src/parser.cpp
        src/parser.h)