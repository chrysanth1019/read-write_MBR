#include <windows.h>
#include <stdio.h>
#include <string.h>

#define SECTOR_SIZE 512

// Function to write data to the second sector of the MBR
int write_to_second_sector(const char* data, size_t data_size) {
    if (data_size > SECTOR_SIZE) {
        printf("Data is too large to fit in one sector.\n");
        return -1;
    }

    HANDLE hDisk = CreateFileA(
        "\\\\.\\PhysicalDrive0", // Target the first physical drive; adjust if needed
        GENERIC_WRITE | GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hDisk == INVALID_HANDLE_VALUE) {
        printf("Error opening disk: %lu\n", GetLastError());
        return -1;
    }

    // Set the file pointer to the second sector (offset 512 bytes)
    LARGE_INTEGER sector_offset;
    sector_offset.QuadPart = SECTOR_SIZE; // Skip the first 512 bytes (first sector)

    if (!SetFilePointerEx(hDisk, sector_offset, NULL, FILE_BEGIN)) {
        printf("Error setting file pointer: %lu\n", GetLastError());
        CloseHandle(hDisk);
        return -1;
    }

    // Prepare buffer and write data to the second sector
    DWORD bytesWritten;
    char buffer[SECTOR_SIZE] = { 0 }; // Initialize buffer with zeros
    memcpy(buffer, data, data_size); // Copy data to the buffer

    if (!WriteFile(hDisk, buffer, SECTOR_SIZE, &bytesWritten, NULL)) {
        printf("Error writing to disk: %lu\n", GetLastError());
        CloseHandle(hDisk);
        return -1;
    }

    if (bytesWritten != SECTOR_SIZE) {
        printf("Error: Not all bytes were written to the sector.\n");
        CloseHandle(hDisk);
        return -1;
    }

    printf("Data successfully written to the second sector.\n");

    CloseHandle(hDisk);
    return 0;
}

// Function to read data from the second sector of the MBR
int read_from_second_sector(char* buffer, size_t buffer_size) {
    if (buffer_size < SECTOR_SIZE) {
        printf("Buffer size is too small to read a full sector.\n");
        return -1;
    }

    HANDLE hDisk = CreateFileA(
        "\\\\.\\PhysicalDrive0", // Target the first physical drive; adjust if needed
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hDisk == INVALID_HANDLE_VALUE) {
        printf("Error opening disk: %lu\n", GetLastError());
        return -1;
    }

    // Set the file pointer to the second sector (offset 512 bytes)
    LARGE_INTEGER sector_offset;
    sector_offset.QuadPart = SECTOR_SIZE; // Skip the first 512 bytes (first sector)

    if (!SetFilePointerEx(hDisk, sector_offset, NULL, FILE_BEGIN)) {
        printf("Error setting file pointer: %lu\n", GetLastError());
        CloseHandle(hDisk);
        return -1;
    }

    // Read data from the second sector
    DWORD bytesRead;
    if (!ReadFile(hDisk, buffer, SECTOR_SIZE, &bytesRead, NULL)) {
        printf("Error reading from disk: %lu\n", GetLastError());
        CloseHandle(hDisk);
        return -1;
    }

    if (bytesRead != SECTOR_SIZE) {
        printf("Error: Not all bytes were read from the sector.\n");
        CloseHandle(hDisk);
        return -1;
    }

    printf("Data successfully read from the second sector.\n");

    CloseHandle(hDisk);
    return 0;
}

int main() {
    const char* data = "If the drive is formatted and configured to be booted from, then the sector 0 of the drive will contain the Master Boot Record (MBR)";

    // Write to the second sector
    if (write_to_second_sector(data, strlen(data)) == 0) {
        printf("Data written successfully.\n");
    }
    else {
        printf("Failed to write data.\n");
    }

    // Read from the second sector
    char buffer[SECTOR_SIZE] = { 0 }; // Buffer to hold the data read from the sector
    if (read_from_second_sector(buffer, sizeof(buffer)) == 0) {
        printf("Data read from the second sector: %s\n", buffer);
    }
    else {
        printf("Failed to read data.\n");
    }

    return 0;
}
