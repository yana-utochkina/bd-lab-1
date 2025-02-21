cmake_minimum_required(VERSION 3.29.5)
project(src)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(src main.cpp
        Models/Visit.cpp
        Models/User.cpp
        functions.cpp
        Models/GarbageCollector.cpp
        Models/IndexTable.cpp
        files.cpp
        Menu.cpp
)
