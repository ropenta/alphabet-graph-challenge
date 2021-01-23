#ifndef Challenge_H
#define Challenge_H

/* 
    Goal:
    - We want to represent the alphabet as a directed graph (connections between letters are directional).
    - Each letter in the alphabet has a set of letters that come before, and set of letters that come later.
    - We don't need to store the whole set of letters that come before and after the letter, since it would take up more memory than is needed.
    - Instead, we can store the set of letters that are confirmed to come after, and a count of letters that come before.
    - We'd like to associate each letter with information that will help determine the order relative to other letters.
    
    Implementation:
    - We can store each unique letter inside a Node class that contains extra information.
    - Anytime we encounter a new ordering between two letters (e.g. 'b' comes before 'a'), we will store two values:
        1) b's set of adjacent letters that come after it in the alphabet includes 'a'
            bNode.nextNeighbors.add(aNode);
        2) 'a' is pointed at by 'b', which we can represent with 'prevLetterCount'.
            a.prevLetterCount++
    - To determine the first letter to choose, we choose the Node with a 'prevLetterCount' of 0.
    - This indicating that no letters come before in the alphabet.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set> // hash set
#include <unordered_map> // hash map
#include <cmath>

using namespace std;

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
        // using SetOfLetterNodes_map_t = unordered_set<Node*>;
        unordered_set<Node*> nextNeighbors;
        Node(char in_char);
    };

    // using GraphOfLetterNodes_map_t = unordered_map<char, Node*>;
    // using SetOfLetters_char_t = unordered_set<char>;
    // using StackOfLetterNodes_set_t = stack<Node*>;

    vector<string> words;
    unordered_map<char, Node*> nodes;
    stack<Node*> nextLetters;
    unordered_set<char> lettersWithZeroPrevLetters;
    vector<char> alphabet;

public:
    Alphabet(vector<string> in_words);
    vector<char> findAlphabet();                        // Step 0: calls all the following functions
    unordered_map<char, Node*> createDirectedGraph();   // Step 1: creates graph connecting chars by their ordering
    stack<Node*> addFirstLetter();                      // Step 2: adds the first letter of the alphabet (if it exists)
    vector<char> createAlphabet();                      // Step 3: adds the rest of the alphabet
};

#endif