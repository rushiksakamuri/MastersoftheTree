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
class WBT {
private:
     Node* root;
     Node* rotateright(Node* node) {
        Node* neo = node->left;
        Node* sub = neo->right;
        neo->right = node;
        node->left = sub;
        node->weight = 1 + ((node->left ? node->left->weight : 0) + (node->right ? node->right->weight : 0));
        neo->weight = 1 + ((neo->left ? neo->left->weight : 0) + (neo->right ? neo->right->weight : 0));
        return neo;
    }


    Node* rotateleft(Node* node) {
        Node* neo = node->right;
        Node* sub = neo->left;
        neo->left = node;
        node->right = sub;
        node->weight = 1 + ((node->left ? node->left->weight : 0) + (node->right ? node->right->weight : 0));
        neo->weight = 1 + ((neo->left ? neo->left->weight : 0) + (neo->right ? neo->right->weight : 0));
        return neo;
    }

	Node* inserth(Node* node, const string& country, const string& deathcount) {

        if (node == nullptr) {
            return new Node(country, deathcount);
        }

        else if (deathcount < node->deathcount) {
            node->left = inserth(node->left, country, deathcount);
        }
        else if (deathcount > node->deathcount) {
            node->right = inserth(node->right, country, deathcount);
        }
	//case if it is equal
        else{
            node->countries.push_back(country);
        }
        node->weight = 1 + ((node->left ? node->left->weight : 0) + (node->right ? node->right->weight : 0));
	//directly based on opengenius and their algorithm for checking balance: https://iq.opengenus.org/weight-balanced-binary-tree/
        float balance = (float)(node->left ? node->left->weight : 0) / (float)(node->weight);

       if (balance > (1 - 0.29289) && node->left) {
            if ((float)(node->left->left ? node->left->left->weight : 0) / (float)(node->left->weight) > 0.414213) {
                return rotateright(node);
            }
            else {
                node->left = rotateleft(node->left);
                return rotateright(node);
            }
        }
        else if ((balance < 0.29289) && node->right) {
            if ((float)(node->right->left ? node->right->left->weight : 0) / (float)(node->right->weight) < 0.585786) {
                return rotateleft(node);
            }
            else {
                node->right = rotateright(node->right);
                return rotateleft(node);
            }
        }
        return node;
    }

     Node* searchdeathcounth(Node* node, const string& deathcount) {
        if (node == nullptr || node->deathcount == deathcount) {
            return node;
        }
        if (deathcount < node->deathcount) {
            return searchdeathcounth(node->left, deathcount);
        }
        else {
            return searchdeathcounth(node->right, deathcount);
        }
    }

    Node* searchcountryh(Node* node, const string& country, vector<string>& countries1) {
        if (node == nullptr) {
            return nullptr;
        }
        for (auto it: node->countries) {
           if(it == country) {
               countries1.push_back((node->deathcount));
           }
        }
        searchcountryh(node->left, country, countries1);
        searchcountryh(node->right, country, countries1);
        return node;
    }

    void inoderh(Node* node, vector<string>& order) {
        if (node != nullptr) {
            inoderh(node->left, order);
            for(const auto it: node->countries){
                order.push_back(it);
            }
            inoderh(node->right, order);
        }
    }
public:
    WBT() {
        root = nullptr;
    }

    void insertcountry(const string& country,const string& deathcount){
        root = inserth(root, country, deathcount);
    }

    void printInorder() {
        vector<string> order;
        inoderh(root, order);
        for (size_t i = 0; i < order.size(); ++i) {
            if (i != 0) {
                cout << endl;
            }
            cout << order[i];
        }
        cout << endl;
    }

    void searchdeathcount(const string& deathcount) {
        Node* node = searchdeathcounth(root, deathcount);
        for (const auto it: node->countries){
            cout << it << endl;
        }
    }

    void searchcountry(const string& country) {
        vector<string> deathcounts;
        searchcountryh(root, country, deathcounts);
        if(!deathcounts.empty()) {
            for (const auto& it : deathcounts) {
                cout << it << endl;
            }
        }
    }
};
