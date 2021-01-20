#include "Challenge.h"

using namespace std;

/* Constructor */
Alphabet::Alphabet(vector<string> in_words) {
    words = in_words;
    nodes = {};
    nextLetters = {};
    zeroInCount = {};
    alphabet = {};
}
/* Node constructor */
Alphabet::Node::Node(char in_char) {
    c = in_char;
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

    // 2. find and add first letter, if it is unambiguous
    nextLetters = addFirstLetter();

    // 3. add curr item to alphabet, get neighbors, decrease inCount, add zero in count nodes to stack
    return createAlphabet();
}


/* Modifies: empty graph, set of letters with no inbound nodes pointing to them
 */
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


/* Modifies: graph, set of letters with no inbound nodes pointing to them, 
 *            empty stack of next letters to go into alphabet
 */
stack<Alphabet::Node*> Alphabet::addFirstLetter() {
    // Check if a char exists that has no chars before it
    if (zeroInCount.size() < 1) {
        // No alphabet can be created
        return {};
    }
    char c = *zeroInCount.begin();
    Node *n1 = nodes[c];
    nextLetters.push(n1);
    return nextLetters;
}


/* Modifies: stack of next letters to go into alphabet
 * Returns: alphabet in string format 
 */
vector<char> Alphabet::createAlphabet() {
    vector<char> alphabet = {};
    bool multipleAlphabets = false; // unused here, but can be used if needed
    while (!nextLetters.empty()) {
        Node *letter = nextLetters.top();
        nextLetters.pop();
        alphabet.push_back(letter->c);
        // update counts of neighboring letters, and add those that are next in line to the alphabet
        for (auto &n: letter->nextNeighbors) {
            n->inCount--;
            if (n->inCount < 1) {
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
