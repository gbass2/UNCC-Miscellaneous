#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<string>> findAnagrams(const vector<string>& dict);

int main() 
{
    vector<string> word_list = {"debitcard", "elvis", "silent", "badcredit", "lives", "freedom", "listen", "levis"};
    vector<vector<string>> result = findAnagrams(word_list);
    for (auto anagrams: result) {
        for (auto words: anagrams)
            cout << words << " ";
        cout << endl;
    }
    return 0;
    
    /* Output should be -
    
    silent listen 
    debitcard badcredit 
    elvis lives levis 
    
    */
}


