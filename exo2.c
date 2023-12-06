#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
//
// Created by franzozich on 06/12/23.
//
void exo2(){
    int fd=open("../myfile.txt",O_RDWR);
    struct stat st;
    fstat(fd,&st);
    uint8_t *byte_ptr = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    int fileSize=(int)st.st_size;
    uint8_t myByteArray[fileSize];
    for (int i = 0; i < fileSize; i++) {
        myByteArray[i]=*(byte_ptr+i);
        printf("%" PRId8 "\n", myByteArray[i]);
    }
    for (int i = 0; i <fileSize ; i++) {
        *(byte_ptr+i)=myByteArray[fileSize-1-i];
    }

    close(fd);
}