#define CATCH_CONFIG_MAIN
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>
#include "catch.hpp" // unit testing with Catch2

using namespace std;

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
string createAlphabet(stack<Node*> &nextLetters) {
    string alphabet = "";
    while (!nextLetters.empty()) {
        Node *letter = nextLetters.top();
        nextLetters.pop();
        alphabet += letter->c;

        for (auto &n: letter->nextNeighbors) {
            n->inCount--;
            if (n->inCount < 1) {
                // multiple letters pushed in a loop can lead to multiple possible alphabets
                nextLetters.push(n);
            }
        }
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
    for (int i = 0; i < words.size() - 1; i++) {
        string firstWord = words[i];
        string secondWord = words[i + 1];
        for (int j = 0; j < firstWord.size() && j < secondWord.size(); j++) {
            char firstChar = firstWord[j];
            char secondChar = secondWord[j];
            if (firstChar != secondChar) {
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
                // set relation in nodes graph
                Node *n1 = nodes[firstChar];
                Node *n2 = nodes[secondChar];

                // only add relation if it doesn't already exist
                if (n1->nextNeighbors.find(n2) == n1->nextNeighbors.end()) {
                    n1->nextNeighbors.insert(n2);
                    n2->inCount++;
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
string findAlphabet(vector<string> &words) {
    /* TODO */
    if (words.size() < 1) {
        return "";
    } else if (words.size() == 1) {
        // edge case: 1 word with 1 letter
        if (words[0].size() == 1) {
            return words[0];
        } else {
            return "";
        }
    }

    // 0. create data structures
    unordered_map<char, Node*> nodes;
    unordered_set<char> zeroInCount;
    stack<Node*> nextLetters;
    string alphabet = "";

    // 1. compare adjacent words, find first difference if it exists
    createDirectedGraph(words, nodes, zeroInCount);

    // 2. find and add first letter, if it is unambiguous
    /* TODO: handle errors in a more standard way (try-catch, exception) */
    addFirstLetter(nodes, zeroInCount, nextLetters);

    // 3. add curr item to alphabet, get neighbors, decrease inCount, add zero in count nodes to stack
    alphabet = createAlphabet(nextLetters);
    return alphabet;
}

TEST_CASE( "Valid alphabets") {
    vector<string> sampleTest = {"bca", "aaa", "acb"};
    REQUIRE( findAlphabet(sampleTest) == "bac" );
    vector<string> firstAlphabetLetterNestedInWord = {"bb", "bh", "hb", "hc", "hd", "dc", "dh", "ddg", "ddb"};
    REQUIRE( findAlphabet(firstAlphabetLetterNestedInWord) == "gbchd" );
}

TEST_CASE( "Valid small inputs") {
    vector<string> noWords = {};
    vector<string> oneLetter = {"h"};
    vector<string> oneWord = {"hi"};
    REQUIRE( findAlphabet(noWords) == "");
    REQUIRE( findAlphabet(oneLetter) == "h");
    REQUIRE( findAlphabet(oneWord) == "");
}

TEST_CASE( "Invalid small inputs") {
    vector<string> oneWord = {"hi"};
    REQUIRE( findAlphabet(oneWord) == "");
}

// TEST_CASE( "Duplicate words") {
//     vector<string> sameWords = {"hi"};
//     vector<string> duplicatesAtEnd = {"bb", "bh", "hb", "hb"};
//     vector<string> duplicatesAtStart = {"bb", "bb", "hb", "hi"};
//     vector<string> multipleDuplicates = {"bb", "bb", "hb", "hb"};
//     REQUIRE( findAlphabet(sameWords) == "hi");
//     REQUIRE( findAlphabet(duplicatesAtEnd) == "bh");
//     REQUIRE( findAlphabet(duplicatesAtStart) == "bhi"); // ambiguous
//     REQUIRE( findAlphabet(multipleDuplicates) == "bh");
// }