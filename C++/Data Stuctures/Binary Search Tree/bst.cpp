#include <iostream>
#include "bst.h"
#include <cmath>

using namespace std;

BinarySearchTree::BinarySearchTree()
{
   root = nullptr;
}

void BinarySearchTree::insert(int key, string val)
{
   Node* new_node = new Node;
   new_node->key = key;
   new_node->val = val;
   new_node->left = nullptr;
   new_node->right = nullptr;
   if (root == nullptr) {
      root = new_node;
  } else {
      insertHelper(root, new_node);
   }
}

void BinarySearchTree::insertHelper(Node* parent, Node* new_node)
{
   if (new_node->key < parent->key) {
      if (parent->left == nullptr) {
         parent->left = new_node;
      }
      else {
         insertHelper(parent->left, new_node); }
   }
   else if (new_node->key > parent->key) {
      if (parent->right == nullptr) {
         parent->right = new_node;
      }
      else {
         insertHelper(parent->right, new_node);
      }
   }
}

string BinarySearchTree::find(int key) const {
// Your code here....Iterative

    Node* current = root;
    Node* right = root->right;
    Node* left = root->left;

    while(current){
        // Checking to see if the key is equal to the root's key
        if(current->key == key)
            return current->val;

        // If the key does not exist in the bst then break and return
        else if ((current->key != key && !right) || (current->key != key && !left))
            break;

        // If the key is less than the root's key then tranverse the left
        else if(root->key < key){
            left = current;
            current = right;
            right = current->right;

        // If the key is less than the root's key then tranverse the right
        }else if(root->key > key){
            right = current;
            current = left;
            left = current->left;
        }
    }
    return "";
}

void BinarySearchTree::printInOrder() const {
	if (root == nullptr) {
		cout << endl;
	}
	printInOrderHelper(root);
	cout << endl;

}

void BinarySearchTree::maxNumber(){
    maxHelper(root);
}

int BinarySearchTree::maxHelper(Node *n){
    if(!root)
        return 0;
        
    int leftMax = maxHelper(n->left);
    int rightMax = maxHelper(n->right);

    if((stoi(n->val) > leftMax) && (stoi(n->val) > rightMax))
        return stoi(n->val);
    else if((leftMax > rightMax) && (leftMax > stoi(n->val)))
        return leftMax;
    else
        return rightMax;
}

void BinarySearchTree::printInOrderHelper(Node* n) const {
// Your code here....Recursive
    if(!n)
        return;

    // Accessing the left child
    if(n->left){
        printInOrderHelper(n->left);
    }
    // printing the key
    cout << n->key << endl;

    // accessing the right child
    if(n->right != nullptr){
        printInOrderHelper(n->right);
    }
}
