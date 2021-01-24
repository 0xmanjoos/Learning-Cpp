#include <iostream>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#define LEN 1000
#else
#include <unistd.h>
#define LEN 1
#endif

// multi dimensional arrays -- matrices -- and other things

void explanation(){
    // so basically its a nested array
    // here, "x" is a two dimensional array, it can hold 12 elements
    // 3 rows || 4 columns
    // 4 columns for each row
    int x[3][4];

    // big boy leagues here now
    // there are 3 columns for each of the 4 columns
    // so thats 12 columns so far
    // then we have 12 * 2, since we have another row
    // so 24 total elements can be held within this nested/multi dimensional array
    float y[2][4][3];

    // this init's 3 elements within 2 total arrays
    // this has 2 rows and 3 columns, which gives us 6 elements in total
    int two[2][3] = { {2, 4, 5}, {9, 0, 19}};

    // the fuck is this
    // there are 4 elements within each column
    // there are 3 columns within 2 arrays
    // so in total it will be 24 elements
    int three[2][3][4] = {
                    { {3, 4, 2, 3}, {0, -3, 9, 11}, {23, 12, 23, 2} },
                    { {13, 4, 56, 3}, {5, 9, 3, 5}, {5, 1, 4, 9} } };
    return;
}
int main(){
    // three elements in 2 columns
    int two[2][3] = { {1, 3, 5}, {21, 23, 1} };
    // nested for loop
    for (int i=0; i < 2 ; i++) {
        for (int k; k<3; k++) {
            // it will iterate through each changing var
            // for i in range(2):
            //      for k in range(3):
            //          print(two[i][k])

            std::cout << "test[" << i << "][" << k << "] = " << two[i][k]<<std::endl;
        }
    }




    return 0;
}
