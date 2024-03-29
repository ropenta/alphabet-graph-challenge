#include "Challenge.h"

using namespace std;

/* Constructor */
Alphabet::Alphabet(vector<string> in_words) {
    words = in_words;
    letterNodes = {};
    nodesWithNoPrevLetters = {};
}

/* Node constructor */
Alphabet::Node::Node(char in_char) {
    charVal = in_char;
}

/* Inserts new unique letter into graph of letter nodes */
void Alphabet::addNewLetterNodeToGraph(char charVal) {
    if (letterNodes.find(charVal) == letterNodes.end()) {
        Node *n = new Node(charVal);
        letterNodes[charVal] = n;
        nodesWithNoPrevLetters.insert(charVal);
    }
}


/* Constucts directed graph of letter nodes and builds an alphabet using prevLetterCount to determine order */
vector<char> Alphabet::findAlphabet() {
    // Check 0 or 1 word
    if (words.empty()) {
        return {};
    } 
    else if (words.size() == 1) {
        char letter = words[0][0];

        for (int i = 1; i < words[0].size(); i++) {
            if (words[0][i] != letter) {
                return vector<char>{};
            }
        }

        return vector<char>{letter};
    }

    // Build alphabet
    createDirectedGraph();
    return createAlphabet();
}


/* Create a node for each letter and store first different between adjacent words */
void Alphabet::createDirectedGraph() {
    for (int i = 0; i < words.size() - 1; i++) {
        
        string firstWord = words[i];
        string secondWord = words[i + 1];
        int diffIdx = -1;
        int charIdx = 0;

        while (charIdx < max(firstWord.size(), secondWord.size())) {
            if (charIdx < firstWord.size()) {
                addNewLetterNodeToGraph(firstWord[charIdx]);
            }
            if (charIdx < secondWord.size()) {
                addNewLetterNodeToGraph(secondWord[charIdx]);
            }
            
            if (diffIdx < 0 && charIdx < firstWord.size() && charIdx < secondWord.size() 
                    && firstWord[charIdx] != secondWord[charIdx]) {
                diffIdx = charIdx;
            }
            charIdx++;
        }

        // update letter nodes when difference is found
        if (diffIdx != -1) {
            Node *n1 = letterNodes[firstWord[diffIdx]];
            Node *n2 = letterNodes[secondWord[diffIdx]];

            if (n1->nextLetters.find(n2) == n1->nextLetters.end()) {
                n1->nextLetters.insert(n2);
                n2->prevLetterCount++;
                nodesWithNoPrevLetters.erase(n2->charVal); 
            }
        }
    }
}

/* Use stack to keep track of next letter(s) to pull from graph to add to alphabet 
 * Decrease prevLetterCount for each adjacent letter node and add to stack if count is 0 */
vector<char> Alphabet::createAlphabet() {
    if (nodesWithNoPrevLetters.empty()) {
        return {};
    }

    // stack handles multiple possible alphabets
    vector<char> alphabet = {};
    stack<Node*> nextLetters;
    Node *letterNode = letterNodes[*nodesWithNoPrevLetters.begin()];
    nextLetters.push(letterNode);
    
    while (!nextLetters.empty()) {
        letterNode = nextLetters.top();
        nextLetters.pop();
        alphabet.push_back(letterNode->charVal);

        for (auto &n: letterNode->nextLetters) {
            n->prevLetterCount--;

            if (n->prevLetterCount == 0) {
                nextLetters.push(n);
            }
        }
    }

    if (letterNodes.size() != alphabet.size()) {
        alphabet = vector<char>{};
    }

    return alphabet;
}
