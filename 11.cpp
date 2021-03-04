#include <bits/stdc++.h>

// wrap inside namespace
namespace math_table {
// return nested vector of long longs, int n is number of iterations
    std::vector<std::vector<long long>> mul_table(int n) {
    // init result nested vector
        std::vector<std::vector<long long>> result(n, std::vector<long long>(n));
        for (int i = 0;i<n;i++) {
            for(int g = 0; g<n;g++) {
            // i will be our number of iterations, if n == 5, then result[i] would be 1-5
                result[i][g] = (i+1) * (g+1);
                // 1-5 * 1-5 is stored in g
            }
        }
        return result;
    }
    // print func in math_table namespace, put here to make main() not complicated
    void outputNested(std::vector<std::vector<long long>> outme, int n) {
        for (int i = 0;i<n;i++) {
            std::cout<<std::endl;
            for (int g = 0; g<n;g++) {
                std::cout<<outme[i][g]<<"\t";
            }
        }
    }
}

int main() {
    int iterations = 5;
    std::vector<std::vector<long long>> ret = math_table::mul_table(iterations);
    math_table::outputNested(ret, iterations);

    return 0;
}



