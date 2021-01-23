#ifndef Challenge_H
#define Challenge_H
#include <iostream>
#include <vector>
#include <stack>         // handle multiple alphabets
#include <unordered_set> // hash set
#include <unordered_map> // hash map
#include <cmath>         // min(a, b)

using namespace std;

/* Builds an alphabet given a list of words */
class Alphabet {
private:
    
    /*
     * charVal:         a unique letter within the alphabet
     * 
     * prevLetterCount: a count of how many letters this char was directly compared to,
     *                  and were determined to come before this letter in the alphabet
     * 
     * nextNeighbors:   the set of letters this char was directly compared to,
     *                  and were determined to come after this letter in the alphabet */    
    struct Node {
        Node(char in_char);
        char                 charVal;
        int                  prevLetterCount = 0;
        unordered_set<Node*> nextNeighbors;
    };
    
    vector<string>             words;
    unordered_map<char, Node*> nodes;
    unordered_set<char>        lettersWithZeroPrevLetters;

public:
    Alphabet(vector<string> in_words);
    void                       addNewLetterNodeToGraph(char charVal);
    vector<char>               findAlphabet();
    unordered_map<char, Node*> createDirectedGraph();
    vector<char>               createAlphabet();
};

#endif