#include <iostream>
#include <string>

using namespace std;



struct Node {
  int value = 0;
  Node *parent = nullptr;
  Node *left = nullptr;
  Node *right = nullptr;
  bool isRed = false;

  void operator=(const Node rhs) {
    value= rhs.value;
    *parent = *rhs.parent;
    *left = *rhs.left;
    *right = *rhs.right;
    isRed = rhs.isRed;
  }
};

bool operator==(const Node &lhs, const Node &rhs){
  if (
    lhs.value == rhs.value &&
    *lhs.parent == *rhs.parent &&
    *lhs.left == *rhs.left &&
    *lhs.right == *rhs.right &&
    lhs.isRed == rhs.isRed
  ) return true;
  else return false;
}

bool operator!=(const Node lhs, const Node rhs){
  if (
    lhs.value != rhs.value ||
    *lhs.parent != *rhs.parent ||
    *lhs.left != *rhs.left ||
    *lhs.right != *rhs.right ||
    lhs.isRed != rhs.isRed
  ) return true;
  else return false;
}

class RedBlackTree {
 public:
   RedBlackTree(){
    TNull = Node();
    rootNode = TNull;
  };
   virtual ~RedBlackTree(){
   };

   void preOrder(){
     preOrderHelp(this -> rootNode);
   };
   void inOrder(){
     inOrderHelp(this -> rootNode);
   };
   void postorder() {
     postOrderHelp(this->rootNode);
   };

   Node getRoot(){
     return this->rootNode;
   };
   Node search(int x){
    return searchTreeHelp(this -> rootNode, x);
   };
   Node min(Node node){
     while (*node.left != TNull) {
       node = *node.left;
     }
     return node;
   };
   Node max(Node node){
    while (*node.right != TNull) {
      node = *node.right;
    }
    return node;
  };
   Node successor(Node node){
    if (*node.right != TNull) {
      return min(*node.right);
    }

    Node y = *node.parent;
    while (y != TNull && node == *y.right) {
      node = y;
      y = *y.parent;
    }
    return y;
  };
   Node predecessor(Node node){
    if (*node.left != TNull) {
      return max(*node.left);
    }

    Node y = *node.parent;
    while (y != TNull && node == *y.left) {
      node = y;
      y = *y.parent;
    }

    return y;
  };

   void leftRotate(Node node){
    Node y = *node.right;
    *node.right = *y.left;
    if (*y.left != TNull) {
      *y.left->parent = node;
    }
    *y.parent = *node.parent;
    if (*node.parent == TNull) {
      this->rootNode = y;
    } else if (node == *node.parent->left) {
      *node.parent->left = y;
    } else {
      *node.parent->right = y;
    }
    *y.left = node;
    *node.parent = y;
  };
   void rightRotate(Node node){
    Node y = *node.left;
    *node.left = *y.right;
    if (*y.right != TNull) {
      *y.right->parent = node;
    }
    *y.parent = *node.parent;
    if (*node.parent == TNull) {
      this -> rootNode = y;
    } else if (node == *node.parent->right) {
      *node.parent->right = y;
    } else {
      *node.parent->left = y;
    }
    *y.right = node;
    *node.parent = y;
  }
;

   void insert(int key){
    Node node;
    node.value = key;
    *node.left = TNull;
    *node.right = TNull;
    node.isRed = true;

    Node y;
    Node x = this -> rootNode;

    while (x != TNull) {
      y = x;
      if (node.value < x.value) {
        x = *x.left;
      } else {
        x = *x.right;
      }
    }

    *node.parent = y;
    if (y == TNull) {
      rootNode = node;
    } else if (node.value < y.value) {
      *y.left = node;
    } else {
      *y.right = node;
    }

    if (*node.parent == TNull) {
      node.isRed = false;
      return;
    }

    if (*node.parent->parent == TNull) {
      return;
    }

    insertFix(node);
  };
   void deleteNode(int data){
     deleteNodeHelp(this->rootNode, data);
   };

   void printTree(){
     if (rootNode != TNull) {
        printHelp(this->rootNode, "", true);
      }
   };

 private:
  Node rootNode;
  Node TNull;

  void iniTNullNode(Node node, Node &parent){
    node.value = 0;
    node.parent = &parent;
    node.left = nullptr;
    node.right = nullptr;
    node.isRed = false;
  };

