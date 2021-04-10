#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <vector>
#include "Node.h"

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

        Node* getRoot();
    private:
        void printHelper(Node* n1);

        Node* root;

        //  store nodes in vector since its easier to delete
        std::vector<Node*> node_storage;
};

#endif // REDBLACKTREE_H
