#include "ArchiveProcess.h"

#include <filesystem>

ArchiveProcess::ArchiveProcess(const LogArgumentDirectory &dir) {
}


std::vector<RFIDLog> ArchiveProcess::gatherLogs(const LogArgumentDirectory &dir) {
    std::vector<RFIDLog> logs;

    return logs;
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


void ArchiveProcess::validateDirectories(LogArgumentDirectory &dir) {
    dir.directoriesValidated = true;
}