#include <iostream>
#include <vector>
#include "Challenge.h"

using namespace std;

int main(int argc, char **argv) {
    Alphabet twoWords = Alphabet({"bca", "aaa", "acb"});
    vector<char> letters = twoWords.findAlphabet();
    cout << "Alphabet: ";
    for (int i = 0; i < letters.size(); i++) {
        cout << letters[i] << " ";
    }
    cout << "\n";
    return 0;
}