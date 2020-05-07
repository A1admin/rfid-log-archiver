#ifndef RFIDLOG_H_
#define RFIDLOG_H_

#include <string>

template<typename Str>
class RFIDLog {
public:
    RFIDLog() = default;
    RFIDLog(const Str &filename, const Str &path) :
        filename(filename), path(path) { }
    RFIDLog(const Str &filename, const Str &path, const Str &stem) :
        filename(filename), path(path), stem(stem) { }

    ~RFIDLog() = default;

    Str filename;
    Str stem;
    Str path;
};

#endif