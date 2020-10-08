/* Karatsuba multiplication */
#include <iostream>


using namespace std;

int karatsuba(int x, int y);


int main() {
    cout << "7*6 = " << karatsuba(7, 6) << endl;
    cout << "15*15 = " << karatsuba(15, 15) << endl;
    cout << "6*13 = " << karatsuba(6, 13) << endl;
    cout << "51*49 = " << karatsuba(51, 49) << endl;
    cout << "111*111 = " << karatsuba(111, 111) << endl;
    cout << "5678*1234 = " << karatsuba(5678, 1234) << endl;
    cout << "12345678*1 = " << karatsuba(12345678, 1) << endl;
    cout << "12345678*0 = " << karatsuba(12345678, 0) << endl;
    return 0;
}