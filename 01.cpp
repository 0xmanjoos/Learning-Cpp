#include <iostream>
#include <cstring>

// encapsulation in c++

class clasS {
public:
    clasS(const char* s="", int i=0, double d=1) {
        strcpy(dataMember1, s);
        dataMember2 = i;
        dataMember3 = d;
    }
    void memberFunction(int i, const char* s = "unknown") {
        dataMember2 = i;
        std::cout<<dataMember1<<' '<<dataMember2<<' '<<dataMember3<<std::endl;
    }
protected:
    char dataMember1[20];
    int dataMember2;
    double dataMember3;
};




int main() {

    clasS object1("object1", 100, 2000), object2("object2"), object3();

    object1.memberFunction(21, "jotaro");
    return 0;
}
