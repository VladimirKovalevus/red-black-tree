#include "tree.hpp"

namespace MySTL
{
  // template <typename _Key, typename _Value>
  // RBTree<_Key, _Value>::RBTree()
  // {
  //   root = nullptr;
  // }
  // template <typename _Key, typename _Value>
  // Node<_Key, _Value> *RBTree<_Key, _Value>::insert(std::pair<_Key, _Value> value)
  // {
  //   if (root == nullptr)
  //   {
  //     root = new Node<_Key, _Value>(value);
  //     root->color = BLACK;
  //     return root;
  //   }
  //   else
  //   {
  //     Node<_Key, _Value> *current = root;
  //     Node<_Key, _Value> *parent = current;
  //     while (current)
  //     {
  //       if (current->data.first == value)
  //       {
  //         return current;
  //       }
  //       parent = current;
  //       current = current->data.first > value ? current->left : current->right;
  //     }
  //     current = new Node<_Key, _Value>(value);
  //     if (parent->data.first > value)
  //     {
  //       parent->left = current;
  //     }
  //     else
  //     {
  //       parent->right = current;
  //     }
  //     current->parent = parent;
  //     insertRecolor(current);
  //     return current;
  //   }
  // }
  // template <typename _Key, typename _Value>
  // void RBTree<_Key, _Value>::deleteNode(Node<_Key, _Value> *node)
  // {
  //   if (node == nullptr)
  //   {
  //     return;
  //   }
  //   Node<_Key, _Value> *node_ = moveDeletion(node, node->data.first);
  //   deleteRecolor(node_);
  // }
  // template <typename _Key, typename _Value>
  // void printInorder(Node<_Key, _Value> *rt)

  // template <typename _Key, typename _Value>
  // Node<_Key, _Value> *RBTree<_Key, _Value>::find(_Key value)
  // {
  //   Node<_Key, _Value> *it = root;
  //   while (it)
  //   {
  //     if (it->data.first == value)
  //     {
  //       return it;
  //     }

  //     if (value < it->data.first)
  //     {
  //       it = it->left;
  //     }
  //     else
  //     {
  //       it = it->right;
  //     }
  //   }
  //   return nullptr;
  // }
  // template <typename _Key, typename _Value>
  // void RBTree<_Key, _Value>::insertRecolor(Node<_Key, _Value> *inserted)

  // template <typename _Key, typename _Value>
  // void RBTree<_Key, _Value>::deleteRecolor(Node<_Key, _Value> *node)
  // {
  //   if (node == nullptr)
  //     return;

  //   if (node == root)
  //   {
  //     root = nullptr;
  //     return;
  //   }

  //   if ((node && node->color == RED) || (node->left && node->left->color) == RED || (node->right && node->right->color) == RED)
  //   {
  //     Node<_Key, _Value> *child = node->left != nullptr ? node->left : node->right;

  //     if (node && node == node->parent->left)
  //     {
  //       node->parent->left = child;
  //       if (child)
  //       {
  //         child->parent = node->parent;
  //         child->color = BLACK;
  //       }
  //       delete (node);
  //     }
  //     else
  //     {
  //       node->parent->right = child;
  //       if (child)
  //       {
  //         child->parent = node->parent;
  //         child->color = BLACK;
  //       }
  //       delete (node);
  //     }
  //   }
  //   else
  //   {
  //     Node<_Key, _Value> *sibling = nullptr;
  //     Node<_Key, _Value> *parent = nullptr;
  //     Node<_Key, _Value> *ptr = node;
  //     ptr->color = BLACK;
  //     while (ptr != root && (ptr && ptr->color == BLACK))
  //     {
  //       parent = ptr->parent;
  //       if (ptr == parent->left)
  //       {
  //         sibling = parent->right;
  //         if (sibling && sibling->color == RED)
  //         {
  //           sibling->color = BLACK;
  //           parent->color = RED;
  //           leftRotation(parent);
  //         }
  //         else
  //         {
  //           if ((!sibling || sibling->left->color == BLACK) && (!sibling || sibling->right->color == BLACK))
  //           {
  //             sibling->color = RED;
  //             if ((parent && parent->color) == RED)
  //               parent->color = BLACK;

