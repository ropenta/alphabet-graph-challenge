#include "Challenge.h"

using namespace std;

/* Constructor */
Alphabet::Alphabet(vector<string> in_words) {
    words = in_words;
    nodes = {};
    lettersWithZeroPrevLetters = {};
}

/* Node constructor */
Alphabet::Node::Node(char in_char) {
    charVal = in_char;
}

/* Inserts new unique letter into graph of letter nodes */
void Alphabet::addNewLetterNodeToGraph(char charVal) {
    Node *n = new Node(charVal);
    nodes[charVal] = n;
    lettersWithZeroPrevLetters.insert(charVal);
}


/* Constucts directed graph of letter nodes and builds an alphabet using prevLetterCount to determine order */
vector<char> Alphabet::findAlphabet() {
    // Check 0 or 1 word
    if (words.size() == 0) {
        return {};
    } 
    else if (words.size() == 1) {
        char c = words[0][0];

        for (int i = 1; i < words[0].size(); i++) {
            if (words[0][i] != c) {
                return vector<char>{};
            }
        }

        return vector<char>{c};
    }

    // Build alphabet
    nodes = createDirectedGraph();
    return createAlphabet();
}


/* Create a node for each letter and store first different between adjacent words */
unordered_map<char, Alphabet::Node*> Alphabet::createDirectedGraph() {
    for (int i = 0; i < words.size() - 1; i++) {
        
        string firstWord = words[i];
        string secondWord = words[i + 1];
        int diffIdx = -1;
        int charIdx = 0;

        while (charIdx < min(firstWord.size(), secondWord.size())) {
            char firstChar = firstWord[charIdx];
            char secondChar = secondWord[charIdx];
            
            if (firstChar != secondChar && diffIdx < 0) {
                diffIdx = charIdx;
            }
            if (nodes.count(firstChar) == 0) {
                addNewLetterNodeToGraph(firstChar);
            }
            if (nodes.count(secondChar) == 0) {
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

/* Use stack to keep track of next letter(s) to pull from graph to add to alphabet 
 * Decrease prevLetterCount for each adjacent letter node and add to stack if count is 0 */
vector<char> Alphabet::createAlphabet() {
    if (lettersWithZeroPrevLetters.size() == 0) {
        return {};
    }

    // stack handles multiple possible alphabets
    stack<Node*> nextLetters;
    char c = *lettersWithZeroPrevLetters.begin();
    Node *letter = nodes[c];
    nextLetters.push(letter);
    vector<char> alphabet = {};
    
    while (!nextLetters.empty()) {

        letter = nextLetters.top();
        nextLetters.pop();
        alphabet.push_back(letter->charVal);

        for (auto &n: letter->nextNeighbors) {
            n->prevLetterCount--;

            if (n->prevLetterCount <= 0) {
                nextLetters.push(n);
            }
            
        }

    }

    if (nodes.size() != alphabet.size()) {
        alphabet = vector<char>{};
    }

    return alphabet;
}
