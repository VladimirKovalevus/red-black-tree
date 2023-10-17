
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

  class RBTree
  {
  public:
    RBTree();
    void insert(T value);
    static void printInorder(Node *rt);
    ~RBTree() = default;
    Node *root;

  protected:
  private:
    void insertRecolor(Node *inserted);

    void leftRotation(Node *inserted);
    void rightRotation(Node *inserted);
  };
}