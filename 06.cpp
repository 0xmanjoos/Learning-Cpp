#include <iostream>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#define LEN 1000
#else
#include <unistd.h>
#define LEN 1
#endif

// this one will mainly be about recursion
// we should be nearing the end of plain vanilla c++

// returns a double, takes a double
// if in == 1, it will return a 1
// if in != 1, it will perform recurse(in - 1) * in, which will find the factorial
double factorial(double in) { return (in==1) ? 1 : factorial(in-1) * in; }

// this is to calculate the fibb sequence with recursion and returning with ternary op
int fibb(double in1){return (in1 <= 1) ? in1 : fibb(in1-1) + fibb(in1-2); }

// driver code
// remember not to make the input too large since the factorial function will cause a seg fault
int main(){
    double uwu;
    std::cout<<"Enter a number: "; std::cin>>uwu;
    std::cout<<"Factorial: "<<factorial(uwu)<<std::endl;
    sleep(LEN);
    std::cout<<"Fib up to n terms: "<<fibb(uwu);
    sleep(LEN);
    return 0;
}
