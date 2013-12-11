cmake_minimum_required (VERSION 2.6)

project (AlfBotClient)

find_package(Boost 1.40.0 REQUIRED COMPONENTS system thread serialization)
include_directories(${Boost_INCLUDE_DIR})

add_definitions(-std=c++11)

include_directories(bots)

link_directories( ${link_directories} ./bots )

add_executable(AlfBotClient main.cpp)

target_link_libraries(AlfBotClient bots)
target_link_libraries(AlfBotClient ${Boost_LIBRARIES})
target_link_libraries(AlfBotClient pthread)



