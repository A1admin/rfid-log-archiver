# This program compress logs created by the RFID-API Web API server
#
# Written by: Kun Deng

import sys

def main():
    if len(sys.argv) < 3:
        print("provide two arguments")
        print("arg1 arg2")
        print("arg1 - source directory where all logs are stored on the filesystem")
        print("arg2 - source directory where archived logs will be stored on the filesystem")
        sys.exit(-1)

    log_path_source = sys.argv[1]
    log_archive_destination = sys.argv[2]
    print("log source path is: %s" % log_path_source)
    print("archive log destination path: %s" % log_archive_destination)

if __name__ == "__main__":
    main()
