#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "number.h"

// Default constructorz
Number::Number(){
}

// Overloaded constructor
Number::Number(string input) : number{input} {
}

// Converts the passed in string to a double
double Number::CONVERT_TYPE(string input){
    long double numberIn;
    
    stringstream ss(input);
    ss >> numberIn;
    
    return numberIn;
}

// Converts a passed in double to a string
string Number::CONVERT_TYPE(long double input){
    ostringstream ss;
    
    ss << input;
    string numberIn = ss.str();
    
    return numberIn;
}

// Converts a passed in string to a double
void Number::SET_NUMBER(string number){
    this->number = number;
}

// Returns the value for the variable number
string Number::GET_NUMBER() const {
    return number;
}

// Converts the incoming decimal string to a binary string
string Number::CONVERT_TO_BINARY(string input){
    long double numberIn = CONVERT_TYPE(input);  // Convert to double

    numberIn = abs(numberIn);           // Removes the negative for decimal division
    
    // Split the number up before the decimal and after
    unsigned long long int integer = numberIn;             // Removes Fraction
    long double decimal = numberIn - integer;   // Removes Integer
    
    string binary;

    // Convert to binary
    while(integer){
        unsigned long long int rem = integer % 2;
        
        // Append 0 to binary
        binary.push_back(rem + '0');
        
        integer /= 2;
    }

    reverse(binary.begin(),binary.end());
    
    // Computes the numbers after the radix and appens it to the binary number
    if (decimal != 0){
        binary.push_back('.'); // Append a decimal point on to the bianry number
    
        int k = 23;
        
        while (k--){
            // Find next bit in fraction 
            decimal *= 2; 
            unsigned long long int fraction = decimal; 
            if (fraction == 1) 
            { 
                decimal -= 1; 
                binary.push_back(1 + '0'); 
            } 
            else
                binary.push_back(0 + '0'); 
        } 
    }
    return binary;
}

// Converts the binary exponent of a floating point number to a decimal
int Number::BINARY_TO_DECIMAL_EXPONENT(unsigned long long int n){
    unsigned long long int decimalNumber = 0; 
    int i = 0; 
    unsigned long long int remainder;
    while (n!=0) {
        remainder = n % 10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

// Converts the binary mantissa of a floating point number to a decimal
double Number::BINARY_TO_DECIMAL_MANTISSA(string n){
    long double M = 0;

    for (int i = 0; i < 23; i++){
        if (n.at(i) == '1'){
            M += pow(2,-(i+1));
        }
    }
    
    return M;
}

int Number::MAKE_EQUAL_LENGTHS(string &str1, string &str2){ 
    int len1 = str1.size(); 
    int len2 = str2.size(); 
    
    if (len1 < len2) 
    { 
        for (int i = 0 ; i < len2 - len1 ; i++) 
            str1 = '0' + str1; 
        return len2; 
    } 
    else if (len1 > len2) 
    { 
        for (int i = 0 ; i < len1 - len2 ; i++) 
            str2 = '0' + str2; 
    } 
    
    return len1; // If len1 >= len2 
} 
  
// The main function that adds two-bit sequences and returns the addition 
string Number::ADD_MANTISSA(string first, string second){ 
    string result;  // To store the sum bits 
  
    int carry = 0;  // Initialize carry 
    
    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());
  
    size_t found = 0;
    for(size_t i = 0; i < first.size(); i++){
        if(first.at(i) == '.')
            found = i;
    }

    if(found != 0){
        //remove decimal point
        first.erase(found,1);
        second.erase(found,1);
    }
    
    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());
    
    // make the lengths same before adding 
    int length = MAKE_EQUAL_LENGTHS(first, second); 
    
    // cout << "Found: " << found << endl;
    // cout << "first size: " << first.size() << endl;
    // cout << "second size: " << second.size() << endl << endl;

    // Add all bits one by one 
    for (int i = length-1 ; i >= 0 ; i--){ 
        int firstBit = first.at(i) - '0'; 
        int secondBit = second.at(i) - '0'; 
  
        // boolean expression for sum of 3 bits 
        int sum = (firstBit ^ secondBit ^ carry)+'0'; 
  
        result = (char)sum + result; 
  
        // boolean expression for 3-bit addition 
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry); 
    } 
    // If overflow, then add a leading 1 
    if (carry) 
        result = '1' + result; 
        
    // cout << "Result: " << result << endl;
  
    reverse(result.begin(), result.end());
    
    if(found != 0)
        result.insert(found, ".");
   
    reverse(result.begin(), result.end());
    
    return result; 
} 

