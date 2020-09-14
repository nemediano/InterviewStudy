#include "pch.h"
#include <cstdlib>

#include <iostream>

using namespace std;

int safe_index(const int& index);

int main(int argc, char* argv[]) {

    for (int i = -13; i <= 13; i++) {
        cout << i << ": " << safe_index(i) << endl;
    }

    return EXIT_SUCCESS;
}

int safe_index(const int& index) {
    constexpr int VECTOR_SIZE = 4;
    int safe = 0;
    safe += index;
    safe %= VECTOR_SIZE;
    if (safe < 0) {
        safe += VECTOR_SIZE;
    }
    return safe;
}