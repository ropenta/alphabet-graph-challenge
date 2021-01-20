#ifndef Challenge_H
#define Challenge_H
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set> // hash set
#include <unordered_map> // hash map

using namespace std;

/* Builds an alphabet given a list of words */
class Alphabet {
private:
    /* Each unique char belongs to a Node */
    struct Node {
        char c;                                 // current char
        int inCount = 0;                        // # of incoming arrows
        unordered_set<Node*> nextNeighbors;     // neighbors after this char
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