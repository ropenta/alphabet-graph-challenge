#include "catch.hpp" // unit testing with Catch2: https://github.com/catchorg/Catch2/tree/v2.x
#include "Challenge.h"
using namespace std;

TEST_CASE( "Test all function calls") {
    Alphabet sampleTest = Alphabet({"bca", "aaa", "acb"});
    REQUIRE( sampleTest.findAlphabet() == vector<char>{'b', 'a', 'c'}); 
    REQUIRE( sampleTest.createDirectedGraph().size() == 3);
    REQUIRE( sampleTest.createAlphabet() == vector<char>{'b', 'a', 'c'});
}

TEST_CASE( "Test valid alphabets") {
    Alphabet sampleTest = Alphabet({"bca", "aaa", "acb"});
    Alphabet firstAlphabetLetterNestedInLastWord = Alphabet({"bb", "bh", "hb", "hc", "hd", "dc", "dh", "ddg", "ddb"});
    REQUIRE( sampleTest.findAlphabet() == vector<char>{'b', 'a', 'c'});
    REQUIRE( firstAlphabetLetterNestedInLastWord.findAlphabet() == vector<char>{'g','b','c','h','d'} );
}

TEST_CASE( "Test valid small inputs") {
    Alphabet noWords = Alphabet({});
    Alphabet oneLetter = Alphabet({"h"});
    Alphabet oneLetterWords = Alphabet({"h", "i", "a", "b", "b"});
    Alphabet oneWordTwoSameLetters = Alphabet({"hh"});
    REQUIRE( noWords.findAlphabet() == vector<char>{});
    REQUIRE( oneLetter.findAlphabet() == vector<char>{'h'});
    REQUIRE( oneLetterWords.findAlphabet() == vector<char>{'h','i','a','b'});
    REQUIRE( oneWordTwoSameLetters.findAlphabet() == vector<char>{'h'});
}

TEST_CASE( "Test valid alphanumeric inputs") {
    Alphabet numbers = Alphabet({"231", "111", "132"});
    Alphabet numbersAndLetters = Alphabet({"1A", "AB", "B2", "21"});
    REQUIRE( numbers.findAlphabet() == vector<char>{'2', '1', '3'});
    REQUIRE( numbersAndLetters.findAlphabet() == vector<char>{'1', 'A', 'B', '2'});
}

TEST_CASE( "Test valid duplicate words") {
    Alphabet sameWords = Alphabet({"h", "h"});
    Alphabet duplicatesAtEnd = Alphabet({"bb", "bh", "hb", "hb"});
    Alphabet multipleDuplicates = Alphabet({"bb", "bb", "hb", "hb"});
    REQUIRE( sameWords.findAlphabet() == vector<char>{'h'});
    REQUIRE( duplicatesAtEnd.findAlphabet() == vector<char>{'b', 'h'});
    REQUIRE( multipleDuplicates.findAlphabet() == vector<char>{'b', 'h'});
}

TEST_CASE( "Test valid ambiguous alphabets") {
    Alphabet duplicatesAtStart = Alphabet({"bb", "bb", "hb", "hi"});
    REQUIRE( duplicatesAtStart.findAlphabet() == vector<char>{'b', 'h', 'i'});
}

TEST_CASE( "Test invalid small inputs") {
    Alphabet oneWord = Alphabet({"hi"});    
    REQUIRE( oneWord.findAlphabet() == vector<char>{});
}

TEST_CASE( "Test invalid long inputs") {
    Alphabet longFirstWord = Alphabet({"dcabzyx", "c"});    
    REQUIRE( longFirstWord.findAlphabet() == vector<char>{});
}

TEST_CASE( "Test invalid cycles") {
    Alphabet twoLetterCycle = Alphabet({"ba", "aa", "ab"});
    Alphabet threeLetterCycle = Alphabet({"abc", "acb", "abc", "bca"});
    REQUIRE( twoLetterCycle.findAlphabet() == vector<char>{});
    REQUIRE( threeLetterCycle.findAlphabet() == vector<char>{});
}
