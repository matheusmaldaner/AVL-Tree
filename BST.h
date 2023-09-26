#include <iostream>
#include <queue>
#include <vector>

class BST
{
public:


    class TreeNode {
    public:
        
        // basic Node variables
        std::string id;
        std::string name;
        int height = 1;

        // left and right Node pointers
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;

        // default constructor
        TreeNode() {
            name = "NoName";
            id = "00000000";
        }
            
        TreeNode(std::string name_, std::string id_) {
            name = name_;
            id = id_;
        }
    };

    // root node
    TreeNode* root;

    // insert function
    TreeNode* insert(TreeNode* n, std::string name, std::string id_);

    // seaching functions
    void searchID(TreeNode* n, std::string id_, bool& toggle, std::string &name);
    void searchName(TreeNode* n, std::string name, std::vector<std::string> &container);

    // traversal functions
    void printInorder(TreeNode* n, bool& comma);
    void inorderIdVector(TreeNode* n, std::vector<std::string>& inorderStorage);
    void printPreorder(TreeNode* n, bool& comma);
    void printPostorder(TreeNode* n, bool& comma);
   
    // rotations
    TreeNode* rotateLeft(TreeNode* n);
    TreeNode* rotateRight(TreeNode* n);
    TreeNode* rotateLeftRight(TreeNode* n);
    TreeNode* rotateRightLeft(TreeNode* n);
    
    // removal functions
    void removeID(TreeNode* n, std::string id_);
    TreeNode* removeAssist(TreeNode* n, std::string id_, bool& removed);
    void removeInorder(TreeNode* n, int number);
    
    // additional functions
    TreeNode* leftIterator(TreeNode* n);
    int checkHeight(TreeNode* n);
    int checkBalance(TreeNode* n);
    void inorderHeight(TreeNode* n);
    int printLevelCount(TreeNode* n, int& max, int& level);

};


    
// inserts node with name and id
BST::TreeNode* BST::insert(TreeNode* node, std::string name_, std::string id_) {

    
    if (node == nullptr) {
        node = new TreeNode(name_, id_);
        return node;
    }
    if (node->id < id_) {
        node->right = insert(node->right, name_, id_);
    }
    else {
        node->left = insert(node->left, name_, id_);
    }

    node->height = checkHeight(node);
    int balance = checkBalance(node);

    if (balance == 2) {
        // performs left right rotation
        if (checkBalance(node->left) == -1) {
            node = rotateLeftRight(node);
        }
        // performs right rotation
        else if (checkBalance(node->left) == 1) {
            node = rotateRight(node);
        }
    }
    else if (balance == -2) {
        // performs left rotation
        if (checkBalance(node->right) == -1) {
            node = rotateLeft(node);            
        }
        // performs right left rotation
        else if (checkBalance(node->right) == 1) {
            node = rotateRightLeft(node);
        }
    }
    return node;
}

void BST::removeID(TreeNode* n, std::string id_) {
    bool removed = false;
    std::string searched;
    removeAssist(n, id_, removed);

    if (!removed) {
        std::cout << "unsuccessful" << std::endl;
    }
    else {
        std::cout << "successful" << std::endl;
    }
}

// assist function for the removeID function
BST::TreeNode* BST::removeAssist(TreeNode* n, std::string id_, bool& removed) {
    if (n == nullptr) {
        return nullptr;
    }

    if (id_ < n->id) {
        n->left = removeAssist(n->left, id_, removed); 
    }
    else if (id_ > n->id) {
        n->right = removeAssist(n->right, id_, removed);
    }
    else {
        removed = true;
        // one or zero children
        if (n->left == nullptr || n->right == nullptr) {
            // has right child
            if (n->left == nullptr && n->right != nullptr) {
                TreeNode* temp = n->right;
                delete n;
                return temp;

            }
            // has left child
            else if (n->left != nullptr && n->right == nullptr) {
                TreeNode* temp = n->left;
                delete n;
                return temp;
            }
            // 0 children
            else {
                delete n;
                return nullptr;
            }
        }
        // two children
        else {
            TreeNode* temp = leftIterator(n->right);
            n->id = temp->id;
            n->name = temp->name;
            n->right = removeAssist(n->right, temp->id, removed);
            return n;

        }
    }
    return n;
}

// searches for an id, passing a boolean parameter to see if id has been found
void BST::searchID(TreeNode* n, std::string id_, bool &toggle, std::string &name) {
    
    if (n == nullptr) {
        return;
    }

    if (n->id == id_) {
        toggle = true;
        name = n->name;
    }

    if (n->left != nullptr) {
        searchID(n->left, id_, toggle, name);
    }
    if (n->right != nullptr) {
        searchID(n->right, id_, toggle, name);
    }
}

