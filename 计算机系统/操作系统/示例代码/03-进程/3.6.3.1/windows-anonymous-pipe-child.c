#include <stdio.h>
#include <windows.h>

enum { BUFFER_SIZE = 64 };

int main(void)
{
    HANDLE read_handle = GetStdHandle(STD_INPUT_HANDLE);
    if (read_handle == INVALID_HANDLE_VALUE || read_handle == NULL) {
        fprintf(stderr, "GetStdHandle failed: %lu\n", GetLastError());
        return 1;
    }

    char buffer[BUFFER_SIZE];
    DWORD bytes_read = 0;
    if (!ReadFile(read_handle, buffer, BUFFER_SIZE - 1, &bytes_read, NULL)) {
        fprintf(stderr, "ReadFile failed: %lu\n", GetLastError());
        return 1;
    }

    buffer[bytes_read] = '\0';
    printf("Child read: %s\n", buffer);
    return 0;
}
