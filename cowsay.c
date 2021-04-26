#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 50
// gonna write this in x86 assembler :/
int main(int argc,char**argv) {
    char buffer[MAX];
    if (argc<2)goto die;
    // ---- \n < hello > \n ------ \n
    for (int i=1;i<argc;i++) {
        size_t d_len = strlen(buffer), z;//dest
        for (z=0;argv[i][z]!='\0';z++) {
            buffer[d_len+z]=argv[i][z];
        }
        if(i!=argc-1)buffer[d_len+z]=' ';
        buffer[d_len+z+1]='\0';
    }
    int len=strlen(buffer),border=0;
    write(1," ",1);
    do {
        write(1,"_",1);
        border++;
    } while (border<=len+1);
    border=0;
    printf("\n< %s >\n",buffer);
    write(1," ",1);
    do {
        write(1,"-",1);
        border++;
    } while (border<=len+1);
    puts(
    "\n        \\   ^__^ \n"
    "         \\  (oo)\\_______ \n"
    "            (__)\\       )\\/\\ \n"
    "                ||----w | \n"
    "                ||     || ");
    exit(0);
die: puts("Error!"); return 0;
}