// The main function that adds two-bit sequences and returns the addition 
string Number::SUB_MANTISSA(string first, string second){ 
    string result;  // To store the sum bits 
  
    int carry = 0;  // Initialize carry 
    
    cout << "first: " << first << endl;
    cout << "second: " << second << endl << endl;
    
    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());
  
    size_t found = 0;
    for(size_t i = 0; i < first.size(); i++){
        if(first.at(i) == '.')
            found = i;
    }

    if(found != 0){
        //remove decimal point
        first.erase(found,1);
        second.erase(found,1);
    }
    
    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());
    
    // make the lengths same before adding 
    int length = MAKE_EQUAL_LENGTHS(first, second); 
    
    // cout << "Found: " << found << endl;
    // cout << "first size: " << first.size() << endl;
    // cout << "second size: " << second.size() << endl << endl;

    for (int i = 0; i < 2; i++) {

        int index = length - i;
        char rjmc = first[index];
        char rkmc = second[index];
        
        if (rjmc == '0' && rkmc == '0') {
            // if 0 - 0 = 0
            result = '0' + result;
        } else if (rjmc == '0' && rkmc == '1') {
            // if 0 - 1 = ???

            // look for a 1 to borrow from
            for (int j = 1; j < index; j++) {
                char rjmcc = first[index - j];
                // if you find it
                if (rjmcc == '1') {
                    first[index - j] = '0';
                    //cout << "I changed index #: " << index - j << " to a '0'" << endl;
                    for (int k = 1; k <= j; k++) {
                        first[index - j + k] = '1';
                    }
                    break;
                }
            }
            result = '1' + result;


        } else if (rjmc == '1' && rkmc == '0') {
            // if 1 - 0 = 1
            result = '1' + result;

        } else if (rjmc == '1' && rkmc == '1') {
            // if 1 - 1 = 0
            result = '0' + result;

        }
    }

    int count = 0;
    for (int i = 0; i < result.length() - 1; i++) {
        count++;
        result = result + '0';
        if (result[i] == '1') {
            break;
        }

    }

    result = result.substr(0 + count, 24);
  
    reverse(result.begin(), result.end());
    
    if(found != 0)
        result.insert(found, ".");
        
    reverse(result.begin(), result.end());
    
    cout << "Mantissa Result: " << result << endl;
    cout << "Size of result after added zero: " << result.size() << endl;
    
    return result; 
} 

// The main function that adds two-bit sequences and returns the addition 
string Number::ADD_BIT_STRINGS( string first, string second ){ 
    string result;  // To store the sum bits 
  
    // make the lengths same before adding 
    int length = MAKE_EQUAL_LENGTHS(first, second); 
  
    int carry = 0;  // Initialize carry 
  
    // Add all bits one by one 
    for (int i = length-1 ; i >= 0 ; i--) 
    { 
        int firstBit = first.at(i) - '0'; 
        int secondBit = second.at(i) - '0'; 
  
        // boolean expression for sum of 3 bits 
        int sum = (firstBit ^ secondBit ^ carry)+'0'; 
  
        result = (char)sum + result; 
  
        // boolean expression for 3-bit addition 
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry); 
    } 
  
    // If overflow, then add a leading 1 
    if (carry) 
        result = '1' + result; 
  
    return result; 
} 
 
 string Number::SUB_BIT_STRINGS( string first, string second ){ 
    string result;  // To store the sum bits 
  
    // make the lengths same before adding 
    int length = MAKE_EQUAL_LENGTHS(first, second); 
    int carry = 0;  // Initialize carry 
  
    for (int i = 0; i < 24; i++) {

        int index = first.length() - i;
        char rjmc = first[index];
        char rkmc = second[index];

        if (rjmc == '0' && rkmc == '0') {
            // if 0 - 0 = 0
            result = '0' + result;
        } else if (rjmc == '0' && rkmc == '1') {
            // if 0 - 1 = ???

            // look for a 1 to borrow from
            for (int j = 1; j < index + 1; j++) {
                char rjmcc = first[index - j];

                // if you find it
                if (rjmcc == '1') {
                    first[index - j] = '0';
                    //cout << "I changed index #: " << index - j << " to a '0'" << endl;
                    for (int k = 1; k <= j; k++) {
                        first[index - j + k] = '1';
                    }
                    break;
                }
            }
            result = '1' + result;


        } else if (rjmc == '1' && rkmc == '0') {
            // if 1 - 0 = 1
            result = '1' + result;

        } else if (rjmc == '1' && rkmc == '1') {
            // if 1 - 1 = 0
            result = '0' + result;

        }
    }

    int count = 0;
    for (int i = 0; i < result.length() - 1; i++) {
        count++;
        result = result + '0';
        if (result[i] == '1') {
            break;
        }

    }
  
    // If overflow, then add a leading 1 
    if (carry) 
        result = '1' + result; 
    
    result = result.substr(0,8);
  
    return result; 
} 


 // Converts the passed in number into single precision floating point
