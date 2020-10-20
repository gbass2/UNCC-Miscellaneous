// Count inversions - homework
// Based off of mergesort
#include <vector>
#include <algorithm> // For copy
#include <iostream>

using namespace std;


int mergeInv(vector<int>& nums, vector<int> &left, vector<int> &right) {
// You will need this helper function that calculates the inversion while merging
// Your code here
    int count = 0;
    int i = 0, j = 0, k = 0;
	while ((j < left.size()) && (k < right.size())) {
		if (left[j] <= right[k]) {
			nums[i] = left[j];
			i++;
			j++;
		} else {
			nums[i] = right[k];

			k++;
            count += left.size() - j;
        }
	}

	while(j < left.size())  { // Remaining elements of left
		nums[i] = left[j];
		i++;
		j++;
	}
	while(k < right.size()) {
		nums[i] = right[k];
		i++;
		k++;
	}

    return count;
}

int countInv(vector<int>&nums) {
// Your code here
    int count = 0;
    if (nums.size() > 1) {
        int mid = nums.size()/2;
        vector<int> left(mid);
        vector<int> right(nums.size()-mid);
        copy(nums.begin(), nums.begin() + mid, left.begin());
        copy(nums.begin() + mid, nums.end(), right.begin());

        count += countInv(left);
        count += countInv(right);

        count += mergeInv(nums, left, right);
        return count;

    // Base case if size = 1
    } else
        return 0;
}
