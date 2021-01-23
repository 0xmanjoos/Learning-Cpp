#include <iostream>

#include <time.h>
#ifdef _WIN32
#include <windows.h>
#define LEN 1000
#else
#include <unistd.h>
#define LEN 1
#endif

using namespace std;

// playing with operator overloading, constructors destructors heap object
// allocation everything of the sort

class value{
public:
    value(int x) {
        cout<<"[ Integer ]: "<<x<<endl;
        sleep(LEN);
    }
    value(const char* x) {
        cout<<"[ String ]: "<<x<<endl;
        sleep(LEN);
    }
    value(double x) {
        cout<<"[ Double/Float ]: "<<x<<endl;
        sleep(LEN);
    }
};

int main(){
    // allocating new dynamic objects on the heap
    value* ob1 = new value(3.1415);

    // same as previous example just longer
    value* ob2;
    ob2 = new value("Jerry");

    // this object will be init'd and stored on the stack
    value ob3(12);

    return 0;
}
