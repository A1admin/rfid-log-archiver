cmake_minimum_required(VERSION 3.10)

project(rla)



# C 7z SDK root directory
option(7Z_ROOT_C "7Z_ROOT_C" "")

message(${7Z_ROOT_C})

set(SOURCES
	src/Main.cpp
	src/ArchiveProcess.cpp
)

set(INCLUDE_DIR
	include
)


set(7Z_LZMA_OBJS_C
	${7Z_ROOT_C}/Util/Lzma/Release/7zFile.obj
	${7Z_ROOT_C}/Util/Lzma/Release/7zStream.obj
	${7Z_ROOT_C}/Util/Lzma/Release/Alloc.obj
	${7Z_ROOT_C}/Util/Lzma/Release/LzFind.obj
	${7Z_ROOT_C}/Util/Lzma/Release/LzFindMt.obj
	${7Z_ROOT_C}/Util/Lzma/Release/LzmaDec.obj
	${7Z_ROOT_C}/Util/Lzma/Release/LzmaEnc.obj
	# ${7Z_ROOT_C}/Util/Lzma/Release/LzmaUtil.obj
	${7Z_ROOT_C}/Util/Lzma/Release/Threads.obj
)


include_directories(${INCLUDE_DIR} ${7Z_ROOT_C}/Util/Lzma ${7Z_ROOT_C})


add_executable(rla ${SOURCES} ${7Z_LZMA_OBJS_C})

set_property(TARGET rla PROPERTY CXX_STANDARD 17)
set_property(TARGET rla PROPERTY CXX_STANDARD_REQUIRED ON)