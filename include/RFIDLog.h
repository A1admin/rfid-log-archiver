#ifndef RFIDLOG_H_
#define RFIDLOG_H_

#include <string>

class RFIDLog {
public:
    RFIDLog() = default;
    RFIDLog(const std::string &filename, const std::string &path) :
        filename(filename), path(path) { }
    RFIDLog(const std::string &filename, const std::string &path, const std::string &stem) :
        filename(filename), path(path), stem(stem) { }

    ~RFIDLog() = default;

    std::string filename;
    std::string stem;
    std::string path;
};

#endif