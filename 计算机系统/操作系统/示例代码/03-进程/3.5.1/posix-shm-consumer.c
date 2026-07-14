#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

enum { SHM_SIZE = 4096 };
static const char *SHM_NAME = "/os_shm_example";

int main(void)
{
    int fd = shm_open(SHM_NAME, O_RDONLY, 0);
    if (fd == -1) {
        perror("shm_open (run the producer first)");
        return EXIT_FAILURE;
    }

    const char *mapping = mmap(NULL, SHM_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (mapping == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Consumed: %s\n", mapping);

    munmap((void *)mapping, SHM_SIZE);
    close(fd);
    if (shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
