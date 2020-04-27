#include "ArchiveProcess.h"

#include <iostream>
#include <filesystem>

ArchiveProcess::ArchiveProcess(const LogArgumentDirectory &dir) {
}


std::vector<RFIDLog> ArchiveProcess::gatherLogs(const LogArgumentDirectory &dir) {
    std::vector<RFIDLog> logs;

    std::cout << "files\n";
    for (auto dir: std::filesystem::directory_iterator(std::filesystem::path(dir.sourceLogDirectory))) {
        if (dir.path().extension().string().compare(LOG_EXT()) == 0) {
            //std::cout << "here\n";
            RFIDLog log(dir.path().filename().string(), dir.path().string(), dir.path().stem().string());
            logs.push_back(log);
        }
        //std::cout << "ext: " << dir.path().extension().string() << " path: " << dir.path().string() << "\n";
    }

    return logs;
}


std::string ArchiveProcess::LOG_EXT() noexcept {
    return ".log";
}


bool ArchiveProcess::isSourceDirectoryValid(LogArgumentDirectory &dir) {
    auto result = (std::filesystem::exists(dir.sourceLogDirectory) && 
        std::filesystem::is_directory(dir.sourceLogDirectory));

    validateDirectories(dir);
    
    return result;
}

bool ArchiveProcess::isTargetDirectoryValid(LogArgumentDirectory &dir) {
    auto result = (std::filesystem::exists(dir.targetArchiveDirectory) &&
        std::filesystem::is_directory(dir.targetArchiveDirectory));

    validateDirectories(dir);

    return result;
}



SRes ArchiveProcess::encode(ISeqOutStream *outStream, ISeqInStream *inStream, UInt64 fileSize, char *rs) {
    CLzmaEncHandle enc;
    SRes res;
    CLzmaEncProps props;

    UNUSED_VAR(rs);

    enc = LzmaEnc_Create(&g_Alloc);
    if (enc == 0) {
        return SZ_ERROR_MEM;
    }

    LzmaEncProps_Init(&props);
    props.level = 9;
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


void ArchiveProcess::compressLogs(const std::vector<RFIDLog> &logs, const LogArgumentDirectory &dir) {
    for (auto &log: logs) {
        std::cout << "compressing log file: " << log.filename << " ";
        std::string outPath(dir.targetArchiveDirectory);
        outPath.append("/");
        outPath.append(log.stem);
        outPath.append(".lzma");
        std::cout << "archived path will be: " << outPath << "\n";

        CFileSeqInStream inStream;
        CFileOutStream outStream;

        char c;
        char rs[800] = { 0 };
        int res;
        int encodeMode;
        BoolInt useOutFile = False;

        auto usingOutFile = prepareArchive(&inStream, &outStream, log.path, outPath);
        /**
        FileSeqInStream_CreateVTable(&inStream);
        File_Construct(&inStream.file);

        FileOutStream_CreateVTable(&outStream);
        File_Construct(&outStream.file);

        if (InFile_Open(&inStream.file, log.path.c_str()) != 0) {
            std::cout << "couldn't open input file\n";
            return;
        }

        useOutFile = True;
        if (OutFile_Open(&outStream.file, outPath.c_str()) != 0) {
            std::cout << "couldn't open output file\n";
            return;
        }
        */

        UInt64 fileSize;
        File_GetLength(&inStream.file, &fileSize);
        std::cout << "file size: " << fileSize << " Bytes\n";
        std::cout << "starting encoding process\n";
        res = encode(&outStream.vt, &inStream.vt, fileSize, rs);
        std::cout << "encoding process complete\n";

        closeFiles(&inStream, &outStream);
        //if (useOutFile) {
        /**
        if (usingOutFile) {
            File_Close(&outStream.file);
        }
        File_Close(&inStream.file);
        */

        if (res != SZ_OK) {
            std::cout << "something went wrong\n";
        }
    }
}


bool ArchiveProcess::prepareArchive(CFileSeqInStream *inStream, CFileOutStream *outStream, const std::string &inputPath, 
        const std::string &outputPath) {

        FileSeqInStream_CreateVTable(inStream);
        File_Construct(&inStream->file);

        FileOutStream_CreateVTable(outStream);
        File_Construct(&outStream->file);

        if (InFile_Open(&inStream->file, inputPath.c_str()) != 0) {
            std::cout << "couldn't open input file\n";
            return false;
        }

        //useOutFile = True;
        if (OutFile_Open(&outStream->file, outputPath.c_str()) != 0) {
            std::cout << "couldn't open output file\n";
            return false;
        }

    return true;
}



void ArchiveProcess::closeFiles(CFileSeqInStream *inStream, CFileOutStream *outStream, bool usingOutFile) {
    if (usingOutFile) {
        File_Close(&outStream->file);
    }
    File_Close(&inStream->file);
}

void ArchiveProcess::validateDirectories(LogArgumentDirectory &dir) {
    dir.directoriesValidated = true;
}