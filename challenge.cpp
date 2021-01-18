#define CATCH_CONFIG_MAIN
#include <iostream>
#include <unordered_map>  // hash map
#include <unordered_set>  // hash set
#include <stack>
#include <vector>
#include "catch.hpp" // unit testing with Catch2

using namespace std;

/* Each unique char belongs to a Node */
struct Node {
    char c;                         // current char
    int inCount = 0;                    // # of incoming arrows
    unordered_set<Node*> nextNeighbors;    // neighbors confirmed to be after this char

    Node(char in_char) {
        c = in_char;
    }
};

/* Input: stack of next letters to go into alphabet*/
/* Modifies: stack */
/* Returns: alphabet in string format */
vector<char> createAlphabet(stack<Node*> &nextLetters, unordered_map<char, Node*> &nodes) {
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
    // not all letters were included (cycles, invalid input)
    if (nodes.size() != alphabet.size()) {
        cout << "Alphabet does not include all letters\n";
        alphabet = vector<char>{};
    }
    return alphabet;
}

/* Input: graph, set of letters with no inbound nodes pointing to them, empty stack of next letters to go into alphabet*/
/* Modifies: graph, set of letters, stack of next alphabet letters */
void addFirstLetter(unordered_map<char, Node*> &nodes, unordered_set<char> &zeroInCount, stack<Node*> &nextLetters) {
    if (zeroInCount.size() < 1) {
        cout << "No alphabet found\n";
        return;
    }
    char c = *zeroInCount.begin();
    Node *n1 = nodes[c];
    nextLetters.push(n1);
}

/* Input: word list, empty graph, set of letters with no inbound nodes pointing to them */
/* Modifies: graph, set of letters */
void createDirectedGraph(
        vector<string> &words, 
        unordered_map<char, Node*> &nodes, 
        unordered_set<char> &zeroInCount) {
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
                zeroInCount.insert(firstChar); // this node could be first in alphabet
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
}

/* Input: list of words */
/* Output: alphabet     */
vector<char> findAlphabet(vector<string> &words) {
    if (words.size() < 1) {
        return {};
    } else if (words.size() == 1) {
        // edge case: 1 word with 1 letter
        if (words[0].size() == 1) {
            char c = words[0][0];
            return vector<char>{c};
        } else {
            return {};
        }
    }

    // 0. create data structures
    unordered_map<char, Node*> nodes;
    unordered_set<char> zeroInCount;
    stack<Node*> nextLetters;
    vector<char> alphabet = {};

    // 1. compare adjacent words, find first difference if it exists
    createDirectedGraph(words, nodes, zeroInCount);

    // 2. find and add first letter, if it is unambiguous
    /* TODO: handle errors in a more standard way (try-catch, exception) */
    addFirstLetter(nodes, zeroInCount, nextLetters);

    // 3. add curr item to alphabet, get neighbors, decrease inCount, add zero in count nodes to stack
    return createAlphabet(nextLetters, nodes);
}

TEST_CASE( "Valid alphabets") {
    vector<string> sampleTest = {"bca", "aaa", "acb"};
    vector<string> firstAlphabetLetterNestedInWord = {"bb", "bh", "hb", "hc", "hd", "dc", "dh", "ddg", "ddb"};

    REQUIRE( findAlphabet(sampleTest) == vector<char>{'b', 'a', 'c'});
    REQUIRE( findAlphabet(firstAlphabetLetterNestedInWord) == vector<char>{'g','b','c','h','d'} );
}

TEST_CASE( "Valid small inputs") {
    vector<string> noWords = {};
    vector<string> oneLetter = {"h"};
    vector<string> oneLetterWords = {"h", "i", "a", "b", "b"};

    REQUIRE( findAlphabet(noWords) == vector<char>{});
    REQUIRE( findAlphabet(oneLetter) == vector<char>{'h'});
    REQUIRE( findAlphabet(oneLetterWords) == vector<char>{'h','i','a','b'});
}

TEST_CASE( "Valid duplicate words") {
    vector<string> sameWords = {"h", "h"};
    vector<string> duplicatesAtEnd = {"bb", "bh", "hb", "hb"};
    vector<string> duplicatesAtStart = {"bb", "bb", "hb", "hi"};
    vector<string> multipleDuplicates = {"bb", "bb", "hb", "hb"};

    REQUIRE( findAlphabet(sameWords) == vector<char>{'h'});
    REQUIRE( findAlphabet(duplicatesAtEnd) == vector<char>{'b', 'h'});
    REQUIRE( findAlphabet(duplicatesAtStart) == vector<char>{'b', 'h', 'i'}); // ambiguous
    REQUIRE( findAlphabet(multipleDuplicates) == vector<char>{'b', 'h'});
}

TEST_CASE( "Invalid small inputs") {
    vector<string> oneWord = {"hi"};
    REQUIRE( findAlphabet(oneWord) == vector<char>{});
}

TEST_CASE( "Invalid cycles") {
    vector<string> twoLetterCycle = {"ba", "aa", "ab"};
    vector<string> threeLetterCycle = {"abc", "acb", "abc", "bca"};

    REQUIRE( findAlphabet(twoLetterCycle) == vector<char>{});
    REQUIRE( findAlphabet(threeLetterCycle) == vector<char>{});
}