// searches a name and stores ids of found matches in a vector container
void BST::searchName(TreeNode* n, std::string name_, std::vector<std::string> &container) {
    if (n == nullptr) {
        return;
    }

    if (n->name == name_) {
        container.push_back(n->id);
    }

    if (n->left != nullptr) {
        searchName(n->left, name_, container);
    }
    if (n->right != nullptr) {
        searchName(n->right, name_, container);
    }
}

// inorder traversal helper function used on removeInorder
void BST::inorderIdVector(TreeNode* n, std::vector<std::string> &inorder) {
    if (n == nullptr) {
        return;
    }
    if (n->left != nullptr) {
        inorderIdVector(n->left, inorder);
    }
    inorder.push_back(n->id);

    if (n->right != nullptr) {
        inorderIdVector(n->right, inorder);
    }
}


/////////////////////////////////////////////
//            print functions              //
///////////////////////////////////////////// 


// prints name elements separated by commas in inorder style
void BST::printInorder(TreeNode* n, bool& comma) {

    if (n == nullptr) {
        return;
    }
    if (n->left != nullptr) {
        printInorder(n->left, comma);
    }

    if (comma) {
        std::cout << ", ";
    }

    std::cout << n->name;
    comma = true;

    if (n->right != nullptr) {
        printInorder(n->right, comma);
    }
}

// prints name elements separated by commas in postorder style
void BST::printPostorder(TreeNode* n, bool& comma) {
    if (n == nullptr) {
        return;
    }
    if (n->left != nullptr) {
        printPostorder(n->left, comma);
    }
    if (n->right != nullptr) {
        printPostorder(n->right, comma);
    }
    if (comma) {
        std::cout << ", ";
    }
    std::cout << n->name;
    comma = true;

}

// prints name elements separated by commas in preorder style
void BST::printPreorder(TreeNode* n, bool& comma) {
    if (n == nullptr) {
        return;
    }
   
    if (comma) {
        std::cout << ", ";
    }

    std::cout << n->name;
    comma = true;

    if (n->left != nullptr) {
        printPreorder(n->left, comma);
    }

    if (n->right != nullptr) {
        printPreorder(n->right, comma);
    }
}


/////////////////////////////////////////////
//            remove & level               //
///////////////////////////////////////////// 


void BST::inorderHeight(TreeNode* n) {
    if (n == nullptr) {
        return;
    }
    if (n->left != nullptr) {
        inorderHeight(n->left);
    }
    std::cout << n->height << " ";

    if (n->right != nullptr) {
        inorderHeight(n->right);
    }
}

void BST::removeInorder(TreeNode* n, int number) {
    std::vector<std::string> inorderVec;
    inorderIdVector(n, inorderVec);
    
    removeID(n, inorderVec.at(number));    
}

// prints number of levels in the avl tree
int BST::printLevelCount(TreeNode* n, int& max, int& level) {
    level++;
    if (level >= max) {
        max = level;
    }

    if (n->left != nullptr) {
        printLevelCount(n->left, max, level);
    }

    if (n->right != nullptr) {
        printLevelCount(n->right, max, level);
    }

    level--;
    
    return max;
}


/////////////////////////////////////////////
//               rotations                 //
///////////////////////////////////////////// 


// function for fixing right imbalance on avl tree
BST::TreeNode* BST::rotateLeft(TreeNode* n) {
    TreeNode* grandchild = n->right->left;
    TreeNode* child = n->right;

    child->left = n;
    n->right = grandchild;

    return child;
}

// function for fixing left imbalance on avl tree
BST::TreeNode* BST::rotateRight(TreeNode* n) {
    TreeNode* grandchild = n->left->right;
    TreeNode* child = n->left;

    child->right = n;
    n->left = grandchild;

    return child;
}

// function for fixing left right imbalance on avl tree
BST::TreeNode* BST::rotateLeftRight(TreeNode* n) {
    TreeNode* child = n->left;
    n = rotateLeft(child);
    n = rotateRight(n);
    return n;
}

// function for fixing right left imbalance on avl tree
BST::TreeNode* BST::rotateRightLeft(TreeNode* n) {
    TreeNode* child = n->right;
    n = rotateRight(child);
    n = rotateLeft(n);
    return n;
}


/////////////////////////////////////////////
//            extra functions              //
///////////////////////////////////////////// 


// gets the leftmost node of a given node
BST::TreeNode* BST::leftIterator(TreeNode* n) {
    if (n->left == nullptr) {
        return n;
    }
    else {
        return leftIterator(n->left);
    }
}

// checks the balance of a given node
int BST::checkBalance(TreeNode* n) {
    if (n == nullptr) {
        return 0;
    }
    else {
        return (checkHeight(n->left) - checkHeight(n->right));
    }
}

// checks the height of a node as well as its children's
int BST::checkHeight(TreeNode* n) {

    if (n == nullptr) {
        return 0;
    }
    else {
        return std::max(checkHeight(n->left), checkHeight(n->right)) + 1;
    }
}