## MBR Second Sector Reader/Writer

This project demonstrates how to read from and write data to the second sector of the Master Boot Record (MBR) on a physical disk using Windows API functions. The code accesses the first physical drive (PhysicalDrive0) and writes a string to the second sector (offset 512 bytes) while reading back the data to verify correctness.

⚠️ WARNING: Modifying the MBR can make your system unbootable or lead to data loss. Only run this code on non-essential or test systems, and ensure you have backups of any critical data.

Features
Write a string to the second sector of the MBR on the specified physical drive.
Read the data back from the second sector to verify the write operation.
Uses the Windows API for direct disk access.
Prerequisites
Administrator privileges are required to access and modify physical disk sectors.
Windows operating system (the code uses Windows-specific APIs like CreateFileA and DeviceIoControl).
A compatible C/C++ compiler (e.g., Visual Studio) to build the project.
Compilation
Compile the code with a C++ compiler on Windows. Here’s an example using the Visual Studio command line:

```
cl /EHsc /W4 main.cpp
```

Replace main.cpp with the name of your source file.

Usage
Run as Administrator: Open a terminal with Administrator privileges.

Execute the compiled program:

main.exe
The program will:

Write a sample string to the second sector of the MBR on PhysicalDrive0.
Read back the data from the second sector and display it to verify the write operation.
Sample Output
plaintext
Copy code
Data successfully written to the second sector.
Data read from the second sector: If the drive is formatted and configured to be booted from, then the sector 0 of the drive will contain the Master Boot Record (MBR)
Code Overview
Writing Data to the Second Sector
The write_to_second_sector function:

Opens PhysicalDrive0 with read and write permissions.
Sets the file pointer to the second sector (offset 512 bytes).
Writes a 512-byte buffer to the second sector, copying the provided data into this buffer.
Reading Data from the Second Sector
The read_from_second_sector function:

Opens PhysicalDrive0 with read permissions.
Sets the file pointer to the second sector.
Reads 512 bytes of data from the second sector into a buffer and prints it.
