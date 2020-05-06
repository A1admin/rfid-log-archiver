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
    //char rs[800] = { 0 };
    //test(argv[1], argv[2], rs);
    //test(argc, argv, rs);
    //std::fputs(rs, stdout);

    //std::cout << "exiting\n";

    //return -1;

    if (argc < 4) {
        std::cout << "not enough arguments provided\n";
        std::cout << "to successfully run rla, follow this example\n\n";
        //std::cout << "rla [source_directory_of_logs] [target_directory_of_archived_logs]\n";
        std::cout << "rla [action] [source_directory_of_logs] [target_directory_of_archived_logs]\n";
        return -1;
    }

    std::cout << "starting rla\n";
    const std::string chosenAction(argv[1]);
    std::cout << "chosen action: " << chosenAction << "\n";
    std::cout << "goodbye\n";

    LogArgumentDirectory directories(argv[2], argv[3]);

    ArchiveProcess arcProc;
    auto result = arcProc.isActionValid(chosenAction);
    if (!result.first) {
        std::cout << chosenAction << " is an invalid action\n";
        return -1;
    }

    if (!arcProc.isSourceDirectoryValid(directories)) {
        std::cout << directories.sourceLogDirectory << " is not a valid source directory where logs are contained\n";
        return -1;
    }
    if (!arcProc.isTargetDirectoryValid(directories)) {
        std::cout << directories.targetArchiveDirectory << " is not a valid directory where archived logs can be stored\n";
        return -1;
    }

    arcProc.compressLogProcess(directories, result.second);
    /**
    switch (result.second) {
        ArchiveProcess::ACTIONS::SINGLE:
            arcProc.compressLogProcess(directories, )
            break;
        ArchiveProcess::ACTIONS::ALL:
            break;
        ArchiveProcess::ACTIONS::NONE:
            std::cout << "no valid action\n";
            return -1;
            break;
        default;
            std::cout << "no valid action\n";
            return -1;
            break;
    }
    */

    return -1;
    auto logs = arcProc.gatherLogs(directories);
    std::cout << "logs to archive: " << logs.size() << "\n";
    // TODO: implement way a directory structure is created for the target directory
    //
    // TODO: Check to see if a log has already been archived. Wouldn't want to re-archive
    // a log that already exists
    arcProc.compressLogs(logs, directories);


    return 0;
}