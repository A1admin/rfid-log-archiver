#ifndef LOGARGUMENTDIRECTORY_H_
#define LOGARGUMENTDIRECTORY_H_

#include <string>

class LogArgumentDirectory {
public:
    LogArgumentDirectory() :
        directoriesValidated(false) { }
    LogArgumentDirectory(const std::string &source, const std::string &target) :
        sourceLogDirectory(source), targetArchiveDirectory(target),
        directoriesValidated(false) { }
    LogArgumentDirectory(const char *source, const char *target) :
        sourceLogDirectory(source), targetArchiveDirectory(target),
        directoriesValidated(false) { }

    ~LogArgumentDirectory() = default;

    std::string sourceLogDirectory;
    bool sourceValid;
    std::string targetArchiveDirectory;
    bool targetValid;
    bool directoriesValidated;

};

#endif