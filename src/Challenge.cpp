#include <iostream>
#include <unordered_map>  // hash map
#include <unordered_set>  // hash set
#include <stack>
#include <vector>
#include "Challenge.h"

using namespace std;


Alphabet::Alphabet(vector<string> in_words) {
    words = in_words;
    nodes = {};
    nextLetters = {};
    zeroInCount = {};
    alphabet = {};
}

Alphabet::Node::Node(char in_char) {
    c = in_char;
}

vector<char> Alphabet::createAlphabet() {
    vector<char> alphabet = {};
    bool multipleAlphabets = false;
    while (!nextLetters.empty()) {
        Node *letter = nextLetters.top();
        nextLetters.pop();
        alphabet.push_back(letter->c);
        for (auto &n: letter->nextNeighbors) {
            n->inCount--;
            if (n->inCount < 1) {
                // multiple letters pushed in a loop can lead to multiple possible alphabets
                nextLetters.push(n);
            }
        }
        if (nextLetters.size() > 1) {
            multipleAlphabets = true;
        }
    }
    // stack contained more than 1 letter at some point
    if (multipleAlphabets) {
        cout << "Multiple alphabets are possible\n";
    }
    // invalid: not all letters were included (cycles, invalid input)
    if (nodes.size() != alphabet.size()) {
        cout << "Alphabet does not include all letters\n";
        alphabet = vector<char>{};
    }
    return alphabet;
}

stack<Alphabet::Node*> Alphabet::addFirstLetter() {
    if (zeroInCount.size() < 1) {
        cout << "No alphabet found\n";
        return {};
    }
    char c = *zeroInCount.begin();
    Node *n1 = nodes[c];
    nextLetters.push(n1);
    return nextLetters;
}

/* Input: word list, empty graph, set of letters with no inbound nodes pointing to them */
/* Modifies: graph, set of letters */
unordered_map<char, Alphabet::Node*> Alphabet::createDirectedGraph() {
    // loop through all adjacent pairs of words
    for (int i = 0; i < words.size() - 1; i++) {
        string firstWord = words[i];
        string secondWord = words[i + 1];
        // loop through both words to see if there's a difference
        for (int j = 0; j < firstWord.size() && j < secondWord.size(); j++) {
            char firstChar = firstWord[j];
            char secondChar = secondWord[j];
            // create new Nodes if either doesn't aleady exist
            if (nodes.count(firstChar) < 1) {
                Node *n1 = new Node(firstChar);
                nodes[firstChar] = n1;
                // this node could be first in alphabet
                zeroInCount.insert(firstChar);
            }
            if (nodes.count(secondChar) < 1) {
                Node *n2 = new Node(secondChar);
                nodes[secondChar] = n2;
            }
            // look for difference
            if (firstChar != secondChar) {
                Node *n1 = nodes[firstChar];
                Node *n2 = nodes[secondChar];
                // only add relation in nodes graph if it doesn't already exist
                if (n1->nextNeighbors.find(n2) == n1->nextNeighbors.end()) {
                    n1->nextNeighbors.insert(n2);
                    n2->inCount++;
                    // remove node2 from set of potential first letters
                    if (zeroInCount.count(secondChar) > 0) {
                        zeroInCount.erase(secondChar);
                    }    
                }
                // skip rest of loop (necessary, not an optimzation)
                break;
            }
        }
    }
    return nodes;
}

/* Input: list of words */
/* Output: alphabet     */
vector<char> Alphabet::findAlphabet() {
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

    // 2. find and add first letter, if it is unambiguous
    nextLetters = addFirstLetter();

    // 3. add curr item to alphabet, get neighbors, decrease inCount, add zero in count nodes to stack
    return createAlphabet();
}

// TODO:
// https://github.com/anderspitman/cpp_bootstrap
// move tests into separate file
// create a Makefile for 'run' with input, and 'test'
// allow for user to input an input file, or multiple strings
// allow user to run program as CLI tool
