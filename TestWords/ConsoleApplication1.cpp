#include "pch.h"
using namespace std;

// abc  size = 3
// i = 1
void reverseWord(char* input, int size) {
    for (int i = 0; i < (size / 2); ++i) {
        char temp = input[i];
        input[i] = input[size - i - 1];
        input[size - i - 1] = temp;
    }
}

void reverseWords(char* input) {
    int len = strlen(input);

    int start = 0;
    bool inside = false;
    int counter = 0;
    for (int i = 0; i <= len; ++i) {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n' || input[i] == '\0') {
            inside = false;
            if (counter > 0) {
                reverseWord(&input[start], counter);
                counter = 0;
            }
        } else {
            if (!inside) {
                start = i;
                inside = true;
            }
            counter++;
        }
    }
}


int main(int argc, char* argv[]) {

    //char test[] = "abcd efg hi\t";
	char test[] = "Jorge";

    cout << "original string: " << test << endl;
    reverseWords(test);
    cout << "reverse words: " << test << endl;

    return EXIT_SUCCESS;
}
