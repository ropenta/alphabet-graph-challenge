#include <iostream>
#include <fstream>
#include <vector>
#include "Challenge.h"

using namespace std;

int main(int argc, char **argv) {
    /* Reads input words from provided inputText argument */
    vector<string> inputWords;
    
    if (argc < 2) {
        cout << "No test file entered. Program ending.\n";
        return -1;
    }
    
    string line;
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Can't open file\n";
    }
    string str;
    while (getline(inputFile, str)) {
        if (str.size() > 0) {
            inputWords.push_back(str);
        }
    }
    inputFile.close();

    for (int i = 0; i < inputWords.size(); i++) {
        cout << inputWords[i] << " ";
    }
    cout << "\n";
    Alphabet test = Alphabet(inputWords);
    vector<char> letters = test.findAlphabet();
    cout << "Alphabet: ";
    for (int i = 0; i < letters.size(); i++) {
        cout << letters[i] << " ";
    }
    cout << "\n";
    return 0;
}