/* Graph read from file, and represnted as adjacency list.
To implement DFS and BFS on the graph
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

// Each vertex has an integer id.

typedef vector<vector<pair<int,int>>> adjlist; // Pair: (head vertex, edge weight)

adjlist makeGraph(ifstream& ifs);
void printGraph(const adjlist& alist);
vector<int> BFS(const adjlist& alist, int source); // Return vertices in BFS order
vector<int> DFS(const adjlist& alist, int source);  // Return vertices in DFS order
void DFSHelper(const adjlist& alist, vector<int>& dfslist, vector<bool>& visited, int source);
void printQ(queue<int> qcopy);


// DFS - returns list of nodes in DFS order starting from source vertex
vector<int> DFS(const adjlist& alist, int source) {
// Your code here
    vector<int> dfslist;
    vector<bool> visited(alist.size(), false);
    visited[source] = 1;
    dfslist.push_back(source);

    DFSHelper(alist, dfslist, visited, source);

    return dfslist;
}

void DFSHelper(const adjlist& alist, vector<int>& dfslist, vector<bool>& visited, int source) {
    for(auto pair: alist[source]){
        int adjVertex = pair.first;

        if(!visited[adjVertex]){
            visited[adjVertex] = 1;
            dfslist.push_back(adjVertex);

            DFSHelper(alist, dfslist, visited, source + 1);
        }
    }
}

// BFS - returns list of nodes in BFS order starting from source vertex
vector<int> BFS(const adjlist& alist, int source) {
// Your code here
    vector<int> nodes;
    vector<bool> visited(alist.size(), false);
    visited[source] = true;

    queue<int> q;
    q.push(source);
    nodes.push_back(source);

    while(!q.empty()){
        // cout << "here" << endl;
        int tmp = q.front();
        q.pop();
        for(auto pair: alist[tmp]){
            // cout << "here" << endl;
            if(!visited[pair.first]){
                // cout << "here" << endl;
                visited[pair.first] = 1;
                q.push(pair.first);
                nodes.push_back(pair.first);
            }
        }
    }
    return nodes;
}




// Reads a csv graph from file and returns an adjacency list
adjlist makeGraph(ifstream& ifs) {
    int vh, vt, wt;
    string line;
    unordered_multimap<int, pair<int, int>> elist;
    set<int> vlist;

    while (getline(ifs, line)) {
        stringstream ss(line);
        ss >> vt;
        if (ss.peek() == ',')
            ss.ignore();
        ss >> vh;
        if (ss.peek() == ',')
            ss.ignore();
        ss >> wt;

        elist.emplace(vt, make_pair(vh, wt));
        vlist.insert(vt);
        vlist.insert(vh);
    }

    adjlist res(vlist.size()); // Preallocate vector

    for (auto& ele : elist) {
        res.at(ele.first).push_back(make_pair(ele.second.first, ele.second.second));
    }
    return res;
}

// Prints the adjacency list (only vertices, not edge weights)
void printGraph(const adjlist& alist) {
    int i = 0;
    for (auto& v : alist) {
        cout << i++ << ": ";
        for (auto& av : v) {
            cout << av.first << " ";
        }
        cout << endl;
    }
}

// Prints queue for debugging
void printQ(queue<int> qcopy) {
    while (!qcopy.empty()) {
        cout << qcopy.front();
        qcopy.pop();
    }
    cout << endl;
}
