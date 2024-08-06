#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class RedBlackTree {
private:
    // Struct representing a tree node
    struct TreeNode {
        string country;
        string deathCount;
        TreeNode *left, *right, *parent;
        bool isRed;

        // Constructor to initialize a new node
        TreeNode(const string& c, string d) {
            country = c;
            deathCount = d;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            isRed = true; // New nodes are initially red
        }
    };

    TreeNode *root = nullptr; // Root of the tree

    // Private helper functions
    void leftRotate(TreeNode *x);
    void rightRotate(TreeNode *x);
    void balanceInsert(TreeNode *k);
    void searchTreeHelper(TreeNode* node, const string& key);
    void inOrderHelper(TreeNode *node);
    void searchByDeathCountHelper(TreeNode* node, const string& deathCount);

public:
    ~RedBlackTree(); // Destructor to clean up the tree
    void insert(const string& country, string deathCount); // Insert a new node
    void search(const string& country); // Search for a node by country
    void searchByDeathCount(const string& deathCount); // Search for a node by death count
    void printTree(); // Print the tree in-order

private:
    void deleteTree(TreeNode* node); // Helper to delete the tree
};

// Destructor to clean up the tree
RedBlackTree::~RedBlackTree() {
    deleteTree(root);
}

// Helper function to delete the tree
void RedBlackTree::deleteTree(TreeNode* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}


// Helper function to search the tree by country
void RedBlackTree::searchTreeHelper(TreeNode* rootHelp, const string& key) {
    if (rootHelp == nullptr) {
        cout << "Country not found!" << endl;
    } else if (key == rootHelp->country) {
        cout << "Country: " << rootHelp->country << ", Death Count: " << rootHelp->deathCount << endl;
    } else if (key < rootHelp->country) {
        searchTreeHelper(rootHelp->left, key);
    } else {
        searchTreeHelper(rootHelp->right, key);
    }
}

// Function to search for a node by country
void RedBlackTree::search(const string& country) {
    searchTreeHelper(this->root, country);
}

// Helper function to search the tree by death count
void RedBlackTree::searchByDeathCountHelper(TreeNode* node, const string& deathCount) {
    if (node == nullptr) return;
    searchByDeathCountHelper(node->left, deathCount);
    if (node->deathCount == deathCount) {
        cout << "Country: " << node->country << ", Death Count: " << node->deathCount << endl;
    }
    searchByDeathCountHelper(node->right, deathCount);
}

// Function to search for a node by death count
void RedBlackTree::searchByDeathCount(const string& deathCount) {
    searchByDeathCountHelper(this->root, deathCount);
}

// Function to print the tree in-order
void RedBlackTree::printTree() {
    inOrderHelper(this->root);
}

// Helper function to perform in-order traversal
void RedBlackTree::inOrderHelper(TreeNode* node) {
    if (node == nullptr) return;
    inOrderHelper(node->left);
    cout << "Country: " << node->country << ", Death Count: " << node->deathCount << endl;
    inOrderHelper(node->right);
}