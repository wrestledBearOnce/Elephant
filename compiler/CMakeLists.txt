﻿
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable (compile 
    "main.cpp"
    "main.h"    
    "lexer.h"
    "lexer.cpp" "ast.h")

