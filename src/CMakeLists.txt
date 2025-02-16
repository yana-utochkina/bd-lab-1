cmake_minimum_required(VERSION 3.30)
project(src)

set(CMAKE_CXX_STANDARD 20)

add_executable(src main.cpp
        Models/Visit.cpp
        Models/User.cpp
        functions.cpp
        Models/GarbageCollector.cpp
        Models/IndexTable.cpp
        files.cpp
)
