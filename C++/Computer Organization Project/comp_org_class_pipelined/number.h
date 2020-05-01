#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <vector>

using namespace std;

// Used for floating point conversion
class Number{
  private:
  // Class member decleration
  string number;
  
  public:
  // Constructers
  Number();
  Number(string);
  
  // Deconstructor
  ~Number();
  
  // Member function prototypes
  string GET_NUMBER() const;
  void SET_NUMBER(string);
  string CONVERT_TO_BINARY(string);
  double BINARY_TO_DECIMAL_MANTISSA(string);
  int BINARY_TO_DECIMAL_EXPONENT(unsigned long long int);
  int MAKE_EQUAL_LENGTHS(string &, string &);
  string ADD_BIT_STRINGS(string, string);
  string SUB_BIT_STRINGS(string, string);
  string ADD_MANTISSA(string, string);
  string SUB_MANTISSA(string, string);
  void CONVERT_TO_FLOATING_POINT();
  string CONVERT_TO_DECIMAL();
  double CONVERT_TYPE(string);
  string CONVERT_TYPE(long double);
  
};

#endif