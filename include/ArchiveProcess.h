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

    // gathers all logs from the source log directory
    std::vector<RFIDLog<std::string>> gatherLogs(const LogArgumentDirectory<std::string> &);

    // all actions that rla will run against
    constexpr static std::array<char [14], 6> allActions() {
        return std::array<char [14], 6> {"single", "singledel", "all", "singletest", 
            "singletestdel", "help"};
    }

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

    // checks to see if the action provided is empty
    std::pair<bool, ACTIONS> isActionValid(const std::string &);
    // checks to see if the source directory is valid
    bool isSourceDirectoryValid(LogArgumentDirectory<std::string> &);
    // checks to see if the target directory is valid
    bool isTargetDirectoryValid(LogArgumentDirectory<std::string> &);

    // entry point in which the process of compressing and archiving logs start
    void compressLogProcess(const LogArgumentDirectory<std::string> &, ACTIONS);
    // compress multiple logs and archives them
    void compressLogs(const std::vector<RFIDLog<std::string>> &, const LogArgumentDirectory<std::string> &);
    // compresses logs called with the single actions and archives them
    void compressSingleLog(const LogArgumentDirectory<std::string> &, const bool = false);
private:
    // encodes log file in lzma format
    SRes encode(ISeqOutStream *, ISeqInStream *, UInt64, char *);

    // generates the filename of the log
    std::string generateLogName();
    // returns the name of the month associated with the month parameter
    // if month value is outside of 1-12 then Janurary will be returned
    std::string monthStringValue(const int);
    // returns the full path of the log file
    std::string inputLogPath(const LogArgumentDirectory<std::string> &);
    // returns the directory where the log archive will be stored in.
    std::string outputLogArchiveDirectory(const LogArgumentDirectory<std::string> &);
    // returns the directory with only the year where the log archive will be stored in
    // The directory structure follows this rule:
    // Root_Directory/[year_value]/[month]
    // though the month value will be omitted
    std::string outputLogArchiveDirectoryYear(const LogArgumentDirectory<std::string> &);
    // returns the full path of the log archive
    std::string outputLogArchivePath(const LogArgumentDirectory<std::string> &, const RFIDLog<std::string> &);

    // function retrieves the year, month, and day values
    //
    // paramaeter is how many days you wish to add.
    // if a negative value was given it will subtract days.
    // default is 0 days
    std::tuple<int, int, int> dateValues(const int = 0);

    // prepares streams involved with the compression process
    bool prepareArchive(CFileSeqInStream *, CFileOutStream *, const std::string &, 
        const std::string &);
    bool isTargetArchiveDirectoryValid(const LogArgumentDirectory<std::string> &);

    // closes file streams related to compressing the log
    void closeFiles(CFileSeqInStream *, CFileOutStream *, bool = true);
    // deletes the log file
    void deleteLogFile(const RFIDLog<std::string> &, const std::string&);
    // marks the directories as being validated
    // not being used
    void validateDirectories(LogArgumentDirectory<std::string> &);
    // creates the directory structure of archived logs
    void createTargetDirectoryStructure(const LogArgumentDirectory<std::string> &);

    int m_day;
};

#endif