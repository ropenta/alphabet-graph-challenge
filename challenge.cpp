#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>

using namespace std; // possibly remove this

struct Node {
    char c;                         // current char
    int inCount = 0;                    // # of incoming arrows
    unordered_set<Node*> nextNeighbors;    // neighbors confirmed to be after this char

    Node(char in_char) {
        c = in_char;
    }
};

/* Solve for alphabet   */
/* Input: list of words */
/* Output: alphabet     */
string findAlphabet(vector<string> &words) {
    /* TODO */
    if (words.size() < 1) {
        return "";
    }

    // 0. create data structures
    unordered_map<char, Node*> nodes;
    unordered_set<char> zeroInCount;
    stack<Node*> nextLetters;
    string alphabet = "";

    // 1. compare adjacent words, find first difference if it exists
    /* TODO add this in helper function */
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
                cout << n1->c << " " << n2->c << "\n";

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

    // 2. find first letter
    /* TODO: handle errors in a more standard way (try-catch, exception) */
    if (zeroInCount.size() < 1) {
        exit(1);
    }
    char c = *zeroInCount.begin();
    Node *n1 = nodes[c];
    nextLetters.push(n1);

    // 3. add curr item to alphabet, get neighbors, decrease inCount, add zero in count nodes to stack
    while (!nextLetters.empty()) {
        Node *letter = nextLetters.top();
        nextLetters.pop();
        alphabet += letter->c;

        for (auto &n: letter->nextNeighbors) {
            n->inCount--;
            if (n->inCount < 1) {
                nextLetters.push(n);
            }
        }
    }

    return alphabet;
}

/* Driver */
int main() {
    vector<string> wordsWithFirstLetterNested;
    // TODO: read from input test file instead of here
    wordsWithFirstLetterNested.push_back("bb");
    wordsWithFirstLetterNested.push_back("bh");
    wordsWithFirstLetterNested.push_back("hb");
    wordsWithFirstLetterNested.push_back("hc");
    wordsWithFirstLetterNested.push_back("hd");
    wordsWithFirstLetterNested.push_back("dc");
    wordsWithFirstLetterNested.push_back("dh");
    wordsWithFirstLetterNested.push_back("ddg");
    wordsWithFirstLetterNested.push_back("ddb");

    string s = "alphabet: " + findAlphabet(wordsWithFirstLetterNested);
    cout << s << "\n";

    vector<string> exampleTestCase;
    exampleTestCase.push_back("bca");
    exampleTestCase.push_back("aaa");
    exampleTestCase.push_back("acb");
    string s2 = "alphabet: " + findAlphabet(exampleTestCase);
    cout << s2 << "\n";

    return 0;
}