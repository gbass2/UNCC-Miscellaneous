#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <string>

using namespace std;

class Node
{
private:
   int key;
   string val;
   Node* left;
   Node* right;
   friend class BinarySearchTree;
};


class BinarySearchTree
{
public:
       BinarySearchTree();
       void insert(int key, string val); // Recursive
       void printInOrder() const; // Prints keys in-order. Recursive
       string find(int key) const; //Returns value if node is present, else return empty string. Iterative
       void maxNumber();
       int maxHelper(Node *n);
private:
        Node* root;
        void insertHelper(Node* parent, Node* new_node);
        void printInOrderHelper(Node *n) const; //Helper for recursive implemenation of printInroder()
};

#endif
