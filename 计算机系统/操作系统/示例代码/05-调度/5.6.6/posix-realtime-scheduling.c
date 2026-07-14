#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { NUM_THREADS = 5 };

static void *worker(void *argument)
{
    long index = (long)argument;
    printf("real-time thread %ld is running\n", index);
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

    error = pthread_attr_setinheritsched(&attributes, PTHREAD_EXPLICIT_SCHED);
    if (error == 0) {
        error = pthread_attr_setschedpolicy(&attributes, SCHED_FIFO);
    }

    struct sched_param parameters = {0};
    parameters.sched_priority = sched_get_priority_min(SCHED_FIFO);
    if (error == 0 && parameters.sched_priority != -1) {
        error = pthread_attr_setschedparam(&attributes, &parameters);
    }
    if (error != 0 || parameters.sched_priority == -1) {
        fprintf(stderr, "Unable to configure SCHED_FIFO: %s\n",
                error == 0 ? "unsupported priority range" : strerror(error));
        pthread_attr_destroy(&attributes);
        return EXIT_FAILURE;
    }

    pthread_t threads[NUM_THREADS];
    int created = 0;
    for (long i = 0; i < NUM_THREADS; ++i) {
        error = pthread_create(&threads[i], &attributes, worker, (void *)i);
        if (error != 0) {
            fprintf(stderr,
                    "pthread_create: %s (real-time privilege may be required)\n",
                    strerror(error));
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
