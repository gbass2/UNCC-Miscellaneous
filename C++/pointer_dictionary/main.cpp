#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    
    //Creates a vector of pointers of type string and userInput of type string. Also a boolean expression is declared
    string userInput;
    vector<string*> sentence;
    bool matchFound = false;
    
    //Accepts input until the user enters '.', '?', or '!'
    do{
        cout << "Enter a word to add to the sentence ('.', '?', '!' to quit): ";
        cin >> userInput;
        matchFound = false;
        
        //Loops through sentence and if userInput equals senetence.at(i) it will append the current word
        for(size_t i = 0; i < sentence.size(); i++){
            if (*sentence.at(i) == userInput){
                cout << "Match Found!" << endl;
                sentence.push_back(sentence.at(i));
                matchFound = true;
                break;
            }
        }
        
        //If userInput is not present, then userInput will be appended
        if (!matchFound){    
            string *temp = new string;
            *temp = userInput;
            sentence.push_back(temp);
        }
    }
    
    while(userInput != "." && userInput != "?" && userInput != "!");
    
    cout << endl;
    
    //Displays the sentence and removes the whitespace before the final punctuation
    for(size_t i = 0; i < sentence.size()-2; i++)
        cout << *sentence.at(i) << " ";
    cout << *sentence.end()[-2];
    cout << *sentence.back();
    
    
    
    cout << endl;
    return 0;
}
