# jan-2021-test-challenge

## Problem:
We're given a list of words sorted in "alphabetical" order. The letters consist of `'a-z'`, `'A-Z'`, and `'0-9'`. These individual letters are not necessarily sorted by the typical `'a-z'` as we might expect. Instead, there could be any ordering of these letters, and our job is to figure out the "alphabetical" ordering.

To get a fully formed alphabet, the input list of words needs to have enough information to derive the complete order of the alphabet. Otherwise, an empty alphabet will be returned. If multiple possible alphabets can be formed, only one set will be returned.

Sample Input:
`["bca", "aaa", "acb"]`

Output:
`['b', 'a', 'c']`

Invalid Input (cycle):
`["ba", "aa", "ab"]`

Output:
`[]`

## Running this program:
You can type `make` followed by the command you'd like to run
* `$ make run inputFile=test/input.txt` builds a `program` executable, runs it, and prints out output
    * the `inputFile` value can be any input file with a valid set of words (separated by newlines) 

Running unit tests:
* `$ make clean`
* `$ make test` runs the suite of unit tests defined in ChallengeTest.cpp
* `$ make clean` removes the executables created by the `program` and `test` commands. You should run this after each command to ensure you are using the latest code.

## A Solution
Our goal is to take the ordered input set:  
> `["bca", "aaa", "acb"]`

and return the following ordering:  
> `["b", "a", "c"]`

By directly comparing adjacent words, we can figure out the ordering of letters  
>bca  
aaa  
`'b'` comes before `'a'`

### How can we store this information? 

When we encounter
a direct relationship between two letters, we can store the following data:
* if we know `'b'` comes before `'a'`:
    * `'b'` has a set of `"nextLetters"` that come after it in the alphabet, and `'a'` is included in this set
    * `'a'` has a set of `"prevLetters"` that comes before it in the alphabet, and `'b'` is included in this set

>`b->prevLetters = {}`  
`b->nextLetters = {a}`  
`a->prevLetters = {b}`  
`a->nextLetters = {}`

We can go through all the words in the input list and derive these relationships and store them.

### How can we figure out which letter comes first?   
It's simply the letter with an empty `"prevLetters"` set.  
Having no letters in `"prevLetters"` means that no letters could have come before, so it must be the first.  

Once we find the letter with an empty `"prevLetters"` set, we can add it to the alphabet.  

> `alphabet: ['b']`

Once the letter `'b'` is added, we need to remove it from all the letters that include `'b'` in their `"prevLetters"` set.
Thankfully, we can easily find these values by checking the nextLetters set of `'b'`

>`a->prevLetters = {}`  

Now we see that `'a'` has an empty prevLetters set, and we can use that as our next letter.
We can repeat this process until all letters have been added to the alphabet.

### Optimization
One improvement we can make is, instead of storing all the `"prevLetters"` values, we can use a count instead. Anytime we add a new letter `'x'` to the alphabet,
we can decrease the `"prevLetterCount"` of each letter in `'x'`s `"nextLetters"` set.

>`a->prevLetterCount--`
