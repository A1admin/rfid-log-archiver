#include "ArchiveProcess.h"

#include <iostream>
#include <chrono>
#include <algorithm>
#include <filesystem>
#include <cctype>
#include <ctime>
#include <sstream>
#include <iomanip>

ArchiveProcess::ArchiveProcess() : m_day(-1) { }
ArchiveProcess::ArchiveProcess(const int day) : m_day(day) { }
ArchiveProcess::ArchiveProcess(const LogArgumentDirectory<std::string> &dir) : m_day(-1) { }
ArchiveProcess::ArchiveProcess(const LogArgumentDirectory<std::string> &dir, const int day) : m_day(day) { }


std::vector<RFIDLog<std::string>> ArchiveProcess::gatherLogs(const LogArgumentDirectory<std::string> &dir) {
    std::vector<RFIDLog<std::string>> logs;

    std::cout << "files\n";
    for (auto dir: std::filesystem::directory_iterator(std::filesystem::path(dir.sourceLogDirectory))) {
        const std::string dirPathExtStr = dir.path().extension().string();
        if (dirPathExtStr.compare(LOG_EXT()) == 0) {
            RFIDLog<std::string> log(dir.path().filename().string(), dir.path().string(), dir.path().stem().string());
            logs.push_back(log);
        }
    }

    return logs;
}


std::string ArchiveProcess::LOG_EXT() noexcept {
    return ".log";
}

std::string ArchiveProcess::LOG_ARCHIVE_EXT() noexcept {
    return ".lzma";
}

std::pair<bool, ArchiveProcess::ACTIONS> ArchiveProcess::isActionValid(const std::string &action) {
    std::string lowerCaseAction(action);
    std::for_each(lowerCaseAction.begin(), lowerCaseAction.end(), [](char &c) {
        if (std::isupper(c))
            c = std::tolower(c);

        return c;
    });

    std::cout << "action without alteration: " << action << "\n";
    std::cout << "action after altercation: " << lowerCaseAction << "\n";

    auto actions = allActions();
    bool result = false;
    ACTIONS act = ACTIONS::NONE;
    for (auto &val : actions) {
        if (lowerCaseAction.compare(val) == 0) {
            if (lowerCaseAction.compare(actions[0]) == 0) {
                act = ACTIONS::SINGLE;
            } else if (lowerCaseAction.compare(actions[1]) == 0) {
                act = ACTIONS::SINGLEDEL;
            } else if (lowerCaseAction.compare(actions[2]) == 0) {
                act = ACTIONS::ALL;
            } else if (lowerCaseAction.compare(actions[3]) == 0) {
                act = ACTIONS::SINGLETEST;
            } else if (lowerCaseAction.compare(actions[4]) == 0) {
                act = ACTIONS::SINGLETESTDEL;
            } else if (lowerCaseAction.compare(actions[5]) == 0) {
                act = ACTIONS::HELP;
            }
            result = true;
            break;
        }
    }

    return std::pair<bool, ACTIONS>(result, act);
}

bool ArchiveProcess::isSourceDirectoryValid(LogArgumentDirectory<std::string> &dir) {
    if (dir.sourceLogDirectory.at(dir.sourceLogDirectory.size() - 1) != '/') {
        dir.sourceLogDirectory.append("/");
    }
    auto result = (std::filesystem::exists(dir.sourceLogDirectory) && 
        std::filesystem::is_directory(dir.sourceLogDirectory));

    validateDirectories(dir);
    
    return result;
}

