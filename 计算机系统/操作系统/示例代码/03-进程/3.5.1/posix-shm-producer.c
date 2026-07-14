#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

enum { SHM_SIZE = 4096 };
static const char *SHM_NAME = "/os_shm_example";

int main(void)
{
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0600);
    if (fd == -1) {
        perror("shm_open");
        return EXIT_FAILURE;
    }
    if (ftruncate(fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        close(fd);
        shm_unlink(SHM_NAME);
        return EXIT_FAILURE;
    }

    char *mapping = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE,
                         MAP_SHARED, fd, 0);
    if (mapping == MAP_FAILED) {
        perror("mmap");
        close(fd);
        shm_unlink(SHM_NAME);
        return EXIT_FAILURE;
    }

    const char *message = "Hello World";
    snprintf(mapping, SHM_SIZE, "%s", message);
    printf("Produced: %s\n", mapping);

    munmap(mapping, SHM_SIZE);
    close(fd);
    return EXIT_SUCCESS;
}
