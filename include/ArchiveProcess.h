#ifndef ARCHIVEPROCESS_H_
#define ARCHIVEPROCESS_H_

#include <string>
#include <vector>

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

    std::string LOG_EXT() noexcept;

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