#include <stdio.h>
#include <string.h>
#include <unistd.h>
// gonna write this in x86 assembler :/
int main(int argc,char**argv) {
    if (argc!=2)goto die;
    // ---- \n < hello > \n ------ \n
    int len=strlen(argv[1]),border=0;
    write(1," ",1);
    do {
        write(1,"_",1);
        border++;
    } while (border<=len+1);
    border=0;
    printf("\n< %s >\n",argv[1]);
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
die: return 0;
}
