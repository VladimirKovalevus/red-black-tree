#include "tree.hpp"
MySTL::RBTree::RBTree()
{
  root = nullptr;
}

void MySTL::RBTree::insert(T value)
{
  if (root == nullptr)
  {
    root = new Node(value);
    root->color = BLACK;
  }
  else
  {
    Node *current = root;
    Node *parent = current;
    while (current)
    {
      if (current->data == value)
      {
        return;
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
  }
}
void MySTL::RBTree::printInorder(Node *rt)
{
  if (rt == nullptr)
  {
    return;
  }
  printInorder(rt->left);
  std::cout << rt->data << " ";
  printInorder(rt->right);
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
