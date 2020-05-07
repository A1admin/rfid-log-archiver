#ifndef LOGARGUMENTDIRECTORY_H_
#define LOGARGUMENTDIRECTORY_H_

#include <string>

template<typename Str>
class LogArgumentDirectory {
public:
    LogArgumentDirectory() :
        directoriesValidated(false) { }
    LogArgumentDirectory(const Str &source, const Str &target) :
        sourceLogDirectory(source), targetArchiveDirectory(target),
        directoriesValidated(false) { }
    LogArgumentDirectory(const char *source, const char *target) :
        sourceLogDirectory(source), targetArchiveDirectory(target),
        directoriesValidated(false) { }

    ~LogArgumentDirectory() = default;

    Str sourceLogDirectory;
    bool sourceValid;
    Str targetArchiveDirectory;
    bool targetValid;
    bool directoriesValidated;

};

#endif