/* Count the number of inversions in O(n log n) time */
#include <iostream>
#include <vector>


using namespace std;


int countInv(vector<int>& numvec);

int main()
{
    int n;
    vector<int> numvec{4, 5, 6, 1, 2, 3};
    n = countInv(numvec);
    cout << "Number of inversions " << n << endl; // Should be 9

    numvec = {1, 2, 3, 4, 5, 6};
    n = countInv(numvec);
    cout << "Number of inversions " << n << endl; // Should be 0

    numvec = {6, 5, 4, 3, 2, 1};
    n = countInv(numvec);
    cout << "Number of inversions " << n << endl;  // Should be 15

    numvec = {0, 0, 0, 0, 0, 0};
    n = countInv(numvec);
    cout << "Number of inversions " << n << endl;;  // Should be 0
}
