cmake_minimum_required (VERSION 2.6)

project (AlfBootClient)

add_definitions(-std=c++11)

include_directories(bots)

link_directories( ${link_directories} ./bots )

add_executable(AlfBootClient main.cpp)


