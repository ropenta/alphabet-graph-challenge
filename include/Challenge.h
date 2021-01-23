#ifndef Challenge_H
#define Challenge_H
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set> // hash set
#include <unordered_map> // hash map
#include <cmath>         // so we can use min(a, b)

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
     *                  and were determined to come after this letter in the alphabet
     */    
    struct Node {
        char charVal;
        int prevLetterCount = 0;
        unordered_set<Node*> nextNeighbors;
        Node(char in_char);
    };
    
    /* Member variables */
    vector<string> words;
    unordered_map<char, Node*> nodes;
    stack<Node*> nextLetters;
    unordered_set<char> zeroInCount;
    vector<char> alphabet;
public:
    /* Constructor */
    Alphabet(vector<string> in_words);

    /* Member functions */
    vector<char> findAlphabet();                        // Step 0: calls all the following functions
    unordered_map<char, Node*> createDirectedGraph();   // Step 1: creates graph connecting chars by their ordering
    stack<Node*> addFirstLetter();                      // Step 2: adds the first letter of the alphabet (if it exists)
    vector<char> createAlphabet();                      // Step 3: adds the rest of the alphabet
};

#endif