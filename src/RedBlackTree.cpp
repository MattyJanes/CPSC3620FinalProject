#include "RedBlackTree.h"
#include <iostream>


RedBlackTree::RedBlackTree() {
    root = new Node;
    node_storage.push_back(root);
}

RedBlackTree::~RedBlackTree() {
    for (std::vector<Node*>::iterator i = node_storage.begin(); i != node_storage.end(); ++i) {
        delete *i;
    }
}




bool RedBlackTree::validTree() {
    if (root->color == RED) {
        return false;
    }

}

//  A red node cannot have a red child
//  Return false if red node
//  Return true if black node
//  Note that all null nodes are black
bool RedBlackTree::checkRedsChildren(Node* n1) {
    if (n1 == nullptr)
        return true;
    if (n1->left_child != nullptr) {
        if (n1->left_child->color == RED) {
            return false;
        }
    }
    if (n1->right_child != nullptr) {
        if (n1->right_child->color == RED) {
            return false;
        }
    }

    bool left = checkRedsChildren(n1->left_child);
    bool right = checkRedsChildren(n1->right_child);
    if (left && right)
        return true;
    else
        return false;
}

//  All paths from a node to any null leaf descendant node must have the same number of
//  black nodes
int RedBlackTree::numBlackNodes(Node* n1) {
    int sum;
    if (n1 == nullptr)
        return 1;
    if (n1->left_child->color == BLACK) {
        sum = 1 + numBlackNodes(n1->left_child);
    }
}

bool RedBlackTree::validTreeHelperFunc(Node* n1) {
    bool red_children_not_red;
    bool same_num_black_nodes;

}



void RedBlackTree::print() {
    if (root == nullptr) {
        std::cout << "EMPTY\n";
    } else {
        printHelper(root);
    }
}

void RedBlackTree::printHelper(Node* n1) {
    if (n1 == nullptr)
        return;
    else {
        if (n1->color == RED) {
            std::cout << "(RED ";
        } else {
            std::cout << "(BLACK ";
        }
        std::cout << " " << n1->value << ") ";
        //  recursively print each node
        std::cout << "\n";
        printHelper(n1->left_child);
        std::cout << " ";
        printHelper(n1->right_child);
    }
}

void RedBlackTree::leftRotate(Node* n1) {
    Node* temp = n1->right_child;
    n1->right_child = temp->left_child;

    if (temp->left_child != nullptr) {
        temp->left_child->parent = n1;
    }
    temp->parent = n1->parent;
    if (n1->parent == nullptr) {
        root = temp;
    } else if (n1 == n1->parent->left_child) {
        n1->parent->left_child = temp;
    } else {
        n1->parent->right_child = temp;
    }
    temp->left_child = n1;
    n1->parent = temp;
}

void RedBlackTree::rightRotate(Node* n1) {
    Node* temp = n1->left_child;
    n1->left_child = temp->right_child;

    if (temp->right_child != nullptr) {
        temp->right_child->parent = n1;
    }
    temp->parent = n1->parent;
    if (n1->parent == nullptr) {
        root = temp;
    } else if(n1 == n1->parent->right_child) {
        n1->parent->right_child = temp;
    } else {
        n1->parent->left_child = temp;
    }
    temp->right_child = n1;
    n1->parent = temp;
}

void RedBlackTree::insertNode(int v) {
    //  initialize new Node
    //  Colour default to black
    Node* n1 = new Node;
    n1->value = v;

    //  store the new node (used for garbage collection later)
    node_storage.push_back(n1);


    Node* temp = root;
    Node* y = nullptr;
    while (temp != nullptr) {
        y = temp;
        if (n1->value < temp->value) {
            temp = temp->left_child;
        } else {
            temp = temp->right_child;
        }
    }
    n1->parent = y;
    if (y == nullptr) {
        root = n1;
    } else if (n1->value < y->value) {
        y->left_child = n1;
    } else {
        y->right_child = n1;
    }
    n1->left_child = nullptr;
    n1->right_child = nullptr;
    n1->color = RED;
    cleanAfterInsert(n1);
}

void RedBlackTree::cleanAfterInsert(Node* n1) {
    std::cout << "parents color: " << n1->parent->color << "\n";
    while (n1->parent->color == RED) {
        if (n1->parent->parent != nullptr) {
            if (n1->parent == n1->parent->parent->left_child) {
                Node* temp = n1->parent->parent->right_child;
                if (temp->color == RED) {
                    n1->parent->color = BLACK;
                    temp->color = BLACK;
                    n1->parent->parent->color = RED;
                    n1 = n1->parent->parent;
                } else {
                    if (n1 == n1->parent->right_child) {
                        n1 = n1->parent;
                        leftRotate(n1);
                    }
                    n1->parent->color = BLACK;
                    n1->parent->parent->color = RED;
                    rightRotate(n1->parent->parent);
                }
            }
        } else {
            n1->parent->color == BLACK;
        }
    }
    root->color = BLACK;
}

Node* RedBlackTree::getRoot() {
    return root;
}
