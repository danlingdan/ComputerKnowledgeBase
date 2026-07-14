#define UNICODE
#define _UNICODE
#include <stdio.h>
#include <windows.h>

int wmain(void)
{
    STARTUPINFOW startup_info;
    PROCESS_INFORMATION process_info;
    wchar_t command_line[] = L"C:\\Windows\\System32\\mspaint.exe";

    ZeroMemory(&startup_info, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    ZeroMemory(&process_info, sizeof(process_info));

    if (!CreateProcessW(NULL, command_line, NULL, NULL, FALSE, 0,
                        NULL, NULL, &startup_info, &process_info)) {
        fwprintf(stderr, L"CreateProcessW failed: %lu\n", GetLastError());
        return 1;
    }

    WaitForSingleObject(process_info.hProcess, INFINITE);
    wprintf(L"Child completed\n");

    CloseHandle(process_info.hThread);
    CloseHandle(process_info.hProcess);
    return 0;
}
