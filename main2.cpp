#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

enum COLOR  {RED = 0, BLACK =1};

struct Node {
    Node* parent = nullptr;
    Node* left_child = nullptr;
    Node* right_child = nullptr;
    COLOR color = BLACK;
    int value = -1;
};

class RedBlackTree
{
    public:
        RedBlackTree();
        ~RedBlackTree();
        void print();


        bool setChild(Node* par, int mode, Node* child);
        bool replaceChild(Node* par, Node* child, Node* new_child);
        void rotateLeft(Node* n1);
        void rotateRight(Node* n1);
        void insert(Node* n1);
        void balanceTree(Node* n1);
        Node* getGrandparent(Node* n1);
        Node* getUncle(Node* n1);

        void remove(int value);
        void removeNode(Node* n1);
        Node* getPrevious(Node* n1);
        Node* getSibling(Node* n1);
        bool notRedOrNull(Node* n1);
        bool nullOrBlack(Node* n1);
        bool bothChildrenBlack(Node* n1);
        void preRemoval(Node* n1);

        bool case1(Node* n1);
        bool case2(Node* n1, Node* sibling);
        bool case3(Node* n1, Node* sibling);
        bool case4(Node* n1, Node* sibling);
        bool case5(Node* n1, Node* sibling);
        bool case6(Node* n1, Node* sibling);

        void bstRemove(int value);
        
        int getSize() {return size;};

    private:
        void bstInsert(Node* n1);
        void printHelper(Node* n1, int spacer, int mode);

        Node* root;
        int size;

        //  store nodes in vector since its easier to delete
        std::vector<Node*> node_storage;
};

int main() {
    const int SIZE = 22000;
    srand(time(NULL));
    RedBlackTree tree;
    
    std::vector<Node*> test1;
    
    int temp;
    for (int i = 0; i < SIZE; i++) {
        temp = rand() % 10000;
        Node* n1 = new Node;
        n1->value = temp;
        test1.push_back(n1);
    }
    
    clock_t start = clock();
    
    for (int i = 0; i < test1.size(); i++) {
        tree.insert(test1[i]);
    }
    
    
    std::cout << std::setprecision(5);

    std::cout << "Time taken to insert " << SIZE << " items : " 
              << (double)(clock() - start)/ CLOCKS_PER_SEC 
              << " seconds\n";
              
    start = clock();
    
    for (int i = 0; i < test1.size(); i++) {
        tree.remove(test1[i]->value);
    }
    
    std::cout << "Time taken to delete " << SIZE << " items: "
              << (double)(clock() - start) / CLOCKS_PER_SEC
              << " seconds\n";
    
    std::cout << "size of tree: " << tree.getSize() << "\n";
    
    //  Clean up
    for (std::vector<Node*>::iterator i = test1.begin(); i != test1.end(); ++i)
        delete *i;

    return 0;
}



RedBlackTree::RedBlackTree() {
    root = nullptr;
    //root = new Node;
    //node_storage.push_back(root);
    size = 0;
}

RedBlackTree::~RedBlackTree() {
/*
    for (std::vector<Node*>::iterator i = node_storage.begin(); i != node_storage.end(); ++i) {
        delete *i;
    }*/
}


void RedBlackTree::print() {
    if (root == nullptr) {
        std::cout << "EMPTY\n";
    } else {
        printHelper(root, 32, 0);
    }
}
//  mode 0-> root node, mode 1 ->right node, mode 2 -> left node
void RedBlackTree::printHelper(Node* n1, int spacer, int mode) {
    if (n1 == nullptr)
        return;
    else {
        if (mode == 0) {
            std::cout << std::setfill(' ') << std::setw(spacer);
        } else if (mode == 1) {
            std::cout << std::setfill(' ') << std::setw(spacer - spacer / 2);
        } else if (mode == 2) {
            std::cout << std::setfill(' ') << std::setw(spacer + spacer / 2);
        }

        if (n1->color == RED) {
            std::cout << "(RED ";
        } else {
            std::cout << "(BLACK ";
        }
        std::cout << " " << n1->value << ") ";
        //  recursively print each node
        std::cout << "\n";
        if (n1 == root) {
            spacer *= 2;
        }
        printHelper(n1->left_child, spacer / 2, 1);
        std::cout << " ";
        printHelper(n1->right_child, spacer /2, 2);
    }
}

//  mode 0 = left, mode 1 = right
bool RedBlackTree::setChild(Node* par, int mode, Node* child) {
    if (mode != 1 && mode != 2) {
        return false;
    }
    if (mode == 0) {
        par->left_child = child;
    } else {
        par->right_child = child;
    }
    if (child != nullptr) {
        child->parent = par;
    }
    return true;
}