void Number::CONVERT_TO_FLOATING_POINT(){  
    bool N = (number.at(0) == '-'); // Sets the N flag if true
    
    // If the number needed to be converted to zero then set the number to zero in floating point
    if(number == "0"){
        number = "00000000000000000000000000000000";
    } else { 
        // If the number is not zero then convert the number to floating point
        string binary = CONVERT_TO_BINARY(number);
        
        // Converts the decimal number to binary
        long double binary_double = CONVERT_TYPE(binary);
    
        // Sets the sign bit
        string S;
        if (N == true) {
            S = "1";
        }
        else {
            S = "0";
        }
        
        
        string strDecimal = binary.substr(binary.find('.') + 1);    // strDecimal is the binary after the decimal point
            
        // Find n (exponent Ex.2^n)
        string strInt = binary.substr(0,binary.find('.')); // strInt is the binary before the decimal point
        int n = 0;
        
        // Exception handling for exponent greater that 127 or less than -127
        try{
            if (strInt.length() == 0){      // For inputs with "0" as integer
                unsigned long long int count = 0;
                while(count < 1){
                    count = binary_double * pow(10,n);      // Count how many times the 1 needs to be shifted
                    n++;
                }
                n = (n * (-1)) + 1;
            }
            else {
                unsigned long long int intLength = strInt.length() - 1;     // Length of integer
                n = intLength;                       // This is the value of the exponent in the floating point (2^n)    
            }
            
            // Throws an error when the exponent goes out of range
            if(n  > 127 || n < -127) { 
                throw 70;
            }
            
        } catch(int x) {
            cout << "Error: Exponent is out of range" << endl;
            exit(1);
        }
        
        // Find E (exponent shift, +127 for single precision)
        long double numE = 127 + n;             // Needs to be turned into Binary
        
    
        string strE = CONVERT_TYPE(numE);     // Converts to String
        string E = CONVERT_TO_BINARY(strE);        // Converts to Binary
        if (E.length() < 8){
            E = "0" + E;
        }
        
        // Removing the decimal point in binary for the mantissa
        if (strInt.length() != binary.length()){    // To account for numbers without decimals
            binary.erase(binary.find('.'),1);
        }
        if (numE < 127){
            binary.erase(0,1);
        }
        
        /* Find Mantissa */
        string mantissa;
        if (numE < 127){
            n *= -1;
            mantissa = binary.substr(n-1,n+22);
        }
        else {
            mantissa = binary.substr(1,23);
        }
        
        if (mantissa.length() < 23) {                       // If mantissa is shorter than 23 bits
            for(int i = mantissa.length(); i < 23; i++){
                mantissa += '0';                            // Insert zeros at the end
            }
        }
        
        number = S + E + mantissa;
    }
}

string Number::CONVERT_TO_DECIMAL(){  // Converts the floating point input into decimal
    // Deals with passed in 0
    if(number == "00000000000000000000000000000000"){
         number = '0';
    } else {
        // Using substring to extract S, E, and the mantissa
        string S = number.substr(0,1);
        string E;
        
        // Exception handling if exponent equals all ones
        try{
            E = number.substr(1,8);
            if(E == "11111111")
                throw 69;
        } catch(int x){
            cout << "Error: Exponents are all ones" << endl;
            exit(1);
        }
        
        string mantissa = number.substr(9,23);
            
        unsigned long long int decimalExp = CONVERT_TYPE(E);            // Converts String to Doub
        decimalExp = BINARY_TO_DECIMAL_EXPONENT(decimalExp);  // need to convert the bianry exp into real
            
        long double decimalFraction = BINARY_TO_DECIMAL_MANTISSA(mantissa);   // need to convert mantissa into real
            
        unsigned long long int decimalS = CONVERT_TYPE(S);
        decimalS = BINARY_TO_DECIMAL_EXPONENT(decimalS);
                                                     //Then put into cutitaru's formula 
        /* Find n */ 
        int n = decimalExp - 127;
            
        /* Find Solution */
        long double decimal = pow(-1,decimalS) * (1+decimalFraction) * pow(2,n);    // Formula from notes
        
        number = CONVERT_TYPE(decimal);
    }
    return number; // Returning due to sementation fault
}

// Destructor for the function. Not necissary since not dealing with dynamic memory
Number::~Number(){
    for(int i = 0; i <number.size(); i++){
        number.pop_back();
    }
  }