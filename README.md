# RFID-Log-Archiver (r-la)
r-la is a program that compresses logs created by the RFID-API web server. The initial reasoning for creating this program was to address the issue of log files reaching large sizes. A single log file for a day could get up to 1 GB. If nothing is done about this problem then storage space can quickly run out and cause issues.  

### That leaves three options  
1. Do nothing (Ostrich method)  
2. Manually compress/archive log files (Hopefully no one forgets before taking an extended vacation)  
3. Automatically compress the logs    


The third option is the most efficient and effect option. Hence, the creation of this program.
