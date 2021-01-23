# jan-2021-test-challenge

## Problem:
We're given a list of words sorted in "alphabetical" order. The letters consist of 'a-z', 'A-Z', and '0-9'. These individual letters are not necessarily sorted by the typical 'a-z' as we might expect. Instead, there could be any ordering of these letters, and our job is to figure out the "alphabetical" ordering.

To get a fully formed alphabet, the input list of words needs to have enough information to derive the complete order of the alphabet. Otherwise, an empty alphabet will be returned. If multiple possible alphabets can be formed, only one set will be returned.

Sample Input:
`["bca", "aaa", "acb"]`

Output:
`['b', 'a', 'c']`

Invalid Input (cycle):
`["ba", "aa", "ab"]`

Output:
`[]`

One [solution](#a-solution) is given below.

## Running this program:
You can type `make` followed by the command you'd like to run
* For example, `make run` builds a `program` executable, runs it, and prints out output
* Running `make test` runs the suite of unit tests defined in ChallengeTest.cpp
* Running `make clean` removes the executables created by the `program` and `test` commands. You should run this after each command to ensure you are using the latest code.

## Using your own custom input:
You can modify `main.cpp` to use a different set of input words, and `make run` will build the executable.

Reading through `Challenge.h` first will help in understanding `Challenge.cpp` better. All the unit tests are included in `ChallengeTest.cpp`.

## A Solution
Goal:
- We want to represent the alphabet as a directed graph (connections between letters are directional).
- Each letter in the alphabet has a set of letters that come before, and set of letters that come later.
- We don't need to store the whole set of letters that come before and after the letter, since it would take up more memory than is needed.
- Instead, we can store the set of letters that are confirmed to come after, and a count of letters that come before.
- We'd like to associate each letter with information that will help determine the order relative to other letters.

Implementation:
- We can store each unique letter inside a Node class that contains extra information.
- Anytime we encounter a new ordering between two letters (e.g. 'b' comes before 'a'), we will store two values:
    1) b's set of adjacent letters that come after it in the alphabet includes 'a'
        bNode.nextNeighbors.add(aNode);
    2) 'a' is pointed at by 'b', which we can represent with 'prevLetterCount'.
        a.prevLetterCount++
- To determine the first letter to choose, we choose the Node with a 'prevLetterCount' of 0.
- This indicating that no letters come before in the alphabet.
