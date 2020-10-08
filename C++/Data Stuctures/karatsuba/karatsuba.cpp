/* Karatsuba multiplication */
#include <iostream>
#include <algorithm>


using namespace std;

int numDigits(int num);
int pow10(int n);



int karatsuba(int x, int y) {
    int a, b, c , d, ac, bd;
    int nbr1 = numDigits(x);
    int nbr2 = numDigits(y);
    int n = max(nbr1, nbr2);

    // Base case
    if(x < 10 && y < 10)
        return x*y;

    // Splitting the numbers
    if(nbr1 <= 1){
        a = 0;
        b = x;
      } else {
        a = x / pow10(n/2);
        b = x % pow10(n/2);
      }

      if(nbr2 <= 1){
          c = 0;
          d = y;
      } else {
          c = y / pow10(n/2);
          d = y % pow10(n/2);
        }

        // Calculating ac and bd
        if(a < 10 && c < 10)
            ac = a*c;
        else{
            ac = karatsuba(a,c);
          }

        if(b < 10 && d < 10)
            bd = b*d;
        else
            bd = karatsuba(b,d);

        return ac * pow10(n) + (a*d + b*c) * pow10(n/2) + bd;

}

// Helper function - returns number of digits
int numDigits(int num) {
    int x = 0;

    while(num > 0){
      x++;
      num /= 10;
    }
    return x;
}

// Helper function - integer exponentiation
int pow10(int n) {
    if (n == 0)
            return 1;

    return 10*pow10(n-1);

}
