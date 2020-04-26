#ifndef ARCHIVEPROCESS_H_
#define ARCHIVEPROCESS_H_

#include <vector>

#include "LogArgumentDirectory.h"
#include "RFIDLog.h"

class ArchiveProcess {
public:
    ArchiveProcess() = default;
    ArchiveProcess(const LogArgumentDirectory &dir);

    std::vector<RFIDLog> gatherLogs(const LogArgumentDirectory &dir);

    bool isSourceDirectoryValid(LogArgumentDirectory &dir);
    bool isTargetDirectoryValid(LogArgumentDirectory &dir);
private:
    void validateDirectories(LogArgumentDirectory &dir);
};

#endif