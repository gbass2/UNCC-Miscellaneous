#include <iostream>
#include <queue>
#include <vector>
using namespace std;


// Helper function to print queue for debugging

template<typename T> void printQueue(T& q) {
    T q_copy(q);
    while(!q_copy.empty()) {
        cout << q_copy.top() << " ";
        q_copy.pop();
    }
    cout << endl;
}

// 4567 - min
// 123 - max


vector<int> findMedian(vector<int>& data) {
    priority_queue<int> max_heap; // STL Max-heap
    priority_queue<int, vector<int>, greater<int> > min_heap; // STL Min-heap

    vector<int> res;

    for(size_t i = 0; i < data.size(); i++){

        // Check if number needs to be placed in min or max heaps. If they are empty then place into min_heap
        if(min_heap.empty())
            min_heap.push(data[i]);
        else if(data[i] < min_heap.top())
            max_heap.push(data[i]);
        else
            min_heap.push(data[i]);

        // If one of the heaps is 2 or more sizes greater than the other then rebalance the heaps. The heaps should only be max of 1 size greater than the other heap
        if((min_heap.size() - max_heap.size() == 2) && !min_heap.empty()){
            max_heap.push(min_heap.top());
            min_heap.pop();
        } if((max_heap.size() - min_heap.size() == 2) && !max_heap.empty()){
            min_heap.push(max_heap.top());
            max_heap.pop();
        }

        if(!min_heap.empty()){
            // if the max is empty
            if(i == 0)
                res.push_back(min_heap.top());

            // If max_heap is greater than min_heap. Then the top of the max heap is median
            else if(max_heap.size() > min_heap.size())
                res.push_back(max_heap.top());

            // If min_heap is greater than max_heap. Then the top of the min heap is median
            else if(max_heap.size() < min_heap.size())
                res.push_back(min_heap.top());

            // If they are the same size then get both max and min and divide by 2
            else
                res.push_back((max_heap.top()+min_heap.top())/2);
        }
    }

    return res;
}
