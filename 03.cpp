// include essential headers
#include <iostream>
#include <time.h>
// if win32, include windowz stufzz
#ifdef _WIN32
#include <Windows.h>
// windows Sleep() function takes milliseconds so i define it here
#define LEN 1000
// else include linux headers
#else
#include <unistd.h>
#define LEN 1
#endif

// dynamic memory allocation in c++
class Box {
   public:
      Box() { // constructor
         std::cout << "Constructor called!\n";
      }
      ~Box() { // destructor
         std::cout << "Destructor called!\n";
      }
};
void dynamic(){
    double* value = NULL; // initialize pointer with value of null
    value = new double; // allocate memory for this variable with c++ 'new' function
    *value = 2919.122; // store value at allocated address
    std::cout<<"Value of value: "<< *value<<std::endl; // output
    delete value; // 'free' this heap segment, or in c++ 'delete'
}
int main(){
    dynamic();
    sleep(LENGTH);
    Box* myBoxArray = new Box[1];
    delete [] myBoxArray; // Delete array
    return 0;
}
