# jan-2021-test-challenge

## Problem:
This program takes in a list of words sorted in alphabetical order using ASCII letters, with any ordering of those letters, and determines the ordering of the alphabet.

To get a fully formed alphabet, the input list of words needs to have enough information to derive the complete order of the alphabet. Otherwise, an empty alphabet will be returned.

Sample Input:
`["bca", "aaa", "acb"]`

Output:
`['b', 'a', 'c']`

Invalid Input (cycle):
`["ba", "aa", "ab"]`

Output:
`[]`

## Running this program:
First, download `clang` so that you can run c++14 on your machine

Then, you can type `make` followed by the command you'd like to run
* For example, `make run` builds a `program` executable, runs it, and prints out output
* Running `make test` runs the suite of unit tests defined in ChallengeTest.cpp
* Running `make clean` removes the executables created by the `program` and `test` commands. You should run this after each command to ensure you are using the latest code.

## Using your own custom input:
You can modify `main.cpp` to use a different set of input words, and `make run` will build the executable.

Reading through `Challenge.h` first will help in understanding `Challenge.cpp` better. All the unit tests are included in `ChallengeTest.cpp`.
