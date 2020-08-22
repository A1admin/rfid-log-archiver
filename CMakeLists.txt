cmake_minimum_required(VERSION 3.10)

project(rla)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# C 7z SDK root directory
option (7Z_ROOT_C "7Z_ROOT_C" "")

set (SOURCES
    src/Main.cpp
    src/ArchiveProcess.cpp
)

set (INCLUDE_DIR
    include
)

set (7Z_LZMA_OBJS_C
    ${7Z_ROOT_C}/Util/lzma/7zFile.o
    ${7Z_ROOT_C}/Util/lzma/7zStream.o
    ${7Z_ROOT_C}/Util/lzma/Alloc.o
    ${7Z_ROOT_C}/Util/lzma/LzFind.o
    ${7Z_ROOT_C}/Util/lzma/LzmaDec.o
    ${7Z_ROOT_C}/Util/lzma/LzmaEnc.o
)

include_directories (${INCLUDE_DIR} ${7Z_ROOT_C}/Util/lzma ${7Z_ROOT_C})

add_executable (rla ${SOURCES} ${7Z_LZMA_OBJS_C})
target_link_libraries (rla "-lstdc++fs")
