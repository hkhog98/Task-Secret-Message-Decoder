#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 1

void decoder(int fd_src, int fd_dst) {
    char buffer;
    int offset = 0;
    while((pread(fd_src, &buffer, SIZE, offset)) > 0) {
        if(((buffer >= 'D') && (buffer <= 'Z')) || ((buffer >= 'd') && (buffer <= 'z'))) {
            buffer = buffer - 3;
            //printf(" %c", buffer);
            pwrite(fd_dst, &buffer, SIZE, offset);
        }
        else if(((buffer <= 'C') && (buffer >= 'A')) || ((buffer <= 'c') && (buffer >= 'a'))) {
            buffer = buffer + 23;
            //printf(" %c", buffer);
            pwrite(fd_dst, &buffer, SIZE, offset);
        }
        else {
            //printf(" %c", buffer);
            pwrite(fd_dst, &buffer, SIZE, offset);
        }
        offset++;
    }
}

int main() {
    int fd_src = open("encoded_text.txt", O_RDONLY);
    int fd_dst = open("decoded_text.txt", O_CREAT | O_RDWR, 0644);
    if((fd_src == -1) || (fd_dst == -1)) {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    decoder(fd_src, fd_dst);
    return 0;
}