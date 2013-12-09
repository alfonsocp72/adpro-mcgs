cmake_minimum_required (VERSION 2.6)

project (AlfBotClient)

add_definitions(-std=c++11)

include_directories(bots)

link_directories( ${link_directories} ./bots )

add_executable(AlfBotClient main.cpp)
target_link_libraries(AlfBotClient bots)



