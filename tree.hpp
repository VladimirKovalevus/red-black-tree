
#define compLT (a, b)(a < b)
#define compEQ (a, b)(a == b)
#include <iostream>

namespace MySTL
{
  enum Color
  {
    RED,
    BLACK
  };
  typedef int T;
  // template <typename T, typename V>
  struct Node
  {

    T data = 0;
    bool color;
    Node *left, *right, *parent;
    Node(T value, Color color = RED)
    {
      data = value;
      left = right = parent = nullptr;
      color = color;
    }
  };
  // template <typename T, typename V>
  class RBTree
  {
  public:
    RBTree();
    Node *insert(T value);
    void deleteNode(Node *node);
    static void printInorder(Node *rt);
    Node *find(T value);
    ~RBTree() = default;
    Node *root;

  protected:
  private:
    void insertRecolor(Node *inserted);
    void deleteRecolor(Node *node);
    Node *moveDeletion(Node *node, T data);
    void leftRotation(Node *inserted);
    void rightRotation(Node *inserted);
    Node *minValueNode(Node *&node);
  };
}