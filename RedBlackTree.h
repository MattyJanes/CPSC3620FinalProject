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

    private:
        void bstInsert(Node* n1);
        void printHelper(Node* n1, int spacer, int mode);

        Node* root;

        //  store nodes in vector since its easier to delete
        std::vector<Node*> node_storage;
};

#endif // REDBLACKTREE_H
