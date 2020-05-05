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
    ArchiveProcess() = default;
    ArchiveProcess(const LogArgumentDirectory &dir);

    std::vector<RFIDLog> gatherLogs(const LogArgumentDirectory &dir);

    //constexpr std::vector<char *> allActions() {
    //constexpr std::vector<char *> allActions() {
    //constexpr std::array<char *, 3> allActions() {
    constexpr static std::array<char [8], 2> allActions() {
    //constexpr std::array<std::string&&, 3> allActions() {
        //std::array<char *, 3> actions = {"sss", "sssss", "ere"};
        //std::array<char [8], 2> actions = {"single", "all", ""};
        std::array<char [8], 2> actions = {"single", "all"};
        //std::vector<char *> actions;
        //actions.push_back("all");

        return actions;
    }

    //enum class ACTIONS;
    enum class ACTIONS {
        SINGLE = 0,
        ALL = 1,
        NONE = 404
    };

    std::string LOG_EXT() noexcept;

    std::pair<bool, ACTIONS> isActionValid(const std::string &);
    bool isSourceDirectoryValid(LogArgumentDirectory &dir);
    bool isTargetDirectoryValid(LogArgumentDirectory &dir);

    void compressLogs(const std::vector<RFIDLog> &logs, const LogArgumentDirectory &dir);
private:
    SRes encode(ISeqOutStream *out, ISeqInStream *in, UInt64 fileSize, char *rs);

    bool prepareArchive(CFileSeqInStream *inStream, CFileOutStream *outStream, const std::string &inputPath, 
        const std::string &outputPath);

    void closeFiles(CFileSeqInStream *inStream, CFileOutStream *outStream, bool usingOutFile = true);
    void validateDirectories(LogArgumentDirectory &dir);
};

#endif