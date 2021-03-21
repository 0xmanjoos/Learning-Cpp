#include <bits/stdc++.h>
#include <unistd.h>

// here i will attempt to learn basic bit manipulation and how these whole bitwise things work
/* NOTES

binary  hex      decimal

BASE:
2       16       10
VALUE:
0000    0        0
0001    1        1
0010    2        2
0011    3        3
0100    4        4
0101    5        5
0110    6        6
0111    7        7
1000    8        8
1001    9        9
1010    A        10
1011    B        11
1100    C        12
1101    D        13
1110    E        14
1111    F        15

the signed bit is the first bit
00010100 == 20 == 0x14
the as the first bit represents the fact that it is a positive value

00000101 == 5
this is due to each bit essentially representing a different value

128 64  32  16  8   4   2   1
0   0   0   0   0   1   0   1

nice we can read positive values, but what about negative ones?

for negative values, the signed bit(first bit) will be a 1, which tells us the value is negative
in this case, 128 will not become the value of 128, it will only server to tell us that this
value is negative
10000101 == -5

the same goes for bytes(4 bits)
0101    ==  5
1101    == -5

important to know how many bits you are working with!

DO THIS EXCERSIZE MANUALLY
TEST YOUR UNDERSTANDING

value:
    8421
    0000

test:
 7  0111
 6  0110
 5  0101
 4  0100
 3  0011
 2  0010
 1  0001
 0  0000
-0  1000
-1  1001
-2  1010
-3  1011
-4  1100
-5  1101
-6  1110
-7  1111

binary arithmetic:
this should basically be the same as normal decimal arithmetic
except we only have 1's and 0's, but each place will represent a value
it will be the same value, just the format will be different

0101    == 5
        +
0001    == 1
------------
0110    =  6

decimal values are represented by 4 bytes, which is 32 bits
if the maximum value of a signed int is 2,147,483,647, then 32 bits should be able to represent that
let me try.
signed two's compliment:
01111111111111111111111111111111

well it looks like i got it, sure took such a long time
now we can actually perform more complicated arithmetic since we can represent values larger than 7 now
lets try multiplication

0 0 0 0 0  0  0  0   0   0   0
1 2 4 8 16 32 64 128 256 512 1024

        32 + 16 + 8 + 4 + 1 = 61
00000000000000000000000000101101
                   128 + 8 = 136
00000000000000000000000010001000
                        61 * 136
--------------------------------
                          = 8296

now lets try to represent 8296 in binary
cant? takes too much time?
well good thing we have computers then!
these things are extremely tedious, so lets write a function that will do it for us

void base2(int in) {
    int out[12], i;
    for (i=0;in>0;i++) {
        out[i]=in % 2;
        in /= 2;
    }
    // we had declared i out of the for loop, so will not be deallocated on the stack
    for (int i-=1 ; i>=0; i--) {
        std::cout<<out[i];
    }
}

There we go!
now we understand two's compliment

*/

void base2(int in) {
    int out[12], i;
    for (i=0;in>0;i++) {
        out[i]=in % 2;
        in /= 2;
    }
    // we had declared i out of the for loop, so will not be deallocated on the stack
    for (i-=1 ; i>=0; i--) {
        std::cout<<out[i];
    }
}
int main(int argc, char**argv) {
    base2(8296);
    return 0;
}
