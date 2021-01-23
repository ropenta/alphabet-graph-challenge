#include "Challenge.h"

using namespace std;

/* Constructor */
Alphabet::Alphabet(vector<string> in_words) {
    words = in_words;
    nodes = {};
    nextLetters = {};
    lettersWithZeroPrevLetters = {};
    alphabet = {};
}
/* Node constructor */
Alphabet::Node::Node(char in_char) {
    charVal = in_char;
}


/* Input: list of words */
/* Output: alphabet     */
vector<char> Alphabet::findAlphabet() {
    // 0. check cases with 1 or fewer words
    if (words.size() < 1) {
        return {};
    } else if (words.size() == 1) {
        // edge case: 1 word
        char c = words[0][0];
        for (int i = 1; i < words[0].size(); i++) {
            // only valid if all chars are the same
            if (words[0][i] != c) {
                return vector<char>{};
            }
        }
        return vector<char>{c};
    }

    // 1. compare adjacent words, find first difference if it exists
    nodes = createDirectedGraph();

    // 2. add first letter to alphabet, get neighbors, decrease prevLetterCount, add zero in count nodes to stack, repeat
    return createAlphabet();
}

/*
 *  Modifies: inserts new node into graph of letter nodes 
 */
void Alphabet::addNewLetterNodeToGraph(char charVal) {
    Node *n = new Node(charVal);
    nodes[charVal] = n;
    lettersWithZeroPrevLetters.insert(charVal);
}


/* Modifies: empty graph, set of letters with no inbound nodes pointing to them
 */
unordered_map<char, Alphabet::Node*> Alphabet::createDirectedGraph() {
    // loop through all adjacent pairs of words
    for (int i = 0; i < words.size() - 1; i++) {
        string firstWord = words[i];
        string secondWord = words[i + 1];

        // init nodes from both words ahead of time, and look for diff if it exists
        // then have a single if statement to set the relation if it
        int diffIdx = -1;
        int charIdx = 0;

        while (charIdx < min(firstWord.size(), secondWord.size())) {
            char firstChar = firstWord[charIdx];
            char secondChar = secondWord[charIdx];
            
            if (firstChar != secondChar && diffIdx < 0) {
                diffIdx = charIdx;
            }
            if (nodes.count(firstChar) < 1) {
                addNewLetterNodeToGraph(firstChar);
            }
            if (nodes.count(secondChar) < 1) {
                addNewLetterNodeToGraph(secondChar);
            }

            charIdx++;
        }

        while (charIdx < firstWord.size()) {
            char charVal = firstWord[charIdx];
            addNewLetterNodeToGraph(charVal);
            charIdx++;
        }

        while (charIdx < secondWord.size()) {
            char charVal = secondWord[charIdx];
            addNewLetterNodeToGraph(charVal);
            charIdx++;
        }


        // check if difference was found
        if (diffIdx != -1) {
            Node *n1 = nodes[firstWord[diffIdx]];
            Node *n2 = nodes[secondWord[diffIdx]];

            if (n1->nextNeighbors.find(n2) == n1->nextNeighbors.end()) {
                n1->nextNeighbors.insert(n2);
                n2->prevLetterCount++;
                lettersWithZeroPrevLetters.erase(n2->charVal); 
            }
        }
    }
    return nodes;
}

/* Modifies: stack of next letters to go into alphabet
 * Returns: alphabet in string format 
 */
vector<char> Alphabet::createAlphabet() {
    // Check if a char exists that has no chars before it
    if (lettersWithZeroPrevLetters.size() < 1) {
        // No alphabet can be created
        return {};
    }
    char c = *lettersWithZeroPrevLetters.begin();
    Node *n1 = nodes[c];
    nextLetters.push(n1);

    vector<char> alphabet = {};
    bool multipleAlphabets = false; // unused here, but can be used if needed
    while (!nextLetters.empty()) {
        Node *letter = nextLetters.top();
        nextLetters.pop();
        alphabet.push_back(letter->charVal);
        // update counts of neighboring letters, and add those that are next in line to the alphabet
        for (auto &n: letter->nextNeighbors) {
            n->prevLetterCount--;
            if (n->prevLetterCount < 1) {
                // multiple letters pushed in a loop can lead to multiple possible alphabets
                nextLetters.push(n);
            }
        }
        // Can check for multiple alphabets by seeing if more than 1 letter can be next
        if (nextLetters.size() > 1) {
            multipleAlphabets = true;
        }
    }

    // invalid: not all letters were included (cycles, invalid input)
    if (nodes.size() != alphabet.size()) {
        alphabet = vector<char>{};
    }
    return alphabet;
}
