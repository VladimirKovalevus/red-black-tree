
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace MySTL
{
  enum Color
  {
    RED,
    BLACK
  };
  template <typename _Key, typename _Value>
  struct Node
  {

    std::pair<_Key, _Value> data;
    bool color;
    Node *left, *right, *parent;
    Node(std::pair<_Key, _Value> value, Color color = RED)
    {
      data = value;
      left = right = parent = nullptr;
      color = color;
    }
  };

  template <typename _Key, typename _Value>
  class RBTree
  {
  public:
    typedef _Key key_type;
    typedef _Value value_type;

    RBTree()
    {
      root = nullptr;
    };
    Node<_Key, _Value> *insert(std::pair<_Key, _Value> value)
    {
      if (root == nullptr)
      {
        root = new Node<_Key, _Value>(value);
        root->color = BLACK;
        return root;
      }
      else
      {
        Node<_Key, _Value> *current = root;
        Node<_Key, _Value> *parent = current;
        while (current)
        {
          if (current->data.first == value.first)
          {
            return current;
          }
          parent = current;
          current = current->data.first > value.first ? current->left : current->right;
        }
        current = new Node<_Key, _Value>(value);
        if (parent->data.first > value.first)
        {
          parent->left = current;
        }
        else
        {
          parent->right = current;
        }
        current->parent = parent;
        insertRecolor(current);
        return current;
      }
    }
    void deleteNode(Node<_Key, _Value> *node)
    {
      if (node == nullptr)
      {
        return;
      }
      Node<_Key, _Value> *node_ = moveDeletion(node, node->data.first);
      deleteRecolor(node_);
    }
    static void printInorder(Node<_Key, _Value> *rt)
    {
      if (rt == nullptr)
      {
        return;
      }
      printInorder(rt->left);
      if (rt->color == RED)
      {
        std::cout << "\033[101m";
      }
      else
      {
        std::cout << "\033[40m";
      }
      std::cout << rt->data.first << " "; //<< rt->data.second;
      printInorder(rt->right);
    }
    Node<_Key, _Value> *find(_Key value)
    {
      Node<_Key, _Value> *it = root;
      while (it)
      {
        if (it->data.first == value)
        {
          return it;
        }

        if (value < it->data.first)
        {
          it = it->left;
        }
        else
        {
          it = it->right;
        }
      }
      return nullptr;
    }
    ~RBTree() = default;
    Node<_Key, _Value> *root;

  protected:
  private:
    void insertRecolor(Node<_Key, _Value> *inserted)
    {

      while (inserted != root && inserted->parent->color == RED)
      {
        if (inserted->parent == inserted->parent->parent->left)
        {
          Node<_Key, _Value> *uncle = inserted->parent->parent->right;
          if (uncle && uncle->color == RED)
          {
            inserted->parent->color = BLACK;
            uncle->color = BLACK;
            inserted->parent->parent->color = RED;
            inserted = inserted->parent->parent;
          }
          else
          {
            if (inserted == inserted->parent->right)
            {
              inserted = inserted->parent;
              leftRotation(inserted);
            }
            inserted->parent->color = BLACK;
            inserted->parent->parent->color = RED;
            rightRotation(inserted->parent->parent);
          }
        }
        else
        {
          Node<_Key, _Value> *uncle = inserted->parent->parent->left;
          if (uncle && uncle->color == RED)
          {
            inserted->parent->color = BLACK;
            uncle->color = BLACK;
            inserted->parent->parent->color = RED;
            inserted = inserted->parent->parent;
          }
          else
          {
            if (inserted == inserted->parent->left)
            {
              inserted = inserted->parent;
              rightRotation(inserted);
            }
            inserted->parent->color = BLACK;
            inserted->parent->parent->color = RED;
            leftRotation(inserted->parent->parent);
          }
        }
      }
      root->color = BLACK;
    }
    void deleteRecolor(Node<_Key, _Value> *node)
    {
      if (node == nullptr)
        return;

      if (node == root)
      {
        root = nullptr;
        return;
      }

      if ((node && node->color == RED) || (node->left && node->left->color) == RED || (node->right && node->right->color) == RED)
      {
        Node<_Key, _Value> *child = node->left != nullptr ? node->left : node->right;

        if (node && node == node->parent->left)
        {
          node->parent->left = child;
          if (child)
          {
            child->parent = node->parent;
            child->color = BLACK;
          }
          delete (node);
        }
        else
        {
          node->parent->right = child;
          if (child)
          {
            child->parent = node->parent;
            child->color = BLACK;
          }
          delete (node);
        }
      }
      else
      {
        Node<_Key, _Value> *sibling = nullptr;
        Node<_Key, _Value> *parent = nullptr;
        Node<_Key, _Value> *ptr = node;
        ptr->color = BLACK;
        while (ptr != root && (ptr && ptr->color == BLACK))
        {
          parent = ptr->parent;
          if (ptr == parent->left)
          {
            sibling = parent->right;
            if (sibling && sibling->color == RED)
            {
              sibling->color = BLACK;
              parent->color = RED;
              leftRotation(parent);
            }
            else
            {
              if ((!sibling || sibling->left->color == BLACK) && (!sibling || sibling->right->color == BLACK))
              {
                sibling->color = RED;
                if ((parent && parent->color) == RED)
                  parent->color = BLACK;

                ptr = parent;
              }
              else
              {
                if (sibling && sibling->right->color == BLACK)
                {
                  if (sibling->left)
                  {
                    sibling->left->color = BLACK;
                  }
                  sibling->color = RED;
                  rightRotation(sibling);
                  sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->right)
                  sibling->right->color = BLACK;
                leftRotation(parent);
                break;
              }
            }
          }
          else
          {
            sibling = parent->left;
            if (sibling && sibling->color == RED)
            {
              sibling->color = BLACK;
              parent->color = RED;
              rightRotation(parent);
            }
            else
            {
              if ((!sibling->left || sibling->left->color == BLACK) && (!sibling->right || sibling->right->color == BLACK))
              {
                sibling->color = RED;
                if (parent && parent->color == RED)
                  parent->color = BLACK;

                ptr = parent;
              }
              else
              {
                if (!sibling->left || sibling->left->color == BLACK)
                {
                  if (sibling->right)
                  {
                    sibling->right->color = BLACK;
                  }
                  sibling->color = RED;
                  leftRotation(sibling);
                  sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->left)
                {
                  sibling->left->color = BLACK;
                }
                rightRotation(parent);
                break;
              }
            }
          }
        }
        if (node == node->parent->left)
          node->parent->left = nullptr;
        else
          node->parent->right = nullptr;
        delete (node);
        if (root)
        {
          root->color = BLACK;
        }
      }
    }
    Node<_Key, _Value> *moveDeletion(Node<_Key, _Value> *node, _Key data)
    {
      if (node == nullptr)
        return node;

      if (data < node->data.first)
        return moveDeletion(node->left, data);

      if (data > node->data.first)
        return moveDeletion(node->right, data);

      if (node->left == nullptr || node->right == nullptr)
        return node;

      Node<_Key, _Value> *temp = minValueNode(node->right);
      node->data = temp->data;
      return moveDeletion(node->right, temp->data.first);
    }
    void leftRotation(Node<_Key, _Value> *inserted)
    {
      Node<_Key, _Value> *pivot = inserted->right;
      inserted->right = pivot->left;
      if (pivot->left)
      {
        pivot->left->parent = inserted;
      }
      if (pivot)
        pivot->parent = inserted->parent;
      if (inserted->parent)
      {
        if (inserted == inserted->parent->left)
        {
          inserted->parent->left = pivot;
        }
        else
        {
          inserted->parent->right = pivot;
        }
      }
      else
      {
        root = pivot;
      }
      pivot->left = inserted;
      if (inserted != nullptr)
        inserted->parent = pivot;
    }
    void rightRotation(Node<_Key, _Value> *inserted)
    {
      Node<_Key, _Value> *pivot = inserted->left;
      inserted->left = pivot->right;
      if (pivot->right)
      {
        pivot->right->parent = inserted;
      }
      if (pivot)
        pivot->parent = inserted->parent;
      if (inserted->parent)
      {
        if (inserted == inserted->parent->right)
        {
          inserted->parent->right = pivot;
        }
        else
        {
          inserted->parent->left = pivot;
        }
      }
      else
      {
        root = pivot;
      }
      pivot->right = inserted;
      if (inserted != nullptr)
        inserted->parent = pivot;
    }
    Node<_Key, _Value> *minValueNode(Node<_Key, _Value> *&node)
    {
      Node<_Key, _Value> *ptr = node;

      while (ptr->left != nullptr)
        ptr = ptr->left;

      return ptr;
    }
  };
}