bool RedBlackTree::replaceChild(Node* par, Node* child, Node* new_child) {
    if (par->left_child == child) {
        return setChild(par, 0, new_child);
    } else if (par->right_child == child) {
        return setChild(par, 1, new_child);
    }
    return false;
}

void RedBlackTree::rotateLeft(Node* n1) {
    Node* temp = n1->right_child->left_child;
    if (n1->parent != nullptr) {
        replaceChild(n1->parent, n1, n1->right_child);
    } else {
        root = n1->right_child;
        root->parent = nullptr;
    }
    setChild(n1->right_child, 0, n1);
    setChild(n1, 1, temp);
}

void RedBlackTree::rotateRight(Node* n1) {
    Node* temp = n1->left_child->right_child;
    if (n1->parent != nullptr) {
        replaceChild(n1->parent, n1, n1->left_child);
    } else {
        root = n1->left_child;
        root->parent = nullptr;
    }
    setChild(n1->left_child, 1, n1);
    setChild(n1, 0, temp);
}

void RedBlackTree::bstInsert(Node* n1) {
    //  push into vector for search
    node_storage.push_back(n1);

    if (root == nullptr) {
        root = n1;
    } else {
        Node* current = root;
        while (current != nullptr) {
            if (n1->value < current->value) {
                if (current->left_child == nullptr) {
                    current->left_child = n1;
                    current = nullptr;
                } else {
                    current = current->left_child;
                }
            } else {
                if (current->right_child == nullptr) {
                    current->right_child = n1;
                    current = nullptr;
                } else {
                    current = current->right_child;
                }
            }

        }
    }
}

void RedBlackTree::insert(Node* n1) {
    size++;
    //std::cout <<"insert\n";
    bstInsert(n1);
    n1->color = RED;
    balanceTree(n1);
}

Node* RedBlackTree::getGrandparent(Node* n1) {
    if (n1->parent == nullptr) {
        return nullptr;
    }
    return n1->parent->parent;
}

Node* RedBlackTree::getUncle(Node* n1) {
    Node* grandparent = nullptr;
    if (n1->parent != nullptr) {
        grandparent = n1->parent->parent;
    }
    if (grandparent == nullptr) {
        return nullptr;
    }
    if (grandparent->left_child == n1->parent) {
        return grandparent->right_child;
    } else {
        return grandparent->left_child;
    }
}


void RedBlackTree::balanceTree(Node* n1) {
    //  std::cout << "start\n";
    if (n1->parent == nullptr) {
        n1->color = BLACK;
        return;
    }
    //  std::cout << "past first statement\n";
    if (n1->parent->color == BLACK) {
        //return;
    }
    //  std::cout << "HERE\n";
    Node* parent = n1->parent;
    Node* grandparent = getGrandparent(n1);
    Node* uncle = getUncle(n1);
    if (uncle != nullptr && uncle->color == RED) {
        parent->color = RED; //
        uncle->color = RED;
        grandparent->color = RED;
        balanceTree(grandparent);
        return;
    }
    if (n1 == parent->right_child && parent == grandparent->left_child) {
        rotateLeft(parent);
        n1 = parent;
        parent = n1->parent;
    } else if (n1 == parent->left_child && parent == grandparent->right_child) {
        rotateRight(n1);
        n1 = parent;
        parent = n1->parent;
    }
    parent->color = BLACK;
    grandparent->color = RED;
    if (n1 == parent->left_child) {
        rotateRight(grandparent);
    } else {
        rotateLeft(grandparent);
    }
}

void RedBlackTree::remove(int v) {
    size--;
    Node* n1 = nullptr;
    //  std::cout << "a\n";
    for (int i = 0; i < node_storage.size(); i++) {
        if (node_storage[i]->value == v) {
            n1 = node_storage[i];
        }
    }
    //  value was found
    if (n1 != nullptr) {
        removeNode(n1);
    }
    //  value was not found;
    return;
}

void RedBlackTree::removeNode(Node* n1) {
    if (n1->left_child != nullptr && n1->right_child != nullptr) {
        Node* previous_node = getPrevious(n1);
        int previous_value = previous_node->value;
        removeNode(previous_node);
        n1->value = previous_value;
        return;
    }
    if (n1->color == BLACK) {
        preRemoval(n1);
    }
    //  std::cout << "b\n";
    bstRemove(n1->value);
}

Node* RedBlackTree::getPrevious(Node* n1) {
    Node* temp = n1->left_child;
    while (n1->right_child != nullptr) {
        n1 = n1->right_child;
    }
    return temp;
}



Node* RedBlackTree::getSibling(Node* n1) {
    if (n1->parent != nullptr) {
        if (n1 == n1->parent->left_child) {
            return n1->parent->left_child;
        }
        return n1->parent->left_child;
    }
    return nullptr;
}

