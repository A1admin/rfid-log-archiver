# RFID-Log-Archiver (r-la)
r-la is a program that compresses log files created by the RFID-API web server. The initial reasoning for creating this program was to address the issue of log files reaching large sizes. A single log file for a day could get up to 1 GB. If nothing is done about this problem then storage space can quickly run out and cause issues.  

### That leaves three options  
1. Do nothing (Ostrich method)  
2. Manually compress/archive log files (Hopefully no one forgets before taking an extended vacation)  
3. Automatically compress the logs    


The third option is the most efficient and effective option. Hence, the creation of this program.


# Note
Change the target C++ standard from 17 to 11. Will have to add more depdencies like Boost (for filesystem usage). Won't have to change the compiler version. When this was created I was using GCC version 8 which has C++ 11 support. Instead what will have to be done is change the compiler CXX standard flag.



## Building
### Required for building:
* Linux OS
* C++ compiler with C++17 support (filesystem library)
* CMake
* 7z Lzma SDK - Download the SDK library from the official site (Link provided below in the building section and included in the 3rdparty directory)


### Getting Started
You will need to be comfortable with the command line or terminal to compile and run this program

1. Clone the repository ``git clone https://github.com/A1admin/rfid-log-archiver``
2. Go to the [7zip](https://www.7-zip.org/sdk.html) website and download the latest version of the sdk or use the SDK from the 3rdparty directory
3. Extract the SDK and change directory to ``[ExtractedRootFolder]/C/Util/Lzma``
4. Build the 7zip library 
```Bash
make -f makefile.gcc
```
5. Copy the ``[ExtractedRootFolder]/C/Util/Lzma`` directory somewhere where it is easily referenceable. Ex. /home/[your_username]
6. Change directory to the root directory of rfid-log-archiver. This is the repository that was cloned
7. Create build directory and change directories
```Bash
mkdir build; cd build
```
8. Build the project 
```Bash
cmake .. -D7Z_ROOT_C=/path/to/library -DCMAKE_BUILD_TYPE=RELEASE
```
Where -D7Z_ROOT_C would be the copied lzma directory /home/[your_username]/[ExtractedRootFolder]/C  
9. Build the executable 
```Bash
make
```
10. Run rla 
```Bash
rla help
```
