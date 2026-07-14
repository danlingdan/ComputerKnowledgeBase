#define UNICODE
#define _UNICODE
#include <stdio.h>
#include <string.h>
#include <windows.h>

int wmain(void)
{
    HANDLE read_handle = NULL;
    HANDLE write_handle = NULL;
    SECURITY_ATTRIBUTES security = {
        sizeof(SECURITY_ATTRIBUTES), NULL, TRUE
    };

    if (!CreatePipe(&read_handle, &write_handle, &security, 0)) {
        fwprintf(stderr, L"CreatePipe failed: %lu\n", GetLastError());
        return 1;
    }
    if (!SetHandleInformation(write_handle, HANDLE_FLAG_INHERIT, 0)) {
        fwprintf(stderr, L"SetHandleInformation failed: %lu\n", GetLastError());
        CloseHandle(read_handle);
        CloseHandle(write_handle);
        return 1;
    }

    STARTUPINFOW startup_info;
    PROCESS_INFORMATION process_info;
    ZeroMemory(&startup_info, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    startup_info.hStdInput = read_handle;
    startup_info.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    startup_info.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    startup_info.dwFlags = STARTF_USESTDHANDLES;
    ZeroMemory(&process_info, sizeof(process_info));

    wchar_t command_line[] = L"windows-anonymous-pipe-child.exe";
    if (!CreateProcessW(NULL, command_line, NULL, NULL, TRUE, 0, NULL, NULL,
                        &startup_info, &process_info)) {
        fwprintf(stderr, L"CreateProcessW failed: %lu\n", GetLastError());
        CloseHandle(read_handle);
        CloseHandle(write_handle);
        return 1;
    }

    CloseHandle(read_handle);
    const char message[] = "Greetings from the parent";
    DWORD bytes_written = 0;
    if (!WriteFile(write_handle, message, (DWORD)sizeof(message),
                   &bytes_written, NULL)) {
        fwprintf(stderr, L"WriteFile failed: %lu\n", GetLastError());
    }
    CloseHandle(write_handle);

    WaitForSingleObject(process_info.hProcess, INFINITE);
    CloseHandle(process_info.hThread);
    CloseHandle(process_info.hProcess);
    return 0;
}
