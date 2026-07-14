#define UNICODE
#define _UNICODE
#include <stdio.h>
#include <string.h>
#include <windows.h>

enum { MAPPING_SIZE = 4096 };
static const wchar_t *MAPPING_NAME = L"Local\\OSSharedObject";

int wmain(void)
{
    HANDLE mapping = CreateFileMappingW(
        INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MAPPING_SIZE,
        MAPPING_NAME);
    if (mapping == NULL) {
        fwprintf(stderr, L"CreateFileMappingW failed: %lu\n", GetLastError());
        return 1;
    }

    char *view = MapViewOfFile(mapping, FILE_MAP_WRITE, 0, 0, MAPPING_SIZE);
    if (view == NULL) {
        fwprintf(stderr, L"MapViewOfFile failed: %lu\n", GetLastError());
        CloseHandle(mapping);
        return 1;
    }

    const char message[] = "Shared memory message";
    memcpy(view, message, sizeof(message));
    printf("Produced: %s\n", view);
    printf("Run the consumer, then press Enter to release the mapping.\n");
    getchar();

    UnmapViewOfFile(view);
    CloseHandle(mapping);
    return 0;
}
