#ifndef Challenge_H
#define Challenge_H
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>

using namespace std;


class Alphabet {
private:
    struct Node {
        char c;                                 // current char
        int inCount = 0;                        // # of incoming arrows
        unordered_set<Node*> nextNeighbors;     // neighbors after this char
        Node(char in_char);
    };
    
    vector<string> words;
    unordered_map<char, Node*> nodes;
    stack<Node*> nextLetters;
    unordered_set<char> zeroInCount;
    vector<char> alphabet;
public:
    Alphabet(vector<string> in_words);
    vector<char> createAlphabet();
    stack<Node*> addFirstLetter();
    unordered_map<char, Node*> createDirectedGraph();
    vector<char> findAlphabet();
};

#endif
