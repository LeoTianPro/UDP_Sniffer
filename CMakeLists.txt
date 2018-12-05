cmake_minimum_required(VERSION 3.12)

project(WinPcapApp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Log.cpp HeaderFile/Log.h Network_Card.cpp HeaderFile/Network_Card.h Get_Package.cpp HeaderFile/Get_Package.h HeaderFile/header.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libstdc++ -static-libgcc -static") #静态编译

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/WpdPack/Include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/WpdPack/Lib/x64)

link_libraries(wpcap.lib;ws2_32.lib)

add_definitions(-DWPCAP)
add_definitions(-DHAVE_REMOTE)

add_executable(WinPcapApp ${SOURCE_FILES})
