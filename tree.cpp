#include "tree.hpp"
MySTL::RBTree::RBTree()
{
  root = nullptr;
}

MySTL::Node *MySTL::RBTree::insert(T value)
{
  if (root == nullptr)
  {
    root = new Node(value);
    root->color = BLACK;
    return root;
  }
  else
  {
    Node *current = root;
    Node *parent = current;
    while (current)
    {
      if (current->data == value)
      {
        return current;
      }
      parent = current;
      current = current->data > value ? current->left : current->right;
    }
    current = new Node(value);
    if (parent->data > value)
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
void MySTL::RBTree::deleteNode(Node *node)
{
  if (node == nullptr)
  {
    return;
  }
  Node *node_ = moveDeletion(node, node->data);
  deleteRecolor(node_);
}
void MySTL::RBTree::printInorder(Node *rt)
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
  std::cout << rt->data << " ";
  printInorder(rt->right);
}
MySTL::Node *MySTL::RBTree::find(T value)
{
  Node *it = root;
  while (it)
  {
    if (it->data == value)
    {
      return it;
    }

    if (value < it->data)
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
void MySTL::RBTree::insertRecolor(Node *inserted)
{

  while (inserted != root && inserted->parent->color == RED)
  {
    if (inserted->parent == inserted->parent->parent->left)
    {
      Node *uncle = inserted->parent->parent->right;
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
      Node *uncle = inserted->parent->parent->left;
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

void MySTL::RBTree::deleteRecolor(Node *node)
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
    Node *child = node->left != nullptr ? node->left : node->right;

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
    Node *sibling = nullptr;
    Node *parent = nullptr;
    Node *ptr = node;
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

MySTL::Node *MySTL::RBTree::moveDeletion(Node *node, T data)
{
  if (node == nullptr)
    return node;

  if (data < node->data)
    return moveDeletion(node->left, data);

  if (data > node->data)
    return moveDeletion(node->right, data);

  if (node->left == nullptr || node->right == nullptr)
    return node;

  Node *temp = minValueNode(node->right);
  node->data = temp->data;
  return moveDeletion(node->right, temp->data);
}
MySTL::Node *MySTL::RBTree::minValueNode(Node *&node)
{
  Node *ptr = node;

  while (ptr->left != nullptr)
    ptr = ptr->left;

  return ptr;
}

void MySTL::RBTree::leftRotation(Node *inserted)
{
  Node *pivot = inserted->right;
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
void MySTL::RBTree::rightRotation(Node *inserted)
{
  Node *pivot = inserted->left;
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