bool ArchiveProcess::isTargetDirectoryValid(LogArgumentDirectory<std::string> &dir) {
    if (dir.targetArchiveDirectory.at(dir.targetArchiveDirectory.size() -1) != '/') {
        dir.targetArchiveDirectory.append("/");
    }
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


void ArchiveProcess::compressLogProcess(const LogArgumentDirectory<std::string> &dir, ArchiveProcess::ACTIONS act) {
    std::vector<RFIDLog<std::string>> logs;
    
    std::string archiveName("RFID-API-");
    std::string logName(generateLogName());

    switch (act) {
    case ACTIONS::ALL:
        std::cout << "not implemented\n";
        break;
    case ACTIONS::SINGLE:
        std::cout << "single action target chosen\n";
        compressSingleLog(dir);
        break;
    case ACTIONS::SINGLEDEL:
        std::cout << "single delete action target chosen\n";
        compressSingleLog(dir, true);
        break;
    case ACTIONS::SINGLETEST:
        std::cout << "singletest action target chosen\n";
        compressSingleLog(dir);
        break;
    case ACTIONS::SINGLETESTDEL:
        std::cout << "singletest delete action target chosen\n";
        compressSingleLog(dir, true);
        break;
    case ACTIONS::NONE:
        std::cout << "not implemented\n";
        break;
    default:
        break;
    }
}


void ArchiveProcess::compressLogs(const std::vector<RFIDLog<std::string>> &logs, const LogArgumentDirectory<std::string> &dir) {
    for (auto &log: logs) {
        std::cout << "compressing log file: " << log.filename << " ";
        std::string outPath(dir.targetArchiveDirectory);
        outPath.append(log.stem);
        outPath.append(LOG_ARCHIVE_EXT());
        std::cout << "archived path will be: " << outPath << "\n";

        CFileSeqInStream inStream;
        CFileOutStream outStream;

        char c;
        char rs[800] = { 0 };
        int res;
        int encodeMode;
        BoolInt useOutFile = False;

        auto usingOutFile = prepareArchive(&inStream, &outStream, log.path, outPath);

        UInt64 fileSize;
        File_GetLength(&inStream.file, &fileSize);
        std::cout << "file size: " << fileSize << " Bytes\n";
        std::cout << "starting encoding process\n";
        res = encode(&outStream.vt, &inStream.vt, fileSize, rs);
        std::cout << "encoding process complete\n";

        closeFiles(&inStream, &outStream);
        if (usingOutFile) {
            File_Close(&outStream.file);
        }
        File_Close(&inStream.file);

        if (res != SZ_OK) {
            std::cout << "something went wrong\n";
        }
    }
}

void ArchiveProcess::compressSingleLog(const LogArgumentDirectory<std::string> &dir, const bool deleteLogFile) {
    const auto logPath = inputLogPath(dir);
    auto logFile = std::filesystem::path(logPath);

    std::cout << "log to compress " << logFile << "\n";
    if (!std::filesystem::exists(logFile)) {
        std::cout << "cannot compress log file that does not exists\n";
        return;
    }

    std::cout << "log file exists... checking to see if directory structure has been created\n";
    RFIDLog<std::string> log(logFile.filename().string(), logFile.string(), logFile.stem().string());
    if (!isTargetArchiveDirectoryValid(dir)) {
        createTargetDirectoryStructure(dir);
    }

    const auto outPath = outputLogArchivePath(dir, log);

    std::cout << "output archive path: " << outPath << "\n";
    std::cout << "checking to see if log has already been compressed...\n";
    if (std::filesystem::exists(outPath)) {
        std::cout << "log " << log.filename << " has already been archived\n";
        return;
    }

    CFileSeqInStream inStream;
    CFileOutStream outStream;

    char c;
    char rs[800] = { 0 };
    int res;
    int encodeMode;
    BoolInt useOutFile = False;

    auto usingOutFile = prepareArchive(&inStream, &outStream, log.path, outPath);

    UInt64 fileSize;
    File_GetLength(&inStream.file, &fileSize);
    std::cout << "file size: " << fileSize << " Bytes\n";
    std::cout << "starting encoding process\n";
    res = encode(&outStream.vt, &inStream.vt, fileSize, rs);
    std::cout << "encoding process complete\n";

    closeFiles(&inStream, &outStream);

    if (res != SZ_OK) {
        std::cout << "something went wrong\n";
        return;
    }
    
    if (deleteLogFile) this->deleteLogFile(log, outPath);
}


std::string ArchiveProcess::generateLogName() {
    std::string archiveName("RFID-API-");
    auto date = dateValues(m_day);
    int year, month, day;


    year = std::get<0>(date);
    month = std::get<1>(date);
    day = std::get<2>(date);
    archiveName.append(std::to_string(year));

    archiveName.append("-");

    if (month > 9) {
        archiveName.append(std::to_string(month));
    } else {
        archiveName.append("0");
        archiveName.append(std::to_string(month));
    }

    archiveName.append("-");

    if (day > 9) {
        archiveName.append(std::to_string(day));
    } else {
        archiveName.append("0");
        archiveName.append(std::to_string(day));
    }

    return archiveName;
}

std::string ArchiveProcess::monthStringValue(const int month) {
    std::string monthVal;
    switch (month) {
        case 1:
            monthVal.assign("January");
            break;
        case 2:
            monthVal.assign("February");
            break;
        case 3:
            monthVal.assign("March");
            break;
        case 4:
            monthVal.assign("April");
            break;
        case 5:
            monthVal.assign("May");
            break;
        case 6:
            monthVal.assign("June");
            break;
        case 7:
            monthVal.assign("July");
            break;
        case 8:
            monthVal.assign("August");
            break;
        case 9:
            monthVal.assign("September");
            break;
        case 10:
            monthVal.assign("October");
            break;
        case 11:
            monthVal.assign("November");
            break;
        case 12:
            monthVal.assign("December");
            break;
        default:
            monthVal.assign("January");
            break;
    }

    return monthVal;
}

std::string ArchiveProcess::inputLogPath(const LogArgumentDirectory<std::string> &dir) {
    std::string logPath(dir.sourceLogDirectory);
    logPath.append(generateLogName());
    logPath.append(LOG_EXT());

    return logPath;
}

std::string ArchiveProcess::outputLogArchiveDirectory(const LogArgumentDirectory<std::string> &dir) {
    std::string logPath(outputLogArchiveDirectoryYear(dir));
    auto date = dateValues(m_day);
    auto monthStr = monthStringValue(std::get<1>(date));
    logPath.append(monthStr);
    logPath.append("/");

    return logPath;
}

std::string ArchiveProcess::outputLogArchiveDirectoryYear(const LogArgumentDirectory<std::string> &dir) {
    std::string logPartialPath(dir.targetArchiveDirectory);
    auto date = dateValues(m_day);
    logPartialPath.append(std::to_string(std::get<0>(date)));
    logPartialPath.append("/");

    return logPartialPath;
}

std::string ArchiveProcess::outputLogArchivePath(const LogArgumentDirectory<std::string> &dir, 
        const RFIDLog<std::string> &log) {
    std::string outPath(outputLogArchiveDirectory(dir));
    outPath.append(log.stem);
    outPath.append(LOG_ARCHIVE_EXT());

    return outPath;
}


std::tuple<int, int, int> ArchiveProcess::dateValues(const int days) {
    int year, month, day;

    std::stringstream ss;
    std::string time("");
    std::chrono::system_clock::time_point now;

    if (days == 0) {
        now = std::chrono::system_clock::now();
    } else {
        now = std::chrono::system_clock::now() + std::chrono::hours(24 * days);
    }

    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    time.assign(ss.str());

    year = std::atoi(time.substr(0, 4).c_str());
    month = std::atoi(time.substr(5, 2).c_str());
    day = std::atoi(time.substr(8, 2).c_str());

    auto date = std::tuple<int, int, int>(year, month, day);

    return date;
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

        if (OutFile_Open(&outStream->file, outputPath.c_str()) != 0) {
            std::cout << "couldn't open output file\n";
            return false;
        }

    return true;
}

bool ArchiveProcess::isTargetArchiveDirectoryValid(const LogArgumentDirectory<std::string> &dir) {
    bool result = false;
    std::string directory(outputLogArchiveDirectoryYear(dir));
    std::cout << directory << "\n";

    if (!std::filesystem::exists(directory)) {
        std::cout << "year sub-directory does not exist: " << directory << "\n";
        return result;
    }

    directory.assign(outputLogArchiveDirectory(dir));

    std::cout << directory << "\n";
    if (!std::filesystem::exists(directory)) {
        std::cout << "month sub-directory does not exists: " << directory << "\n";
        return result;
    }

    result = true;

    return result;
}


void ArchiveProcess::closeFiles(CFileSeqInStream *inStream, CFileOutStream *outStream, bool usingOutFile) {
    if (usingOutFile) {
        File_Close(&outStream->file);
    }
    File_Close(&inStream->file);
}

void ArchiveProcess::deleteLogFile(const RFIDLog<std::string> &log, const std::string &outPath) {
    if (std::filesystem::exists(outPath)) {
        std::cout << "log file successfully archived\n";
        std::cout << "deleting log file " << log.path << "\n";
        std::filesystem::remove(std::filesystem::path(log.path));
    } else {
        std::cout << "log file " << log.path << " does not exist\n";
    }
}

void ArchiveProcess::validateDirectories(LogArgumentDirectory<std::string> &dir) {
    dir.directoriesValidated = true;
}

void ArchiveProcess::createTargetDirectoryStructure(const LogArgumentDirectory<std::string> &dir) {
    std::cout << "creating archive directory structure\n";
    
    std::string directory(outputLogArchiveDirectoryYear(dir));
    if (!std::filesystem::exists(directory)) {
        std::cout << "created year sub-directory: " << directory << "\n";
        std::filesystem::create_directory(directory);
    }

    directory.assign(outputLogArchiveDirectory(dir));
    if (!std::filesystem::exists(directory)) {
        std::cout << "created month sub-directory: " << directory << "\n";
        std::filesystem::create_directory(directory);
    }
}