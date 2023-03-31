#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE file_handle;
    FILETIME creation_time, local_creation_time;
    SYSTEMTIME system_creation_time;
    char file_path[MAX_PATH];

    printf("Enter file path: ");
    scanf("%s", file_path);

    file_handle = CreateFile(file_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file_handle == INVALID_HANDLE_VALUE) {
        printf("Error opening file.\n");
        return 1;
    }

    if (!GetFileTime(file_handle, &creation_time, NULL, NULL)) {
        printf("Error getting file time.\n");
        CloseHandle(file_handle);
        return 1;
    }

    if (!FileTimeToLocalFileTime(&creation_time, &local_creation_time)) {
        printf("Error converting file time.\n");
        CloseHandle(file_handle);
        return 1;
    }

    if (!FileTimeToSystemTime(&local_creation_time, &system_creation_time)) {
        printf("Error converting file time.\n");
        CloseHandle(file_handle);
        return 1;
    }

    printf("Creation time: %d-%02d-%02d %02d:%02d:%02d\n",
           system_creation_time.wYear, system_creation_time.wMonth, system_creation_time.wDay,
           system_creation_time.wHour, system_creation_time.wMinute, system_creation_time.wSecond);

    CloseHandle(file_handle);

    return 0;
}
