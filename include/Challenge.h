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
    vector<char> createAlphabet();
    stack<Node*> addFirstLetter();
    unordered_map<char, Node*> createDirectedGraph();
    vector<char> findAlphabet();
};

#endif
