#include <iostream>
#include <RedBlackTree.h>

int main() {
    RedBlackTree tree;


    tree.insertNode(10);
    tree.insertNode(5);
    tree.insertNode(6);
    tree.insertNode(30);

    tree.print();

    return 0;
}