  //             ptr = parent;
  //           }
  //           else
  //           {
  //             if (sibling && sibling->right->color == BLACK)
  //             {
  //               if (sibling->left)
  //               {
  //                 sibling->left->color = BLACK;
  //               }
  //               sibling->color = RED;
  //               rightRotation(sibling);
  //               sibling = parent->right;
  //             }
  //             sibling->color = parent->color;
  //             parent->color = BLACK;
  //             if (sibling->right)
  //               sibling->right->color = BLACK;
  //             leftRotation(parent);
  //             break;
  //           }
  //         }
  //       }
  //       else
  //       {
  //         sibling = parent->left;
  //         if (sibling && sibling->color == RED)
  //         {
  //           sibling->color = BLACK;
  //           parent->color = RED;
  //           rightRotation(parent);
  //         }
  //         else
  //         {
  //           if ((!sibling->left || sibling->left->color == BLACK) && (!sibling->right || sibling->right->color == BLACK))
  //           {
  //             sibling->color = RED;
  //             if (parent && parent->color == RED)
  //               parent->color = BLACK;

  //             ptr = parent;
  //           }
  //           else
  //           {
  //             if (!sibling->left || sibling->left->color == BLACK)
  //             {
  //               if (sibling->right)
  //               {
  //                 sibling->right->color = BLACK;
  //               }
  //               sibling->color = RED;
  //               leftRotation(sibling);
  //               sibling = parent->left;
  //             }
  //             sibling->color = parent->color;
  //             parent->color = BLACK;
  //             if (sibling->left)
  //             {
  //               sibling->left->color = BLACK;
  //             }
  //             rightRotation(parent);
  //             break;
  //           }
  //         }
  //       }
  //     }
  //     if (node == node->parent->left)
  //       node->parent->left = nullptr;
  //     else
  //       node->parent->right = nullptr;
  //     delete (node);
  //     if (root)
  //     {
  //       root->color = BLACK;
  //     }
  //   }
  // }
  // template <typename _Key, typename _Value>
  // Node<_Key, _Value> *RBTree<_Key, _Value>::moveDeletion(Node<_Key, _Value> *node, _Key data)
  // {
  //   if (node == nullptr)
  //     return node;

  //   if (data < node->data.first)
  //     return moveDeletion(node->left, data);

  //   if (data > node->data.first)
  //     return moveDeletion(node->right, data);

  //   if (node->left == nullptr || node->right == nullptr)
  //     return node;

  //   Node<_Key, _Value> *temp = minValueNode(node->right);
  //   node->data = temp->data;
  //   return moveDeletion(node->right, temp->data.first);
  // }
  // template <typename _Key, typename _Value>
  // Node<_Key, _Value> *RBTree<_Key, _Value>::minValueNode(Node<_Key, _Value> *&node)
  // {
  //   Node<_Key, _Value> *ptr = node;

  //   while (ptr->left != nullptr)
  //     ptr = ptr->left;

  //   return ptr;
  // }
  // template <typename _Key, typename _Value>
  // void RBTree<_Key, _Value>::leftRotation(Node<_Key, _Value> *inserted)
  // {
  //   Node<_Key, _Value> *pivot = inserted->right;
  //   inserted->right = pivot->left;
  //   if (pivot->left)
  //   {
  //     pivot->left->parent = inserted;
  //   }
  //   if (pivot)
  //     pivot->parent = inserted->parent;
  //   if (inserted->parent)
  //   {
  //     if (inserted == inserted->parent->left)
  //     {
  //       inserted->parent->left = pivot;
  //     }
  //     else
  //     {
  //       inserted->parent->right = pivot;
  //     }
  //   }
  //   else
  //   {
  //     root = pivot;
  //   }
  //   pivot->left = inserted;
  //   if (inserted != nullptr)
  //     inserted->parent = pivot;
  // }
  // template <typename _Key, typename _Value>
  // void RBTree<_Key, _Value>::rightRotation(Node<_Key, _Value> *inserted)
  // {
  //   Node<_Key, _Value> *pivot = inserted->left;
  //   inserted->left = pivot->right;
  //   if (pivot->right)
  //   {
  //     pivot->right->parent = inserted;
  //   }
  //   if (pivot)
  //     pivot->parent = inserted->parent;
  //   if (inserted->parent)
  //   {
  //     if (inserted == inserted->parent->right)
  //     {
  //       inserted->parent->right = pivot;
  //     }
  //     else
  //     {
  //       inserted->parent->left = pivot;
  //     }
  //   }
  //   else
  //   {
  //     root = pivot;
  //   }
  //   pivot->right = inserted;
  //   if (inserted != nullptr)
  //     inserted->parent = pivot;
  // }
}
