#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { NUM_THREADS = 5 };

static void *worker(void *argument)
{
    long index = (long)argument;
    printf("thread %ld is running\n", index);
    return NULL;
}

int main(void)
{
    pthread_attr_t attributes;
    int error = pthread_attr_init(&attributes);
    if (error != 0) {
        fprintf(stderr, "pthread_attr_init: %s\n", strerror(error));
        return EXIT_FAILURE;
    }

    int scope;
    error = pthread_attr_getscope(&attributes, &scope);
    if (error != 0) {
        fprintf(stderr, "pthread_attr_getscope: %s\n", strerror(error));
    } else {
        printf("default scope: %s\n",
               scope == PTHREAD_SCOPE_PROCESS
                   ? "PTHREAD_SCOPE_PROCESS"
                   : "PTHREAD_SCOPE_SYSTEM");
    }

    error = pthread_attr_setscope(&attributes, PTHREAD_SCOPE_SYSTEM);
    if (error != 0) {
        fprintf(stderr, "PTHREAD_SCOPE_SYSTEM not accepted: %s\n",
                strerror(error));
    }

    pthread_t threads[NUM_THREADS];
    int created = 0;
    for (long i = 0; i < NUM_THREADS; ++i) {
        error = pthread_create(&threads[i], &attributes, worker, (void *)i);
        if (error != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(error));
            break;
        }
        ++created;
    }
    for (int i = 0; i < created; ++i) {
        pthread_join(threads[i], NULL);
    }
    pthread_attr_destroy(&attributes);
    return created == NUM_THREADS ? EXIT_SUCCESS : EXIT_FAILURE;
}
