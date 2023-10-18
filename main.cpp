#include "tree.hpp"

int main()
{
  MySTL::RBTree tree;

  tree.insert(1);
  MySTL::RBTree::printInorder(tree.root);
  std::cout << std::endl;

  tree.insert(2);
  MySTL::RBTree::printInorder(tree.root);
  std::cout << std::endl;

  tree.insert(3);
  MySTL::RBTree::printInorder(tree.root);
  std::cout << std::endl;

  tree.insert(4);
  MySTL::RBTree::printInorder(tree.root);
  std::cout << std::endl;

  tree.insert(5);
  MySTL::RBTree::printInorder(tree.root);
  std::cout << std::endl;

  tree.insert(-5);
  MySTL::RBTree::printInorder(tree.root);
  std::cout << std::endl;
  tree.insert(-3);

  MySTL::RBTree::printInorder(tree.root);
  std::cout << std::endl;
  MySTL::Node *point = tree.find(-3);
  tree.deleteNode(point);

  MySTL::RBTree::printInorder(tree.root);
  std::cout << std::endl;
  point = tree.find(1);
  tree.deleteNode(point);

  // MySTL::RBTree::printInorder(tree.root);
  // std::cout << std::endl;
  // point = tree.find(-3);
  // tree.deleteNode(point);

  MySTL::RBTree::printInorder(tree.root);
  // std::cout << tree.root->right->data;
}