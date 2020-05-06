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
    ArchiveProcess(const LogArgumentDirectory &);
    ArchiveProcess(const LogArgumentDirectory &, const int);

    std::vector<RFIDLog> gatherLogs(const LogArgumentDirectory &dir);

    constexpr static std::array<char [11], 4> allActions() {
        return std::array<char [11], 4> {"single", "all", "singletest", "help"};
    }

    //enum class ACTIONS;
    enum class ACTIONS {
        SINGLE = 0,
        ALL = 1,
        SINGLETEST = 2,
        HELP = 3,
        NONE = 404
    };

    std::string LOG_EXT() noexcept;
    std::string LOG_ARCHIVE_EXT() noexcept;

    std::pair<bool, ACTIONS> isActionValid(const std::string &);
    bool isSourceDirectoryValid(LogArgumentDirectory &dir);
    bool isTargetDirectoryValid(LogArgumentDirectory &dir);

    void compressLogProcess(const LogArgumentDirectory &, ACTIONS);
    void compressLogs(const std::vector<RFIDLog> &logs, const LogArgumentDirectory &dir);
    void compressSingleLog(const LogArgumentDirectory &, const std::string &);
private:
    SRes encode(ISeqOutStream *out, ISeqInStream *in, UInt64 fileSize, char *rs);

    std::string generateLogName();
    std::string monthStringValue(const int);
    // returns the directory where the log archive will be stored in.
    std::string outputLogArchiveDirectory(const LogArgumentDirectory &);
    std::string outputLogArchiveDirectoryYear(const LogArgumentDirectory &);

    // Function retrieves the year, month, and day values;
    //
    // paramaeter is how many days you wish to add.
    // if a negative value was given it will subtract days.
    // default is 0 days
    std::tuple<int, int, int> dateValues(const int = 0);

    bool prepareArchive(CFileSeqInStream *inStream, CFileOutStream *outStream, const std::string &inputPath, 
        const std::string &outputPath);
    bool isTargetArchiveDirectoryValid(const LogArgumentDirectory &);

    void closeFiles(CFileSeqInStream *inStream, CFileOutStream *outStream, bool usingOutFile = true);
    void validateDirectories(LogArgumentDirectory &dir);
    void createTargetDirectoryStructure(const LogArgumentDirectory &);

    int m_day;
};

#endif