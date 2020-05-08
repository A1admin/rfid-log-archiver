#ifndef ARCHIVEPROCESS_H_
#define ARCHIVEPROCESS_H_

#include <string>
#include <array>
#include <vector>
#include <utility>

#include "7zFile.h"
#include "7zVersion.h"
#include "Alloc.h"
#include "CpuArch.h"
#include "LzmaEnc.h"
#include "Precomp.h"

#include "LogArgumentDirectory.h"
#include "RFIDLog.h"

class ArchiveProcess {
public:
    ArchiveProcess();
    ArchiveProcess(const int);
    ArchiveProcess(const LogArgumentDirectory<std::string> &);
    ArchiveProcess(const LogArgumentDirectory<std::string> &, const int);

    std::vector<RFIDLog<std::string>> gatherLogs(const LogArgumentDirectory<std::string> &);

    constexpr static std::array<char [14], 6> allActions() {
        return std::array<char [14], 6> {"single", "singledel", "all", "singletest", 
            "singletestdel", "help"};
    }

    //enum class ACTIONS;
    enum class ACTIONS {
        SINGLE = 0,
        SINGLEDEL = 1,
        ALL = 2,
        SINGLETEST = 3,
        SINGLETESTDEL = 4,
        HELP = 5,
        NONE = 404
    };

    std::string LOG_EXT() noexcept;
    std::string LOG_ARCHIVE_EXT() noexcept;

    std::pair<bool, ACTIONS> isActionValid(const std::string &);
    bool isSourceDirectoryValid(LogArgumentDirectory<std::string> &);
    bool isTargetDirectoryValid(LogArgumentDirectory<std::string> &);

    void compressLogProcess(const LogArgumentDirectory<std::string> &, ACTIONS);
    void compressLogs(const std::vector<RFIDLog<std::string>> &, const LogArgumentDirectory<std::string> &);
    void compressSingleLog(const LogArgumentDirectory<std::string> &, const bool = false);
private:
    SRes encode(ISeqOutStream *, ISeqInStream *, UInt64, char *);

    std::string generateLogName();
    std::string monthStringValue(const int);
    std::string inputLogPath(const LogArgumentDirectory<std::string> &);
    // returns the directory where the log archive will be stored in.
    std::string outputLogArchiveDirectory(const LogArgumentDirectory<std::string> &);
    std::string outputLogArchiveDirectoryYear(const LogArgumentDirectory<std::string> &);
    std::string outputLogArchivePath(const LogArgumentDirectory<std::string> &, const RFIDLog<std::string> &);

    // Function retrieves the year, month, and day values;
    //
    // paramaeter is how many days you wish to add.
    // if a negative value was given it will subtract days.
    // default is 0 days
    std::tuple<int, int, int> dateValues(const int = 0);

    bool prepareArchive(CFileSeqInStream *, CFileOutStream *, const std::string &, 
        const std::string &);
    bool isTargetArchiveDirectoryValid(const LogArgumentDirectory<std::string> &);

    void closeFiles(CFileSeqInStream *, CFileOutStream *, bool = true);
    void deleteLogFile(const RFIDLog<std::string> &, const std::string&);
    void validateDirectories(LogArgumentDirectory<std::string> &);
    void createTargetDirectoryStructure(const LogArgumentDirectory<std::string> &);

    int m_day;
};

#endif