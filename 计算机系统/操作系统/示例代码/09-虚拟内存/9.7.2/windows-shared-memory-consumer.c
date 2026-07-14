#define UNICODE
#define _UNICODE
#include <stdio.h>
#include <windows.h>

static const wchar_t *MAPPING_NAME = L"Local\\OSSharedObject";

int wmain(void)
{
    HANDLE mapping =
        OpenFileMappingW(FILE_MAP_READ, FALSE, MAPPING_NAME);
    if (mapping == NULL) {
        fwprintf(stderr,
                 L"OpenFileMappingW failed: %lu (run the producer first)\n",
                 GetLastError());
        return 1;
    }

    const char *view = MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0);
    if (view == NULL) {
        fwprintf(stderr, L"MapViewOfFile failed: %lu\n", GetLastError());
        CloseHandle(mapping);
        return 1;
    }

    printf("Consumed: %s\n", view);
    UnmapViewOfFile(view);
    CloseHandle(mapping);
    return 0;
}
