#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long long sum;

static void *summation(void *argument)
{
    int upper = *(const int *)argument;
    long long total = 0;
    for (int i = 1; i <= upper; ++i) {
        total += i;
    }
    sum = total;
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *end = NULL;
    long value = strtol(argv[1], &end, 10);
    if (*argv[1] == '\0' || *end != '\0' || value < 0 || value > INT_MAX) {
        fprintf(stderr, "Argument must be an integer in [0, %d].\n", INT_MAX);
        return EXIT_FAILURE;
    }
    int upper = (int)value;

    pthread_t thread;
    int error = pthread_create(&thread, NULL, summation, &upper);
    if (error != 0) {
        fprintf(stderr, "pthread_create: %s\n", strerror(error));
        return EXIT_FAILURE;
    }
    error = pthread_join(thread, NULL);
    if (error != 0) {
        fprintf(stderr, "pthread_join: %s\n", strerror(error));
        return EXIT_FAILURE;
    }

    printf("sum = %lld\n", sum);
    return EXIT_SUCCESS;
}
