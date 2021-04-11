#include <iostream>
#include <ctime>
#include <RedBlackTree.h>

int main() {
    RedBlackTree tree;
    clock_t start = clock();

    Node n1, n2, n3, n4, n5, n6, n7, n8;

    n1.value = 20;
    n2.value = 30;
    n3.value = 15;
    n4.value = 11;
    n5.value = 5;
    n6.value = 50;
    n7.value = 34;
    n8.value = 12;

    tree.insert(&n1);
    tree.insert(&n2);
    tree.insert(&n3);
    tree.insert(&n4);
    tree.insert(&n5);
    tree.insert(&n6);
    tree.insert(&n7);
    tree.insert(&n8);

    tree.print();

    tree.remove(n1.value);

    tree.print();

    std::cout << "Time taken: " << (double)(clock() - start)/ CLOCKS_PER_SEC << "\n";

    return 0;
}
