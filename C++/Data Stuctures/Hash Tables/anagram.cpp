#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
vector<vector<string>> findAnagrams(const vector<string>& dict);



vector<vector<string>> findAnagrams(const vector<string>& dict)
{
    unordered_map<string,vector<string>> anagramMap;
    vector<vector<string>> anagrams;


    for(size_t i = 0; i < dict.size(); i++){

        string temp = dict.at(i);
        sort(temp.begin(), temp.end()); // sorting the unsorted strings

        // If string does not already exists create a new key and value which is a vector of the unsotred string
        if(anagramMap.find(temp) == anagramMap.end()){
            vector<string> tempVec {dict.at(i)};
            anagramMap.insert(make_pair(temp,tempVec));

        // If the string already exist then push_back the unsorted string to the value
        } else {
            anagramMap[temp].push_back(dict.at(i));
        }
    }

    // Filling the 2-D vector in with the anagrams
    for (auto const& pair: anagramMap) {
        anagrams.push_back(pair.second);
    }

    return anagrams;
}
