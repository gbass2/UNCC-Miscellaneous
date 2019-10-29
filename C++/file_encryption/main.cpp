#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

//concatenates the value of argv[3] and cipher and removes duplicate characters
void remDupes(const char cipher[], char str[], const char* temp){
    //coppying argv[3] into str
    strcpy(str,temp);
    
    //concatenating cipher and str
    strcat(str, cipher);
    
    //removing character duplicates
    for(size_t i = 0; i < strlen(str); i++){
  		for(size_t j = i + 1; str[j] != '\0'; j++){
  			if(str[j] == str[i]){
  				for(size_t k = j; str[k] != '\0'; k++){
					str[k] = str[k + 1];
				}
 			}
		}
	}
}

int main(int argc, char* argv[]){
    //opening the input file
    string fileNameIn (argv[4]);
    ifstream inFile;
    inFile.open(fileNameIn);
    //opening the output files
    string fileNameOut (argv[5]);
    ofstream outFile;
    outFile.open(fileNameOut);
    
    //declaring a char of size argv[3] and creating a temp pointer to the value of argv[3]
    char key[strlen(argv[3])];
    char cipher[] = "zyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA"; //reverse alphabets
    
    //setting a temp pointer to argv[1] to remove segmentaion fault
    char* temp = argv[1];
    
    //concatenates the value of argv[3] and cipher and removes duplicate characters
    remDupes(cipher, key, argv[3]);
    
    //converting key to a c++ string
    string encrypted;
    encrypted = key; 

    string decrypted = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string contents;
    string decryptedMessage;
    string encryptedMessage;
    
    //determining if -e is used
    if(strcmp("-e", temp) == 0){
        //getting the decrypted message from the file
        getline(inFile, contents);
        //encrypting message
        for (char c: contents) {
            size_t pos = decrypted.find(c);
            if (pos != string::npos) {
                char newChar = encrypted.at(pos);
                encryptedMessage += newChar;
            //if the character is not found, it will not be changed
            } else {
                encryptedMessage += c;
            }
        }
        //outputting to the file
        outFile << encryptedMessage;
    }
    
    //determining if -d is used
    if(strcmp("-d", temp) == 0){
        //getting the encrypted message from the file
        getline(inFile, contents);
        //decrypting message 
        for (char c: contents) {
            size_t pos = encrypted.find(c);
            if (pos != string::npos) {
                char newChar = decrypted.at(pos);
                decryptedMessage += newChar;
            //if the character is not found, it will not be changed
            } else {
                decryptedMessage += c;
            }
         }  
      
        //outputting to the file
        outFile << decryptedMessage;
    }
 
    
    inFile.close();
    outFile.close();

    return 0;
}