# RFID-Log-Archiver (r-la)
r-la is a program that compresses log files created by the RFID-API web server. The initial reasoning for creating this program was to address the issue of log files reaching large sizes. A single log file for a day could get up to 1 GB. If nothing is done about this problem then storage space can quickly run out and cause issues.  

### That leaves three options  
1. Do nothing (Ostrich method)  
2. Manually compress/archive log files (Hopefully no one forgets before taking an extended vacation)  
3. Automatically compress the logs    


The third option is the most efficient and effective option. Hence, the creation of this program.


## Building
### Required for building:
* Windows OS - Used Windows 10
* C++ Compiler that supports C++ 17 standard - I used Visual Studio 2019
* CMake
* 7z Lzma SDK - Download the SDK library from the official site (Link provided below in the building section and included in the 3rdparty directory)


### Getting Started
You will need to be comfortable with the command line or terminal to compile and run this program

1. Clone the repository ``git clone https://github.com/A1admin/rfid-log-archiver``
2. Go to the [7zip](https://www.7-zip.org/sdk.html) website and download the latest version of the sdk or use the SDK from the 3rdparty directory
3. Extract the SDK and change directory to ``C/Util/Lzma`` (**Note**: Not the **Local C Drive** but the directory that was extracted from the archive)
4. Open Visual Studio and open the project file found within ``C/Util/Lzma``. There maybe a prompt to convert the project to a newer project file, accept, and make sure the target architecture matches what you're building for. Ex. x86 on x86 systems aND X64 for x64 systems. By default it's x86 and needs to be changed to x64
5. Change the build target from Debug to Release, build, and exit Visual Studio once complete
6. Change directory to the root directory for rfid-log-archiver from powershell
7. Run ```mkdir build; cd build```
8. Run cmake ```cmake .. -D7Z_ROOT_C=/path/to/library```
9. Run make ```msbuild /p:Configuration=Release /m:4 rla.vcxproj```
10. Run rla ```rla help```
