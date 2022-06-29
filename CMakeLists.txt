cmake_minimum_required(VERSION 3.21)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# APEX.dll
project(apex)
add_library(apex SHARED
    src/APEX/DllMain.cpp
)

# injector.exe
project(injector)
add_executable(injector src/injector.cpp)
