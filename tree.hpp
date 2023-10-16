
#define compLT (a, b)(a < b)
#define compEQ (a, b)(a == b)

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
    Node(T value)
    {
      data = value;
      left = right = parent = nullptr;
    }
  };

  class RBTree
  {
  public:
    RBTree();
    void insert(T value);

    ~RBTree();

  protected:
  private:
    Node *root;
    void leftRotation();
    void rightRotation();
    void recolor();
  };
}