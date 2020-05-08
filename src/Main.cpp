/*
 * Purpose: rla is a compression and archiving software created to address the 
 * issue of logs consuming storage space on the server.
 * 
 * Writer: Kun Deng
 * 
 */

#include <iostream>
#include <string>
#include <filesystem>

#include "ArchiveProcess.h"
#include "LogArgumentDirectory.h"


void printHelp() {
    std::cout << "rla [action] [source_directory_of_logs] [target_directory_of_archived_logs] (days)\n";
    std::cout << "\nsuported actions\n";
    std::cout << "* single - compresses single log file from the previous day. If log file does not exist or\n";
    std::cout << "\tif the comrpessed archive file does exist, nothing will happen\n";
    std::cout << "* singledel - similar to the single action but the log file is deleted at the end\n";
    std::cout << "* singletest - similar to the single action but the days numerical value is required\n";
    std::cout << "\t\tdirectories\n";
    std::cout << "* singletestdel - similar to the singletest action except the log file is deleted at the end\n\n";
    std::cout << "* [source_directory_of_logs] - root directory in which logs are stored\n";
    std::cout << "* [target_directory_of_archived_logs] - target directory where archived logs will be stored\n";
    std::cout <<"\noptional:\n";
    std::cout << "* days - only required when given the singletest action\n";
}


int main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "run rla with help to get more information\n";
        std::cout << "rla help\n";
        return -1;
    }

    std::cout << "starting rla\n";
    const std::string chosenAction(argv[1]);

    // by default the previous day's log is compressed
    int daysToAdd = -1;
    ArchiveProcess arcProc(daysToAdd);
    auto result = arcProc.isActionValid(chosenAction);
    if (!result.first) {
        std::cout << chosenAction << " is an invalid action\n";
        return -1;
    }
    if (result.second == ArchiveProcess::ACTIONS::HELP) {
        printHelp();
        return -1;
    }

    std::cout << "chosen action: " << chosenAction << "\n";

    LogArgumentDirectory<std::string> directories(argv[2], argv[3]);

    if (argc < 4) {
        std::cout << "not enough arguments provided\n";
        std::cout << "to successfully run rla, follow this example\n\n";
        std::cout << "rla [action] [source_directory_of_logs] [target_directory_of_archived_logs]\n";
        std::cout << "**rla help** for more information\n";
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

    // if any of the single test actions are used a day value can be provided
    switch (result.second) {
    case ArchiveProcess::ACTIONS::SINGLETEST:
        if (argc < 5) {
            std::cout << "no days argument provided\nexiting...\n";
            return -1;
        }
        daysToAdd = std::atoi(argv[4]);
        std::cout << "days to add: " << daysToAdd << "\n";
        arcProc = ArchiveProcess(daysToAdd);
        break;
    case ArchiveProcess::ACTIONS::SINGLETESTDEL:
        if (argc < 5) {
            std::cout << "no days argument provided\nexiting...\n";
            return -1;
        }
        daysToAdd = std::atoi(argv[4]);
        std::cout << "days to add: " << daysToAdd << "\n";
        arcProc = ArchiveProcess(daysToAdd);
        break;
    }

    arcProc.compressLogProcess(directories, result.second);

    return 0;
}