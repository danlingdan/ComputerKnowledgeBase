#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

static unsigned long long sum;

static DWORD WINAPI summation(LPVOID argument)
{
    DWORD upper = *(const DWORD *)argument;
    unsigned long long total = 0;
    for (DWORD i = 1; i <= upper; ++i) {
        total += i;
    }
    sum = total;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return 1;
    }

    char *end = NULL;
    unsigned long value = strtoul(argv[1], &end, 10);
    if (*argv[1] == '\0' || argv[1][0] == '-' || *end != '\0') {
        fprintf(stderr, "Argument must be a non-negative integer.\n");
        return 1;
    }
    DWORD upper = (DWORD)value;

    DWORD thread_id;
    HANDLE thread = CreateThread(NULL, 0, summation, &upper, 0, &thread_id);
    if (thread == NULL) {
        fprintf(stderr, "CreateThread failed: %lu\n", GetLastError());
        return 1;
    }

    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    printf("sum = %llu\n", sum);
    return 0;
}
