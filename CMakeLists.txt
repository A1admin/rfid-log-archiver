cmake_minimum_required(VERSION 3.10)

project(rla)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

option(7Z_OBJ_PATH "7Z_OBJ_PATH" "/mnt/c/Users/Kun/Temporary/Downloads/Development/lzma1900/CPP/7zip/Bundles/LzmaCon")
option(7Z_INCLUDE_PATH "7Z_INCLUDE_PATH" "/mnt/c/Users/Kun/Temporary/Downloads/Development/lzma1900/CPP/7zip/Common")

# message(${7Z_OBJ_PATH})
#message(${7Z_INCLUDE_PATH})

# C 7z lib
option(7Z_ROOT_C "7Z_ROOT_C" "")
#option(7Z_7Z_OBJ_C "7Z_7Z_OBJ_C" "/mnt/c/Users/Kun/Temporary/Downloads/Development/lzma1900/C/Util/7z")
#option(7Z_7Z_SOURCE_DIR_C "7Z_7Z_SOURCE_DIR_C" "/mnt/c/Users/Kun/Temporary/Downloads/Development/lzma1900/C/Util/7z")
#option(7Z_7Z_INCLUDE_DIR_C "7Z_7Z_INCLUDE_DIR_C" "/mnt/c/Users/Kun/Temporary/Downloads/Development/lzma1900/C/Util/7z")
#option(7Z_INCLUDE_DIR_C "7Z_INCLUDE_DIR_C" "/mnt/c/Users/Kun/Temporary/Downloads/Development/lzma1900/C")

#message(${7Z_7Z_OBJ_C})
#message(${7Z_7Z_SOURCE_DIR_C})
#message(${7Z_7Z_INCLUDE_DIR_C})
#message(${7Z_INCLUDE_DIR_C})
message(${7Z_ROOT_C})

set(SOURCES
	src/Main.cpp
	src/ArchiveProcess.cpp
)

set(INCLUDE_DIR
	include
)

SET(OBJS
  ${7Z_OBJ_PATH}/7zCrc.o
  ${7Z_OBJ_PATH}/7zCrcOpt.o
  ${7Z_OBJ_PATH}/Alloc.o
  ${7Z_OBJ_PATH}/Bench.o
  ${7Z_OBJ_PATH}/BenchCon.o
  ${7Z_OBJ_PATH}/Bra86.o
  ${7Z_OBJ_PATH}/CRC.o
  ${7Z_OBJ_PATH}/CWrappers.o
  ${7Z_OBJ_PATH}/C_FileIO.o
  ${7Z_OBJ_PATH}/CommandLineParser.o
  ${7Z_OBJ_PATH}/ConsoleClose.o
  ${7Z_OBJ_PATH}/CpuArch.o
  ${7Z_OBJ_PATH}/CrcReg.o
  ${7Z_OBJ_PATH}/CreateCoder.o
  ${7Z_OBJ_PATH}/FileStreams.o
  ${7Z_OBJ_PATH}/FilterCoder.o
  ${7Z_OBJ_PATH}/IntToString.o
  ${7Z_OBJ_PATH}/LzFind.o
  ${7Z_OBJ_PATH}/Lzma86Dec.o
  ${7Z_OBJ_PATH}/Lzma86Enc.o
  # ${7Z_OBJ_PATH}/LzmaAlone.o
  ${7Z_OBJ_PATH}/LzmaDec.o
  ${7Z_OBJ_PATH}/LzmaDecoder.o
  ${7Z_OBJ_PATH}/LzmaEnc.o
  ${7Z_OBJ_PATH}/LzmaEncoder.o
  ${7Z_OBJ_PATH}/LzmaRegister.o
  ${7Z_OBJ_PATH}/MethodProps.o
  ${7Z_OBJ_PATH}/MyString.o
  ${7Z_OBJ_PATH}/MyVector.o
  ${7Z_OBJ_PATH}/MyWindows.o
  ${7Z_OBJ_PATH}/PropVariant.o
  ${7Z_OBJ_PATH}/StreamUtils.o
  ${7Z_OBJ_PATH}/StringConvert.o
  ${7Z_OBJ_PATH}/StringToInt.o
  ${7Z_OBJ_PATH}/System.o
)

set(7Z_SOURCES_C
	${7Z_ROOT_C}/7zAlloc.c
	${7Z_ROOT_C}/7zArcIn.c
	${7Z_ROOT_C}/7zBuf.c
	${7Z_ROOT_C}/7zBuf2.c
	${7Z_ROOT_C}/7zCrc.c
	${7Z_ROOT_C}/7zCrcOpt.c
	${7Z_ROOT_C}/7zDec.c
	${7Z_ROOT_C}/7zFile.c
	${7Z_ROOT_C}/7zStream.c
	${7Z_ROOT_C}/Aes.c
	${7Z_ROOT_C}/AesOpt.c
	${7Z_ROOT_C}/Alloc.c
	${7Z_ROOT_C}/Bcj2.c
	${7Z_ROOT_C}/Bcj2Enc.c
	${7Z_ROOT_C}/Bra.c
	${7Z_ROOT_C}/Bra86.c
	${7Z_ROOT_C}/BraIA64
	# ${7Z_ROOT_C}/
)

