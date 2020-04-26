#ifndef RFIDLOG_H_
#define RFIDLOG_H_

#include <string>

class RFIDLog {
public:
    RFIDLog() = default;
    RFIDLog(const std::string &filename, const std::string &path) :
        filename(filename), path(path) { }

    ~RFIDLog() = default;

    std::string filename;
    std::string path;
};

#endif