#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define STUB __attribute__((constructor))
#define MAX_TASKS 101
/*
    carriage return and no newline to make the loading output
    important function will use modulo and multiply by 10000 since that was the proper time for usleep
    populate function pointer array in program stub, as well as disable FILE buffering
    overall, pretty cool
*/
void(*ptrs[MAX_TASKS])();

void important_function() {
    usleep((unsigned int)(rand()%12)*10000);
}

int main(int argc,char**argv) {
    for(int i=0;ptrs[i]!=0;i++) {
        ptrs[i]();
        printf("\rloading: %d",i);
    }
}
void STUB s() {
    srand(time(0));
    setbuf(stdout,0);setbuf(stdin,0);setbuf(stderr,0);
    int n=sizeof(ptrs)/8;
    for (int i=0;i<n;i++) {
        ptrs[i]=important_function;
    }
}