SET(7Z_7Z_OBJS_C
	${7Z_ROOT_C}/Util/7z/7zAlloc.o
	${7Z_ROOT_C}/Util/7z/7zArcIn.o
	${7Z_ROOT_C}/Util/7z/7zBuf.o
	${7Z_ROOT_C}/Util/7z/7zBuf2.o
	${7Z_ROOT_C}/Util/7z/7zCrc.o
	${7Z_ROOT_C}/Util/7z/7zCrcOpt.o
	${7Z_ROOT_C}/Util/7z/7zDec.o
	${7Z_ROOT_C}/Util/7z/7zFile.o
	# ${7Z_ROOT_C}/Util/7z/7ZMain.o
	${7Z_ROOT_C}/Util/7z/7zStream.o
	${7Z_ROOT_C}/Util/7z/Bcj2.o
	${7Z_ROOT_C}/Util/7z/Bra.o
	${7Z_ROOT_C}/Util/7z/Bra86.o
	${7Z_ROOT_C}/Util/7z/BraIA64.o
	${7Z_ROOT_C}/Util/7z/CpuArch.o
	${7Z_ROOT_C}/Util/7z/Delta.o
	${7Z_ROOT_C}/Util/7z/Lzma2Dec.o
	${7Z_ROOT_C}/Util/7z/LzmaDec.o
	${7Z_ROOT_C}/Util/7z/Ppmd7.o
	${7Z_ROOT_C}/Util/7z/Ppmd7Dec.o
)

set(7Z_LZMA_OBJS_C
	${7Z_ROOT_C}/Util/Lzma/7zFile.o
	${7Z_ROOT_C}/Util/Lzma/7zStream.o
	${7Z_ROOT_C}/Util/Lzma/Alloc.o
	${7Z_ROOT_C}/Util/Lzma/LzFind.o
	${7Z_ROOT_C}/Util/Lzma/LzmaDec.o
	${7Z_ROOT_C}/Util/Lzma/LzmaEnc.o
	# ${7Z_ROOT_C}/Util/Lzma/LzmaUtil.o
)

SET(7Z_7Z_SOURCES_C
	${7Z_ROOT_C}/Util/7Z/PreComp.c
)

set(7Z_LZMA_SOURCES_C
	${7Z_ROOT_C}/Util/Lzma/LzmaUtil.c
)

SET(7Z_SOURCES
	${7Z_INCLUDE_PATH}/CWrappers.cpp
	${7Z_INCLUDE_PATH}/CreateCoder.cpp
	${7Z_INCLUDE_PATH}/FilePathAutoRename.cpp
	${7Z_INCLUDE_PATH}/FileStreams.cpp
	${7Z_INCLUDE_PATH}/FilterCoder.cpp
	${7Z_INCLUDE_PATH}/InBuffer.cpp
	${7Z_INCLUDE_PATH}/InOutTempBuffer.cpp
	${7Z_INCLUDE_PATH}/LimitedStreams.cpp
	${7Z_INCLUDE_PATH}/LockedStream.cpp
	${7Z_INCLUDE_PATH}/MethodId.cpp
	${7Z_INCLUDE_PATH}/OffsetStream.cpp
	${7Z_INCLUDE_PATH}/OutBuffer.cpp
	${7Z_INCLUDE_PATH}/ProgressUtils.cpp
	${7Z_INCLUDE_PATH}/PropId.cpp
	${7Z_INCLUDE_PATH}/StreamBinder.cpp
	${7Z_INCLUDE_PATH}/StreamObjects.cpp
	${7Z_INCLUDE_PATH}/StreamUtils.cpp
	${7Z_INCLUDE_PATH}/UniqBlocks.cpp
	${7Z_INCLUDE_PATH}/VirtThread.cpp
)

SET_SOURCE_FILES_PROPERTIES(
  ${OBJS}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

# include_directories(${INCLUDE_DIR} ${7Z_INCLUDE_PATH})
# include_directories(${INCLUDE_DIR} ${7Z_7Z_INCLUDE_DIR})
# include_directories(${INCLUDE_DIR} ${7Z_ROOT_C}/Util/7z ${7Z_ROOT_C})
include_directories(${INCLUDE_DIR} ${7Z_ROOT_C}/Util/Lzma ${7Z_ROOT_C})
# include_directories(${INCLUDE_DIR} ${7Z_ROOT_C}/Util/7z ${7Z_ROOT_C}/Util/Lzma ${7Z_ROOT_C})


# add_executable(rla ${SOURCES} ${OBJS} ${7Z_SOURCES})
# add_executable(rla ${SOURCES} ${7Z_SOURCES_C} ${7Z_7Z_OBJS_C} ${7Z_7Z_SOURCES_C})
# add_executable(rla ${SOURCES} ${7Z_7Z_OBJS_C} ${7Z_7Z_SOURCES_C})
add_executable(rla ${SOURCES} ${7Z_LZMA_OBJS_C})
# add_executable(rla ${SOURCES} ${7Z_7Z_OBJS_C} ${7Z_7Z_SOURCES_C} ${7Z_LZMA_OBJS_C} ${7Z_LZMA_SOURCES_C})
# add_executable(rla ${SOURCES})
target_link_libraries(rla "-lstdc++fs")