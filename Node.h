#ifndef NODE_H
#define NODE_H

enum COLOR  {RED = 0, BLACK =1};

struct Node {
    Node* parent = nullptr;
    Node* left_child = nullptr;
    Node* right_child = nullptr;
    COLOR color = BLACK;
    int value = -1;
};

#endif // NODE_H
