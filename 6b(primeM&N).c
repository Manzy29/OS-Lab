//parent.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(int argumentCount, char *argumentVector[]) {
    int i, j, sharedMemoryFileDescriptor;
    const int SIZE = 4096;
    pid_t processID;
    void *ptr;

    if (argumentCount > 2) {
        sscanf(argumentVector[1], "%d", &i);
        sscanf(argumentVector[2], "%d", &j);
        if (i < 2) {
            printf("Error input: %d\n", i);
            return 0;
        }
    } else {
        printf("Error: Minimum of two arguments must be passed as command line arguments!\n");
        exit(0);
    }

    processID = fork();

    if (processID == 0) {
        execl("./child", "prime", argumentVector[1], argumentVector[2], NULL);
    } else if (processID > 0) {
        wait(NULL);
        printf("\nParent: child completed!\n");

        sharedMemoryFileDescriptor = shm_open("VSS", O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, sharedMemoryFileDescriptor, 0);

        printf("%s", (char *)ptr);
        shm_unlink("VSS");
    }
    return 0;
}

//child.c
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <math.h>

int main(int argumentCount, char *argumentVector[]) {
    void *ptr;
    int sharedMemoryFileDescriptor = shm_open("VSS", O_CREAT | O_RDWR, 0666);
    ftruncate(sharedMemoryFileDescriptor, 4096);
    ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, sharedMemoryFileDescriptor, 0);

    printf("CHILD:\n");

    int i = atoi(argumentVector[1]);
    int j = atoi(argumentVector[2]);
    int flag = 0;

    printf("The prime numbers in the range %d and %d are:\n", i, j);
    for (int num = i; num < j; num++) {
        flag = 0;
        for (int k = 2; k <= num / 2; k++) {
            if (num % k == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            sprintf(ptr, "%d\t", num);
            ptr += strlen((char*)ptr); 
            printf("%d\t", num);
        }
    }
    printf("\n");
    shm_unlink("VSS");  
    return 0;
}
