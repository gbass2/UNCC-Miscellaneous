// Practice question for pretest - test

#include <iostream>
#include <vector>
// #include "practice_yoursoln.cpp"

using namespace std;

vector<string> removeDuplicates(const vector<string>& s);

int main() {
    // Test 1. Output should be - to be or not is the question 
    vector<string> line1 = {"to", "be", "or", "not", "to", "be", "is", "the", "question"} ;
    vector<string> result1  = removeDuplicates(line1);
    for(int i = 0; i < result1.size(); i++) {
        cout << result1[i] << " ";
    }
    cout << endl;
    
    // Test 2. Output should be - of all the gin joints in towns world she walks into mine 
    vector<string> line2 = {"of", "all", "the", "gin", "joints", "in", "all", "the", "towns", "in", "all", "the", "world", "she", "walks", "into", "mine"} ;
    vector<string> result2  = removeDuplicates(line2);
    for(int i = 0; i < result2.size(); i++) {
        cout << result2[i] << " ";
    }
    cout << endl;
}