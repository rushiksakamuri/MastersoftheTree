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

// Function to perform left rotation
void RedBlackTree::leftRotate(TreeNode *x) {
    TreeNode *y = x->right; // y is x's right child
    x->right = y->left; // Turn y's left subtree into x's right subtree
    if (y->left) y->left->parent = x; // Update parent pointer of y's left child
    y->parent = x->parent; // Link y's parent to x's parent

    if (!x->parent) root = y; // x was root, now y is root
    else if (x == x->parent->left) x->parent->left = y; // x was left child
    else x->parent->right = y; // x was right child

    y->left = x; // Put x on y's left
    x->parent = y; // Update x's parent pointer
}

// Function to perform right rotation
void RedBlackTree::rightRotate(TreeNode *x) {
    TreeNode *y = x->left; // y is x's left child
    x->left = y->right; // Turn y's right subtree into x's left subtree
    if (y->right) y->right->parent = x; // Update parent pointer of y's right child
    y->parent = x->parent; // Link y's parent to x's parent

    if (!x->parent) root = y; // x was root, now y is root
    else if (x == x->parent->right) x->parent->right = y; // x was right child
    else x->parent->left = y; // x was left child

    y->right = x; // Put x on y's right
    x->parent = y; // Update x's parent pointer
}

// Function to balance the tree after insertion
void RedBlackTree::balanceInsert(TreeNode *k) {
    while (k->parent && k->parent->isRed) {
        TreeNode *gp = k->parent->parent; // Grandparent
        TreeNode *u = (k->parent == gp->right) ? gp->left : gp->right; // Uncle

        if (u && u->isRed) {
            k->parent->isRed = u->isRed = false;
            gp->isRed = true;
            k = gp;
        } else {
            if (k->parent == gp->right) {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->isRed = false;
                gp->isRed = true;
                leftRotate(gp);
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->isRed = false;
                gp->isRed = true;
                rightRotate(gp);
            }
        }
    }
    root->isRed = false;
}

// Function to insert a new node into the tree
void RedBlackTree::insert(const string& country, string deathCount) {
    TreeNode *node = new TreeNode(country, deathCount);
    TreeNode *y = nullptr;
    TreeNode *x = root;

    while (x != nullptr) {
        y = x;
        if (node->country < x->country) x = x->left;
        else x = x->right;
    }

    node->parent = y;
    if (y == nullptr) root = node;
    else if (node->country < y->country) y->left = node;
    else y->right = node;

    if (node->parent == nullptr) {
        node->isRed = false;
        return;
    }

    if (node->parent->parent == nullptr) return;
    balanceInsert(node);
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

int main() {
    RedBlackTree rbt;
    WBT wbt;	
    ifstream file("covid.csv");
	
    // Check if the file opened successfully
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    getline(file, line);  // Skip the header line
    map<string, string> countryDeathCounts;

    // Read data from the CSV file
    while (getline(file, line)) {
        stringstream ss(line);
        string country;
        string deathCount;
        string temp;

        // Extract country and death count from the line
	//col being extracted is values derived from col e and f(which is a total of 100000+ dataset) which should fufill the requirement of using 100,000 dataset within the project
        for (int i = 0; i < 10; ++i) {
            getline(ss, temp, ',');
            if (i == 8) {
                country = temp;
            }
            else if (i == 9) {
                deathCount = temp;
            }
        }
        countryDeathCounts[country] = deathCount;
    }

    file.close();
	// Insert data into the Red-Black Tree
    for (auto pair: countryDeathCounts) {
        rbt.insert(pair.first, pair.second);
	wbt.insertcountry(pair.first,pair.second);
    }
    cout << "Welcome to Covid tree!";
    int option;
    while (option != 7) {
        cout << "Select an option!" << endl;
        cout << "1: Weight balance tree search by country" << endl;
        cout << "2: Weight balance tree search by deathcount" << endl;
        cout << "3: Weight balance tree print in order" << endl;
        cout << "4: Red-Black tree search by country" << endl;
        cout << "5: Red-Black tree search by deathcount" << endl;
        cout << "6: Red-Black tree print in order" << endl;
        cout << "7: End the program" << endl;

        cin >> option;
        if (option == 1) {
            cout << "input a country:" << endl;
            string country;
            cin >> country;
            wbt.searchcountry(country);
        }
        else if (option == 2){
            cout << "input deathcount:" << endl;
            string deathcount;
            cin >> deathcount;
            wbt.searchdeathcount(deathcount);
        }
        else if (option == 3) {
            wbt.printInorder();
        }
        else if (option == 4) {
            cout << "input a country!" << endl;
            string country;
            cin >> country;
            rbt.search(country);
        }
        else if (option == 5) {
            cout << "input deathcount!" << endl;
            string deathcount;
            cin >> deathcount;
            rbt.searchByDeathCount(deathcount);
        }
        else if (option == 6) {
            rbt.printTree();
        }
        else if (option == 7) {
            cout << "Program ended" << endl;
            break;
        }
        else {
            cout << "Error! pick anther option!" << endl;
        }
    }
    return 0;
}

