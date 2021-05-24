/*
  interesting little test with non printable characters
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#define SECRET " Everything is so tiring and I dont want to continue with life "
#define MASK   "I love everything about my life"

int main(int argc,char**argv) {
    if(argc<=1){
        printf("Usage: %s [filename]\n",argv[0]);
    }
    int fd =open(argv[1],O_RDWR|O_CREAT,0777);
    uint8_t non_print=0xd;
    write(fd,SECRET,sizeof(SECRET));
    write(fd,&non_print,sizeof(char));
    write(fd,MASK,sizeof(MASK));
    close(fd);    
}
