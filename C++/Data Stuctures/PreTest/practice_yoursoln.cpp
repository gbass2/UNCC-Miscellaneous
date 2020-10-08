// Practice questions for pretest - Your solution

#include <iostream>
#include <vector>

using namespace std;

vector<string> removeDuplicates(const vector<string>& s) {
  // Your code here
  vector<string> res;
  bool repeated;
  for(size_t i = 0; i < s.size(); i++){
      repeated = false;
      for(size_t j = 0; j < res.size(); j++){
          if(s.at(i) == s.at(j)){
             repeated = true;
             break;
          }
      }
      if(repeated == false)
          res.push_back(s.at(i));
  }

  return res;





// Sorts the words and removes dupes but the sentence is not in order

  // vector<string> temp = s;
  // vector<string> ans;
  //
  // sort(temp.begin(), temp.end());
  //
  // for (int i = 1; i<temp.size(); i++)
  //   if (temp[i-1] == temp[i])
  //
  //     // STL function to push the duplicate
  //     // words in a new vector string
  //           temp.erase(temp.begin() +i);
  // return temp;
}