bool RedBlackTree::notRedOrNull(Node* n1) {
    if (n1 == nullptr) {
        return false;
    }
    if (n1->color == RED) {
        return false;
    } else {
        return true;
    }
}

bool RedBlackTree::nullOrBlack(Node* n1) {
    if (n1 == nullptr) {
        return true;
    }
    if (n1->color == BLACK)
        return true;
    else
        return false;
}

bool RedBlackTree::bothChildrenBlack(Node* n1) {
    if (n1->left_child != nullptr && n1->left_child->color == RED) {
        return false;
    }
    if (n1->right_child != nullptr && n1->right_child->color == RED) {
        return false;
    }
    return true;
}


void RedBlackTree::preRemoval(Node* n1) {
    if (case1(n1)) {
        return;
    }
    Node* sibling = getSibling(n1);
    if (case2(n1, sibling)) {
        sibling = getSibling(n1);
    }
    if (case3(n1, sibling)) {
        return;
    }
    if (case4(n1, sibling)) {
        return;
    }
    if (case5(n1, sibling)) {
        sibling = getSibling(n1);
    }
    if (case6(n1, sibling)) {
        sibling = getSibling(n1);
    }

    sibling->color = n1->parent->color;
    n1->parent->color = BLACK;
    if (n1 == n1->parent->left_child) {
        sibling->right_child->color = BLACK;
        rotateLeft(n1->parent);
    } else {
        sibling->left_child->color = BLACK;
        rotateRight(n1->parent);
    }
}

bool RedBlackTree::case1(Node* n1) {
    if (n1->color == RED || n1->parent == nullptr) {
        return true;
    } else {
        return false;
    }
}
bool RedBlackTree::case2(Node* n1, Node* sibling) {
    if (sibling->color == RED) {
        n1->parent->color = RED;
        sibling->color = BLACK;
        if (n1 == n1->parent->left_child) {
            rotateLeft(n1->parent);
        } else {
            rotateRight(n1->parent);
        }
        return true;
    }
    return false;
}

bool RedBlackTree::case3(Node* n1, Node* sibling) {
    if (n1->parent->color == BLACK &&
        bothChildrenBlack(sibling)) {
            sibling->color = RED;
            preRemoval(n1->parent);
            return true;
    }
    return false;
}

bool RedBlackTree::case4(Node* n1, Node* sibling) {
    if (n1->parent->color == RED &&
        bothChildrenBlack(sibling)) {
            n1->parent->color = BLACK;
            sibling->color = RED;
            return true;
    }
    return false;
}

bool RedBlackTree::case5(Node* n1, Node* sibling) {
    if (notRedOrNull(sibling->left_child) &&
        nullOrBlack(sibling->right_child) &&
        n1 == n1->parent->left_child) /* */ {
            sibling->color = RED;
            sibling->left_child->color = BLACK;
            rotateRight(sibling);
            return true;
    }
    return false;
}

bool RedBlackTree::case6(Node* n1, Node* sibling) {
    if (nullOrBlack(sibling->left_child) &&
        notRedOrNull(sibling->right_child) &&
        n1 == n1->parent->right_child) {
            sibling->color = RED;
            sibling->right_child->color = BLACK;
            rotateLeft(sibling);
            return true;
    }
    return false;
}

void RedBlackTree::bstRemove(int value) {
    if (root == nullptr) {
        return;
    }
    Node* parent = nullptr;
    Node* current = root;
    //  std::cout << "c\n";
    while (current != nullptr) {
        if (current->value == value) {
            if (current->left_child == nullptr && current->right_child == nullptr) {
                if (parent == nullptr) {
                    root = nullptr;
                } else if (parent->left_child == current) {
                    parent->left_child = nullptr;
                } else {
                    parent->right_child = nullptr;
                }
            } else if (current->right_child == nullptr) {
                if (parent == nullptr) {
                    root = current->left_child;
                } else if (parent->left_child == current) {
                    parent->left_child = current->left_child;
                } else {
                    parent->right_child = current->left_child;
                }
            } else if (current->left_child == nullptr) {
                if (parent == nullptr) {
                    root = current->right_child;
                } else if (parent->left_child == current) {
                    parent->left_child = current->right_child;
                } else {
                    parent->right_child = current->right_child;
                }
            } else {
                Node* successor = current->right_child;
                while (successor != nullptr) {
                    successor = successor->left_child;
                    //  std::cout << "d\n";
                }
                //bstRemove(successor->value);
            }
            return;
        } else if (current->value < value) {
            parent= current;
            current = current->right_child;
        } else {
            parent = current;
            current = current->left_child;
        }
    }
    return;

}
