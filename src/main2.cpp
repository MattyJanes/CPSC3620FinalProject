#include <iostream>
#include <vector>
 
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
        void leftRotate(Node* n1);
        void rightRotate(Node* n2);

        void insertNode(int value);

        void cleanAfterInsert(Node* n1);

        void deleteNode(Node* n1);

        void cleanAfterDelete(Node* n1);

        void printNode(Node* n1);

        Node* getRoot();
    private:
        void printHelper(Node* n1);

        Node* root;

        //  store nodes in vector since its easier to delete
        std::vector<Node*> node_storage;
};

int main() {
    RedBlackTree tree;


    tree.insertNode(10);
    tree.insertNode(5);
    tree.insertNode(6);
    tree.insertNode(30);

    tree.print();

    return 0;
}

RedBlackTree::RedBlackTree() {
    root = new Node;
    node_storage.push_back(root);
}

RedBlackTree::~RedBlackTree() {
    for (std::vector<Node*>::iterator i = node_storage.begin(); i != node_storage.end(); ++i) {
        delete *i;
    }
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

    if (n1->parent == nullptr) {
        n1->color = BLACK;
        return;
    }
    if (n1->parent->parent == nullptr) {
        return;
    }

    cleanAfterInsert(n1);
}

void RedBlackTree::cleanAfterInsert(Node* n1) {
    //std::cout << "parents color: " << n1->parent->color << "\n";
    Node* temp;
    while (n1->parent->color == RED) {
        //std::cout << "a\n";
        if (n1->parent == n1->parent->parent->left_child) {
            //std::cout << "b\n";
            temp = n1->parent->parent->right_child;
            if (temp->color == RED) {
                //std::cout << "c\n";
                n1->parent->color = BLACK;
                temp->color = BLACK;
                n1->parent->parent->color = RED;
                n1 = n1->parent->parent;
            } else {
                //std::cout << "d\n";
                if (n1 == n1->parent->right_child) {
                    n1 = n1->parent;
                    leftRotate(n1);
                }
                n1->parent->color = BLACK;
                n1->parent->parent->color = RED;
                rightRotate(n1->parent->parent);
            }
        } else if (n1->parent == n1->parent->parent->right_child) {
            //std::cout << "e\n";
            if (n1->parent->parent->left_child != nullptr)
                temp = n1->parent->parent->left_child;
            if (temp->color == 1) {
                //std::cout << "f\n";
                n1->parent->color = BLACK;
                temp->color = BLACK;
                n1->parent->parent->color = RED;
                n1 = n1->parent->parent;
            } else {
                //std::cout << "g\n";
                if (n1 == n1->parent->left_child) {
                    n1 = n1->parent;
                    rightRotate(n1);
                }
                n1->parent->color = BLACK;
                n1->parent->parent->color = RED;
                leftRotate(n1->parent->parent);
            }
        } else if (n1 == root) {
            break;
        } else {
           //  do nothing
        }
    }
    root->color = BLACK;
    //std::cout << "done\n";
}

void RedBlackTree::deleteNode(Node* n1) {

}

void RedBlackTree::cleanAfterDelete(Node* n1) {

}

Node* RedBlackTree::getRoot() {
    return root;
}