  void preOrderHelp(Node node){
    if (node != TNull) {
      std::cout << node.value << " ";
      preOrderHelp(*node.left);
      preOrderHelp(*node.right);
    }
  };
  void inOrderHelp(Node node){
    if (node != TNull) {
      inOrderHelp(*node.left);
      std::cout << node.value << " ";
      inOrderHelp(*node.right);
    }
  };
  void postOrderHelp(Node node){
    if (node != TNull) {
      postOrderHelp(*node.left);
      postOrderHelp(*node.right);
      std::cout << node.value << " ";
    }
  };
  Node searchTreeHelp(Node node, int key){
    if (node == TNull || key == node.value) {
      return node;
    }

    if (key < node.value) {
      return searchTreeHelp(*node.left, key);
    }
    return searchTreeHelp(*node.right, key);
  };
  void deleteNodeHelp(Node node, int key){
    Node z = TNull;
    Node x, y;
    while (node != TNull) {
      if (node.value == key) {
        z = node;
      }

      if (node.value <= key) {
        node = *node.right;
      } else {
        node = *node.left;
      }
    }

    if (z == TNull) {
      std::cout << "Key not found in the tree" << std::endl;
      return;
    }

    y = z;
    int y_original_color = y.isRed;
    if (*z.left == TNull) {
      x = *z.right;
      rbChange(z, *z.right);
    } else if (*z.right == TNull) {
      x = *z.left;
      rbChange(z, *z.left);
    } else {
      y = min(*z.right);
      y_original_color = y.isRed;
      x = *y.right;
      if (*y.parent == z) {
        *x.parent = y;
      } else {
        rbChange(y, *y.right);
        *y.right = *z.right;
        *y.right->parent = y;
      }

      rbChange(z, y);
      *y.left = *z.left;
      *y.left->parent = y;
      y.isRed = z.isRed;
    }
    if (y_original_color == 0) {
      deleteFix(x);
    }
  };

  void printHelp(Node root, std::string indenter, bool last){
    if (root != TNull) {
      std::cout << indenter;
      if (last) {
        std::cout << "R----";
        indenter += "   ";
      } else {
        std::cout << "L----";
        indenter += "|  ";
      }

      std::string sColor = root.isRed ? "RED" : "BLACK";
      std::cout << root.value << "(" << sColor << ")" << std::endl;
      printHelp(*root.left, indenter, false);
      printHelp(*root.right, indenter, true);
    }
  };

  void deleteFix(Node x){
    Node s;
    while (x != rootNode && x.isRed == false) {
      if (x == *x.parent -> left) {
        s = *x.parent -> right;
        if (s.isRed == true) {
          s.isRed = false;
          x.parent -> isRed = true;
          leftRotate(*x.parent);
          s = *x.parent -> right;
        }

        if (s.left -> isRed == false && s.right -> isRed == false) {
          s.isRed = true;
          x = *x.parent;
        } else {
          if (s.right -> isRed == false) {
            s.left -> isRed = false;
            s.isRed = true;
            rightRotate(s);
            s = *x.parent -> right;
          }

          s.isRed = x.parent -> isRed;
          x.parent -> isRed = false;
          s.right -> isRed = false;
          leftRotate(*x.parent);
          x = rootNode;
        }
      } else {
        s = *x.parent -> left;
        if (s.isRed == true) {
          s.isRed = false;
          x.parent -> isRed = true;
          rightRotate(*x.parent);
          s = *x.parent -> left;
        }

        if (s.right -> isRed == false && s.right -> isRed == false) {
          s.isRed = true;
          x = *x.parent;
        } else {
          if (s.left -> isRed == false) {
            s.right -> isRed = false;
            s.isRed = true;
            leftRotate(s);
            s = *x.parent -> left;
          }

          s.isRed = x.parent -> isRed;
          x.parent -> isRed = false;
          s.left -> isRed = false;
          rightRotate(*x.parent);
          x = rootNode;
        }
      }
    }
    x.isRed = false;
  };
  void insertFix(Node x){
    Node u;
    while (x.parent -> isRed == true) {
      if (*x.parent == *x.parent->parent->right) {
        u = *x.parent->parent->left;
        if (u.isRed == true) {
          u.isRed = false;
          x.parent -> isRed = false;
          x.parent->parent->isRed = true;
          x = *x.parent->parent;
        } else {
          if (x == *x.parent->left) {
            x = *x.parent;
            rightRotate(x);
          }
          x.parent -> isRed = false;
          x.parent -> parent -> isRed = true;
          leftRotate(*x.parent->parent);
        }
      } else {
        u = *x.parent->parent->right;

        if (u.isRed == true) {
          u.isRed = false;
          x.parent -> isRed = false;
          x.parent->parent -> isRed = true;
          x = *x.parent->parent;
        } else {
          if (x == *x.parent->right) {
            x = *x.parent;
            leftRotate(x);
          }
          x.parent -> isRed = false;
          x.parent->parent -> isRed = true;
          rightRotate(*x.parent->parent);
        }
      }
      if (x == rootNode) {
        break;
      }
    }
    rootNode.isRed = 0;
  };

  void rbChange(Node a, Node b){
    if (*a.parent == TNull) {
      rootNode = b;
    } else if (a == *a.parent -> left) {
      *a.parent -> left = b;
    } else {
      *a.parent -> right = b;
    }
    *b.parent = *a.parent;
  };
};


int main()
{

  RedBlackTree* bst = new RedBlackTree();
  std::cout << "Hello, world" << std::endl;

  bst.insert(55);
  bst.insert(40);
  bst.insert(65);
  bst.insert(60);
  bst.insert(75);
  bst.insert(57);

  bst.printTree();
  cout << endl
     << "After deleting" << endl;
  bst.deleteNode(40);
  bst.printTree();

  while (cin.get() != '\n');

  //delete bst;
  return 0;
}
