# RFID-Log-Archiver (r-la)
r-la is a program that compresses logs created by the RFID-API web server. The initial reasoning for creating this program was to address the issue of log files reaching large sizes. A single log file for a day could get up to 1 GB. If nothing is done about this problem then storage space can quickly run out and cause issues.  

### That leaves three options  
1. Do nothing (Ostrich method)  
2. Manually compress/archive log files (Hopefully no one forgets before taking an extended vacation)  
3. Automatically compress the logs    


The third option is the most efficient and effect option. Hence, the creation of this program.


## Building
### Required for building:
* Linux OS
* Linux compiler that has c++17 support
* CMake
* Make
* 7z Lzma SDK


### Building
1. Clone the repository ``git clone https://github.com/A1admin/rfid-log-archiver``
2. Go to the [7zip](https://www.7-zip.org/sdk.html) website and download the latest version of the sdk
3. Extract the SDK and change directory to ``C/Util/Lzma``
4. Run ```make -f makefile.gcc``` to build the object files (``filename.o``)
5. Copy the ``C/`` directory from the compressed file in a location where you can reference it later taking note of the full path
6. Change directory to rfid-log-archiver
7. Run ```mkdir build; cd build```
8. Run cmake ```cmake .. -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_C_COMPILER=/usr/bin/gcc-8 -DCMAKE_CXX_COMPILER=/usr/bin/g++-8 -D7Z_ROOT_C=/path/to/library```
9. Run make ```make```
10. Run rla ```rla help```
