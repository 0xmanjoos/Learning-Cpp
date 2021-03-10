#include <iostream>
/*
reference and dereference operators basically
referencing a value is getting the real address(location) in memory where it resides
dereferencing it is getting the value at the provided memory address
in assembly, this would be []
an example of a dereference in asm is getting the length of a string

strlen:
    push ebp
    mov ebp, esp
    xor ecx, ecx
strloop:
    cmp byte [eax+ecx], 0
    je strhalt
    inc ecx
    jmp strloop
strhalt:
    pop ebp
    ret

the important part is in strloop and on "cmp byte [eax+ecx], 0"
before we call this subroutine, we will move the address of a string into eax
the deference operator is [eax+ecx], remember that addresses are in hexadecimal, but can also
be interpreted as decimal, octal, binary, and probably more.
if we were to have the memory address of eax + counter of ecx, this would store the length of string
in ecx as well as increment the values of eax, trying to find the null terminator
*/
// hehe, one time function overloading came in handy, this was very useful

void print(int* intpointer, int n) {
    std::cout<<"\ninteger array\naddress\t\t\tvalue\n"<<std::endl;
    for (int i = 0; i<n;i++) {
        std::cout<< intpointer+i << "\t=\t"<< *(intpointer+i) <<"\n";
    }
}
void print(const char* *strpointer, int n) {
    std::cout<<"\nstring array\naddress\t\t\tvalue\n"<<std::endl;
    for (int i = 0; i<n;i++) {
        std::cout<< strpointer+i << "\t=\t"<< *(strpointer+i) <<"\n";
    }
}

int main() {
    // initialize pointer to array of chars
    const char* strarray[] = {"jotaro", "james", "jackie", "hehe"};
    // initialize pointer to pointer to array of chars
    const char* *strpointer = &strarray[0];

    // init array of integers, probably stored on stack, mov [ebp-*], 1-5;
    int intarray[] = {1, 2, 3, 4, 5};
    // init pointer to array
    int *intpointer = &intarray[0];
  
    // get size of both arrays
    int strsize = sizeof(strarray) / sizeof(strarray[0]);
    int intsize = sizeof(intarray) / sizeof(intarray[0]);
    // goto print function, iterates through array without indexing and outputs
    print(intpointer, intsize);
    print(strpointer, strsize);



    return 0;
}
