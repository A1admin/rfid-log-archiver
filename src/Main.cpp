#include <iostream>
#include <string>
#include <filesystem>
#include <cctype>

// #include <7z.h>
#include "7zFile.h"
#include "7zVersion.h"
#include "Alloc.h"
#include "CpuArch.h"
#include "LzmaEnc.h"
#include "Precomp.h"
//#include <lzma.h>

#include "ArchiveProcess.h"
#include "LogArgumentDirectory.h"

// Function returns true if response is y
// anything else returns false
bool isInputValid(const char response) {
    if (std::tolower(response) == 'y') {
        return true;
    }

    return false;
}


SRes encode(ISeqOutStream *outStream, ISeqInStream *inStream, UInt64 fileSize, char *rs) {
    CLzmaEncHandle enc;
    SRes res;
    CLzmaEncProps props;

    UNUSED_VAR(rs);

    enc = LzmaEnc_Create(&g_Alloc);
    if (enc == 0) {
        return SZ_ERROR_MEM;
    }

    LzmaEncProps_Init(&props);
    std::cout << "setting props\n";
    res = LzmaEnc_SetProps(enc, &props);

    if (res == SZ_OK) {
        std::cout << "props successfully set\n";
        Byte header[LZMA_PROPS_SIZE + 8];
        size_t headerSize = LZMA_PROPS_SIZE;
        int i;

        res = LzmaEnc_WriteProperties(enc, header, &headerSize);
        for (i = 0; i < 8; i++)
            header[headerSize++] = (Byte)(fileSize >> (8 * i));
        if (outStream->Write(outStream, header, headerSize) != headerSize) {
            std::cout << "failed to write\n";
            res = SZ_ERROR_WRITE;
        } else {
            if (res == SZ_OK) {
                std::cout << "encoding\n";
                LzmaEnc_Encode(enc, outStream, inStream, NULL, &g_Alloc, &g_Alloc);
                std::cout << "finished encoding\n";
            }
        }
    }

    LzmaEnc_Destroy(enc, &g_Alloc, &g_Alloc);

    return res;
}

SRes encode2(ISeqOutStream *outStream, ISeqInStream *inStream, UInt64 fileSize, char *rs) {
    SRes res;

    return res;
}


void test(char *path, char *outPath, char *rs) {
    std::cout << "testing file compression\n";
    std::cout << "input file: " << path << "\n";
    std::cout << "output file: " << outPath << "\n";
    CFileSeqInStream inStream;
    CFileOutStream outStream;

    char c;
    int res;
    int encodeMode;
    BoolInt useOutFile = False;

    FileSeqInStream_CreateVTable(&inStream);
    File_Construct(&inStream.file);

    FileOutStream_CreateVTable(&outStream);
    File_Construct(&outStream.file);

    if (InFile_Open(&inStream.file, path) != 0) {
        std::cout << "couldn't open file to compress\n";
        return;
    }

    useOutFile = True;
    if (OutFile_Open(&outStream.file, outPath) != 0) {
        std::cout << "couldn't open output file\n";
        return;
    }

    UInt64 fileSize;
    File_GetLength(&inStream.file, &fileSize);
    std::cout << "file size: " << fileSize << " Bytes\n";

    std::cout << "starting encoding process\n";
    res = encode(&outStream.vt, &inStream.vt, fileSize, rs);
    std::cout << "encoding process complete\n";

    if (useOutFile) {
        File_Close(&outStream.file);
    }
    File_Close(&inStream.file);

    if (res != SZ_OK) {
        std::cout << "something went wrong\n";
    }
}


int main(int argc, char **argv) {
    char rs[800] = { 0 };
    test(argv[1], argv[2], rs);
    std::fputs(rs, stdout);

    std::cout << "exiting\n";

    return -1;

    if (argc < 3) {
        std::cout << "not enough arguments provided\n";
        std::cout << "to successfully run rla, follow this example\n\n";
        std::cout << "rla [source_directory_of_logs] [target_directory_of_archived_logs]\n";
        return -1;
    }

    std::cout << "starting rla\n";

    LogArgumentDirectory directories(argv[1], argv[2]);

    ArchiveProcess arcProc;

    if (!arcProc.isSourceDirectoryValid(directories)) {
        std::cout << directories.sourceLogDirectory << " is not a valid source directory where logs are contained\n";
        return -1;
    }
    if (!arcProc.isTargetDirectoryValid(directories)) {
        std::cout << directories.targetArchiveDirectory << " is not a valid directory where archived logs can be stored\n";
        return -1;
    }

    auto logs = arcProc.gatherLogs(directories);
    std::cout << "logs to archive: " << logs.size() << "\n";


    return 0;
}