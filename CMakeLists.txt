cmake_minimum_required(VERSION 3.10)

project(rla CXX)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCES
	src/Main.cpp
	src/ArchiveProcess.cpp
)

set(INCLUDE_DIR
	include
)

include_directories(${INCLUDE_DIR})


add_executable(rla ${SOURCES})
target_link_libraries(rla "-lstdc++fs")