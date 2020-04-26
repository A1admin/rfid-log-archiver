#include <iostream>
#include <string>
#include <filesystem>
#include <cctype>

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

int main(int argc, char **argv) {
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