#include <iostream>
#include <vector>
#include "Challenge.h"

using namespace std;

int main(int argc, char **argv) {
    /* Add your own input words here: */
    vector<string> inputWords = {
        "bca",
        "aaa",
        "acb"
    };
    Alphabet test = Alphabet(inputWords);
    vector<char> letters = test.findAlphabet();
    cout << "Alphabet: ";
    for (int i = 0; i < letters.size(); i++) {
        cout << letters[i] << " ";
    }
    cout << "\n";
    return 0;
}