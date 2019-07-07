#include "WordLadder.h"
#include <fstream>
using namespace std; 

WordLadder::WordLadder(const string &filename) {
    string word;
    ifstream inFS;
    inFS.open(filename.c_str());
    if(!inFS.is_open()) {
        cout << "Couldn't open the file!" << endl;
        return;
    }
    while(inFS >> word) {
        if(word.size() != 5) {
            cout << "Word is not 5 characters long!" << endl;
            return;
        }
        dict.push_back(word);
    }

    inFS.close();
}

stack<string> WordLadder::createWordLadder(const string& first, const string &end) {
    stack<string> emptyStack; //return empty stack if it cant find a wordladder
    stack<string> firstWord;
    firstWord.push(first);
    queue<stack<string>> stacks;
    stacks.push(firstWord);

    while(!stacks.empty()) {
        string word = stacks.front().top();
        for(list<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
            int lettersOff = 0;
            for(unsigned j = 0; j < it->size(); ++j) {
                if(word.at(j) != it->at(j)) {
                    ++lettersOff;
                }
            }
            if(lettersOff == 1) {
                stack<string> copy = stacks.front();
                copy.push(*it);
                if(*it == end) { return copy; }
                else {
                    stacks.push(copy);
                    it = dict.erase(it);
                    --it;
                }
            }
        }
        stacks.pop();
    }
    return emptyStack;
}


void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    ofstream outFS;
    int numChecks = 0;
    for(list<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
        if(start == *it || end == *it) 
            ++numChecks;
    }
    if(numChecks == 0) { 
        cout << "Error. First and second words do not exist in the dictionary." << endl;
        return;
    }

    stack<string> wordLadderReverse = createWordLadder(start, end);
    stack<string> wordLadder;
    while(!wordLadderReverse.empty()) {
        wordLadder.push(wordLadderReverse.top());
        wordLadderReverse.pop();
    }
    outFS.open(outputFile.c_str());
    if(!outFS.is_open()) {
        cout << "Couldn't open the file!" << endl;
        return;
    }
    if(start == end) {
        outFS << start << endl;
        return;
    }
    if(!wordLadder.empty()) {
        while(!wordLadder.empty()) {
            outFS << wordLadder.top() << endl;
            wordLadder.pop();
        }
    }
    else { 
        outFS << "No Word Ladder Found." << endl; 
    }

    outFS.close();
} 