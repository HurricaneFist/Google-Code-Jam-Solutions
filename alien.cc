// Solution to "Alien Language" from Google's Code Jam, by Ian K. Lee
// https://code.google.com/codejam/contest/90101/dashboard

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {

  // L is the number of tokens
  // D is the number of words
  // N is the number of test cases
  int L, D, N;

  ifstream inputFile;
  inputFile.open(argv[1]);

  string line;
  vector<string> words, patterns;
  inputFile >> L >> D >> N;
  int ct = 0;
  while (inputFile >> line) {
    if (ct < D)
      words.push_back(line);
    else
      patterns.push_back(line);

    ct++;
  }

  // for each pattern
  for (int i = 0; i < patterns.size(); i++) {
    string pattern = patterns[i];
    vector<string> tokens;

    // for each char in one pattern
    for (int j = 0; j < pattern.length(); j++) {
      if (pattern[j] == '(') {
        tokens.push_back(""); // start a new token (with multiple chars)
        j++;
        while (pattern[j] != ')') {
          tokens[tokens.size()-1] += pattern[j];
          j++;
        }
      } else {
        tokens.push_back(""); // start a new token (with one char)
        tokens[tokens.size()-1] += pattern[j];
      }
    }

    // now we have the tokens, time for pattern matching for each word
    int wordMatches = 0;
    for (int j = 0; j < words.size(); j++) {
      int charMatches = 0;
      // for each character in the word, and token in the token set...
      // both of which, remember, MUST be exactly L length
      for (int k = 0; k < L; k++)
        if (tokens[k].find(words[j][k]) != string::npos)
          charMatches++;

      if (charMatches == L)
        wordMatches++;
    }

    // now we can print the number of word matches for each case
    cout << "Case #" << i+1 << ": " << wordMatches << endl;
  }
}
