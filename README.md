# jan-2021-test-challenge

## Problem:
This program takes in a list of words sorted in alphabetical order using ASCII letters, with any ordering of those letters, and determines the ordering of the alphabet.

To get a fully formed alphabet, the input list of words needs to have enough information to derive the complete order of the alphabet. Otherwise, an empty alphabet will be returned.

Sample Input:
`["bca", "aaa", "acb"]`

Output:
`['b', 'a', 'c']`

Invalid Input:
`["ba", "aa", "ab"]`

Output:
`[]`

## Running this program:
First, download `clang` so that you can run c++14 on your machine

Then, you can type `make` followed by the command you'd like to run

For example, `make program` builds a `program` executable that can be directly run with `./program`.
* for running your own custom example, you can modify `main.cpp` to use a different set of input words

Running `make test` runs the suite of unit tests defined in ChallengeTest.cpp
