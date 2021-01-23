#include <iostream>
// xor swap algorithm

// apparently the xor swap algorithm is extremely old, depricated, and useless
// still cool to know tho :/

int xorswap(int x, int y) {
    x=x^y;
    std::cout<<x<<std::endl;

    y=y^x;
    std::cout<<y<<std::endl;

    x=x^y;

    std::cout<<"x: "<<x<<"\ny: "<<y;
}

int main() {

    int input, input2;
    std::cout<<"[x]Enter a number: ";std::cin>>input;
    std::cout<<"[y]Enter another number: ";std::cin>>input2;
    xorswap(input, input2);
    return 0;
}
