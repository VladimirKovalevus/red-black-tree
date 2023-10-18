#include "tree.hpp"

#include <string>
int main()
{
  MySTL::RBTree<std::string, std::string> tree;

  tree.insert(std::pair<std::string, std::string>("Вот это да", "5125"));
  MySTL::RBTree<std::string, std::string>::printInorder(tree.root);
  std::cout << std::endl;

  tree.insert(std::pair<std::string, std::string>("Оно живое", "da"));
  MySTL::RBTree<std::string, std::string>::printInorder(tree.root);
  std::cout << std::endl;

  // tree.insert(std::pair<std::string, std::string>(3, 2));
  // MySTL::RBTree<std::string, std::string>::printInorder(tree.root);
  // std::cout << std::endl;

  // tree.insert(std::pair<std::string, std::string>(4, 2));
  // MySTL::RBTree<std::string, std::string>::printInorder(tree.root);
  // std::cout << std::endl;

  // tree.insert(std::pair<std::string, std::string>(5, 2));
  // MySTL::RBTree<std::string, std::string>::printInorder(tree.root);
  // std::cout << std::endl;

  // tree.insert(std::pair<std::string, std::string>(-5, 2));
  // MySTL::RBTree<std::string, std::string>::printInorder(tree.root);
  // std::cout << std::endl;
  // tree.insert(std::pair<std::string, std::string>(-3, 2));

  // MySTL::RBTree<std::string, std::string>::printInorder(tree.root);
  // std::cout << std::endl;
  // MySTL::Node<std::string, std::string> *point = tree.find(-3);
  // tree.deleteNode(point);

  // MySTL::RBTree<std::string, std::string>::printInorder(tree.root);
  // std::cout << std::endl;
  // point = tree.find(1);
  // tree.deleteNode(point);

  // MySTL::RBTree<std::string, std::string>::printInorder(tree.root);
  // std::cout << std::endl;
  // point = tree.find(-3);
  // tree.deleteNode(point);

  // MySTL::RBTree<std::string, std::string>::printInorder(tree.root);
}