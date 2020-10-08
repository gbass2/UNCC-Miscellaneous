// Set operations

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Set intersection - words common to both inputs
vector<string> intersection(vector<string> s1, vector<string> s2) {
	vector<string> result;

	// Looping through both vectors and comparing them one by one. If one element is equal to the other vectors element, then push back to result and return
	for(size_t i = 0; i < s1.size(); i++){
		for(size_t j = 0; j < s2.size(); j++){

			if(s1.at(i) == s2.at(j)){
				result.push_back(s1.at(i));
			}
		}
	}

	return result;
}


// Do not modify
int main() {
	vector<string> s1{"dream", "peace", "love", "strong"};
	vector<string> s2{"strong", "hope", "believe"};
	vector<string> s3{"fear", "defeat", "bad", "fail"};

	// Test1
	vector<string> want1{"strong"};
	vector<string> got1 = intersection(s1, s2);
	if (want1.size() != got1.size()) {
		cout << "Test1 intersection failed" << endl;
		return -1;
	}
	for (int i = 0; i < want1.size(); i++) {
		if (want1[i] != got1[i]) {
			cout << "Test1 intersection failed" << endl;
			return -1;
		}
	}

	cout << "Test1 passed" << endl;

	// Test2
	vector<string> want2{};
	vector<string> got2 = intersection(s1, s3);
	if (want2.size() != got2.size()) {
		cout << "Test2 intersection failed" << endl;
		return -1;
	}
	for (int i = 0; i < want2.size(); i++) {
		if (want1[i] != got2[i]) {
			cout << "Test2 intersection failed" << endl;
			return -1;
		}
	}
	cout << "Test2 passed" << endl;

}
