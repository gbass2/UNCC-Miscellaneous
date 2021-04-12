/* Given: Find median of a data stream using heaps */

#include <iostream>
#include <vector>
using namespace std;

const int MAX_VAL = 100;
const int NUM_ELEM = 15;


vector<int> findMedian(vector<int>& nums);


int main() {
    vector<int> data_stream = {5, 42, 29, 85, 95, 99, 2, 15};
    // i-th element of median_stream is median of first i elements of input 
    vector<int> median_stream = findMedian(data_stream) ;
    for (auto ele: median_stream) {
        cout << ele << " "; // Answer should be - 5 23 29 35 42 63 42 35 
    }
    cout << endl;
}

