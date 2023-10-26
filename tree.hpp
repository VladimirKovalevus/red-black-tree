#ifndef __SRC_COMMON_RB_TREE_H__
#define __SRC_COMMON_RB_TREE_H__

#include <cstdlib>
#include <ctime>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>
#define DEBUG


namespace mystl {
enum Color { RED, BLACK };
template <typename _Key, typename _Value>
struct Node {
  std::pair<const _Key, _Value> data;
  bool color;
  Node *left, *right, *parent;
  Node(std::pair<const _Key, _Value> value, Color color = RED) : data{value} {
    left = right = parent = nullptr;
    color = color;
  }
  static Node<_Key, _Value> *reassign(Node *to, Node *from) {
    Node<_Key, _Value> *result = new Node(from->data);
    result->parent = to->parent;
    result->left = to->left;
    result->right = to->right;
    if (result->right) {
      result->right->parent = result;
    }
    if (result->left) {
      result->left->parent = result;
    }
    if (result->parent) {
      if (result->parent->right == to) {
        result->parent->right = result;
      } else {
        result->parent->left = result;
      }
    }
    delete to;
    return result;
  }
};

template <typename _Key, typename _Value>
class RBTree {
  class Iterator {
    friend class RBTree<_Key, _Value>;
    using key_type = _Key;
    using mapped_type = _Value;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = const value_type *;

   public:
    Iterator(Node<_Key, _Value> *init) : node(init) {}
    Iterator(const Iterator &other) { node = other.node; }
    Iterator(Iterator &&other) {
      node = other.node;
      other.node = nullptr;
    }
    Iterator operator++() {
      Iterator temp(*this);
      __plus();
      return temp;
    }
    Iterator operator++(int) {
      __plus();
      return *this;
    }
    Iterator operator--() {
      Iterator temp(*this);
      __minus();
      return temp;
    }
    Iterator operator--(int) {
      __minus();
      return *this;
    }
    bool operator==(const Iterator &other) { return this->node == other.node; }
    bool operator!=(const Iterator &other) { return this->node != other.node; }
    value_type *operator->() { return &(node->data); }

    Iterator &operator=(const Iterator &other) {
      if (this != &other) {
        node = other.node;
      }
      return *this;
    }
    Iterator &operator=(Iterator &&other) {
      if (this != &other) {
        node = other.node;
        other.node = nullptr;
      }
      return *this;
    }

   protected:
    Node<_Key, _Value> *node;

    void __plus() {
      if (node->parent == nullptr) {
        throw std::out_of_range("out of range");
      }
      if (node->right) {
        node = node->right;
        while (node->left) {
          node = node->left;
        }
      } else if (!node->left && !node->right) {
        if (node->parent) {
          if (node->parent->left == node)
            node = node->parent;
          else if (node->parent->right == node) {
            while (node->parent && node->parent->right == node) {
              node = node->parent;
            }
            if (node->parent && node == node->parent->left) node = node->parent;
          }
        }
      } else if (node->parent) {
        node = node->parent;
      }
    }
    void __minus() {
      if (node->parent == nullptr) {
        throw std::out_of_range("131");
      }
      if (node->left) {
        node = node->left;
        while (node->right) {
          node = node->right;
        }
      } else if (!node->left && !node->right) {
        if (node->parent) {
          if (node->parent->right == node)
            node = node->parent;
          else if (node->parent->left == node) {
            while (node->parent && node->parent->left == node)
              node = node->parent;

            if (node->parent && node == node->parent->left) node = node->parent;
          }
        }
      } else if (node->parent) {
        node = node->parent;
      }
      if (node->parent == nullptr) {
        throw std::out_of_range("out of range");
      }
    }
  };

 public:
  using key_type = _Key;
  using mapped_type = _Value;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;

  RBTree() {
    root = nullptr;
    end_ = new Node<_Key, _Value>({_Key(), _Value()});
  };
  RBTree(const RBTree &other) {
    for (auto it = other.begin(); it != other.end(); it++) {
      insert({it->first, it->second});
    }
  }
  RBTree(RBTree &&other) : end_() {
    if (this != &other) {
      root = other.root;
      root->parent = end_;
      end_->right = root;
      end_->left = root;

      other.clear();
    }
  }
  RBTree(std::initializer_list<value_type> init):RBTree() {
    for(auto it = init.begin();it!=init.end();++it){
      insert({it->first,it->second});
    }
  }
  template <typename  ...Args>
  std::vector<std::pair<Iterator,bool>> insert_many(Args&&... args){
      std::vector<std::pair<Iterator,bool>> vec;
      (vec.push_back({insert(args),true}),...);
      return vec;
  }

  Node<_Key, _Value> *insert(value_type value) {
    if (root == nullptr) {
      root = new Node<_Key, _Value>(value);
      root->color = BLACK;
      root->parent = end_;
      end_->right = root;
      end_->left = root;

      return root;
    } else {
      root->parent = nullptr;
      Node<_Key, _Value> *current = root;
      Node<_Key, _Value> *parent = current;
      while (current) {
        if (current->data.first == value.first) {
          return current;
        }
        parent = current;
        current =
            current->data.first > value.first ? current->left : current->right;
      }
      current = new Node<_Key, _Value>(value);
      if (parent->data.first > value.first) {
        parent->left = current;
      } else {
        parent->right = current;
      }
      current->parent = parent;
      insertRecolor(current);

      this->root->parent = end_;
      end_->right = root;
      end_->left = root;
      return current;
    }
  }
  void deleteNode(Node<_Key, _Value> *node) {
    if (node == nullptr) {
      return;
    }
    root->parent = nullptr;
    Node<_Key, _Value> *node_ = moveDeletion(node, node->data.first);
    deleteRecolor(node_);
    if (root) {
      root->parent = end_;
      end_->right = root;
      end_->left = root;
    }
  }
#ifdef DEBUG
  void printInorder() { inorderTraversial(root); }
#endif

  virtual ~RBTree() { destroyTree(root); }

  bool empty() { return root == nullptr; }
  size_t max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(Node<_Key, _Value>);
  }
  void clear() {
    destroyTree(root);
    root = nullptr;
    delete end_;
  }
  size_t size() { return sizeCount(root); }

  Iterator begin() { return Iterator(minValueNode(root)); }
  Iterator end() { return Iterator(end_); }

  _Value &at(const _Key &key) {
    Iterator it = find(key);
    if (it == end()) {
      throw std::out_of_range("0_0");
    }
    return it->second;
  }
  Iterator find(const _Key &key) {
    Node<_Key, _Value> *it = root;
    while (it) {
      if (it->data.first > key) {
        it = it->left;
      } else if (it->data.first < key) {
        it = it->right;
      } else {
        break;
      }
    }
    if (!it) {
      it = end_;
    }
    return Iterator(it);
  }

  _Value &operator[](const _Key &key) {
    Iterator it = find(key);
    if (it == end()) {
      it = Iterator(insert({key, _Value()}));
    }
    return it->second;
  }
  bool contains(const _Key &key) { return find(key) != end(); }
  void erase(Iterator pos) { deleteNode(pos.node); }
  void swap(RBTree &other) {
    Node<_Key, _Value> *tmp = other.root;
    other.root = this->root;
    this->root = tmp;
    tmp = other.end_;
    other.end_ = end_;
    this->end_ = tmp;
  }
  void merge(RBTree &other) {

    for(auto it= other.begin(); it !=other.end();++it){
      insert({it->first,it->second});
    }
    other.clear();
  }

 protected:
  Node<_Key, _Value> *root;
  Node<_Key, _Value> *end_;

  static void inorderTraversial(Node<_Key, _Value> *rt) {
    if (!rt) {
      return;
    }
    inorderTraversial(rt->left);
    std::cout << rt->data.first << " ";
    inorderTraversial(rt->right);
  }
  static size_t sizeCount(Node<_Key, _Value> *rt) {
    if (!rt) {
      return 0;
    }
    return sizeCount(rt->left) + sizeCount(rt->right) + 1;
  }
  void destroyTree(Node<_Key, _Value> *rt) {
    if (!rt) return;

    destroyTree(rt->left);
    destroyTree(rt->right);
    delete rt;
  }
  void insertRecolor(Node<_Key, _Value> *inserted) {
    while (inserted != root && inserted->parent->color == RED) {
      if (inserted->parent == inserted->parent->parent->left) {
        Node<_Key, _Value> *uncle = inserted->parent->parent->right;
        if (uncle && uncle->color == RED) {
          inserted->parent->color = BLACK;
          uncle->color = BLACK;
          inserted->parent->parent->color = RED;
          inserted = inserted->parent->parent;
        } else {
          if (inserted == inserted->parent->right) {
            inserted = inserted->parent;
            leftRotation(inserted);
          }
          inserted->parent->color = BLACK;
          inserted->parent->parent->color = RED;
          rightRotation(inserted->parent->parent);
        }
      } else {
        Node<_Key, _Value> *uncle = inserted->parent->parent->left;
        if (uncle && uncle->color == RED) {
          inserted->parent->color = BLACK;
          uncle->color = BLACK;
          inserted->parent->parent->color = RED;
          inserted = inserted->parent->parent;
        } else {
          if (inserted == inserted->parent->left) {
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
    root->parent = end_;
    end_->right = root;
    end_->left = root;
  }
  void deleteRecolor(Node<_Key, _Value> *node) {
    if (node == nullptr) return;

    if (node == root) {
      root = nullptr;
      return;
    }
    root->parent = nullptr;
    if ((node && node->color == RED) ||
        (node->left && node->left->color) == RED ||
        (node->right && node->right->color) == RED) {
      Node<_Key, _Value> *child =
          node->left != nullptr ? node->left : node->right;

      if (node && node == node->parent->left) {
        node->parent->left = child;
        if (child) {
          child->parent = node->parent;
          child->color = BLACK;
        }
        delete (node);
      } else {
        node->parent->right = child;
        if (child) {
          child->parent = node->parent;
          child->color = BLACK;
        }
        delete (node);
      }
    } else {
      Node<_Key, _Value> *sibling = nullptr;
      Node<_Key, _Value> *parent = nullptr;
      Node<_Key, _Value> *ptr = node;
      ptr->color = BLACK;
      while (ptr != root && (ptr && ptr->color == BLACK)) {
        parent = ptr->parent;
        if (ptr == parent->left) {
          sibling = parent->right;
          if (sibling && sibling->color == RED) {
            sibling->color = BLACK;
            parent->color = RED;
            leftRotation(parent);
          } else {
            if ((!sibling || sibling->left->color == BLACK) &&
                (!sibling || sibling->right->color == BLACK)) {
              sibling->color = RED;
              if ((parent && parent->color) == RED) parent->color = BLACK;

              ptr = parent;
            } else {
              if (sibling && sibling->right->color == BLACK) {
                if (sibling->left) {
                  sibling->left->color = BLACK;
                }
                sibling->color = RED;
                rightRotation(sibling);
                sibling = parent->right;
              }
              sibling->color = parent->color;
              parent->color = BLACK;
              if (sibling->right) sibling->right->color = BLACK;
              leftRotation(parent);
              break;
            }
          }
        } else {
          sibling = parent->left;
          if (sibling && sibling->color == RED) {
            sibling->color = BLACK;
            parent->color = RED;
            rightRotation(parent);
          } else {
            if ((!sibling->left || sibling->left->color == BLACK) &&
                (!sibling->right || sibling->right->color == BLACK)) {
              sibling->color = RED;
              if (parent && parent->color == RED) parent->color = BLACK;

              ptr = parent;
            } else {
              if (!sibling->left || sibling->left->color == BLACK) {
                if (sibling->right) {
                  sibling->right->color = BLACK;
                }
                sibling->color = RED;
                leftRotation(sibling);
                sibling = parent->left;
              }
              sibling->color = parent->color;
              parent->color = BLACK;
              if (sibling->left) {
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

      if (root) {
        root->color = BLACK;
      }
    }
  }
  Node<_Key, _Value> *moveDeletion(Node<_Key, _Value> *node, key_type data) {
    if (node == nullptr) return node;

    if (data < node->data.first) return moveDeletion(node->left, data);

    if (data > node->data.first) return moveDeletion(node->right, data);

    if (node->left == nullptr || node->right == nullptr) return node;

    Node<_Key, _Value> *temp = minValueNode(node->right);
    node = Node<_Key, _Value>::reassign(node, temp);
    // Node<_Key, _Value> *hmm= new Node<_Key, _Value>(temp->data);
    return moveDeletion(node->right, temp->data.first);
  }
  void leftRotation(Node<_Key, _Value> *inserted) {
    Node<_Key, _Value> *pivot = inserted->right;
    inserted->right = pivot->left;
    if (pivot->left) {
      pivot->left->parent = inserted;
    }
    if (pivot) {
      if (pivot->parent != end_) {
        pivot->parent = inserted->parent;
      } else {
      }
    }
    if (inserted->parent && inserted->parent != end_) {
      if (inserted == inserted->parent->left) {
        inserted->parent->left = pivot;
      } else {
        inserted->parent->right = pivot;
      }
    } else {
      root = pivot;
    }
    pivot->left = inserted;
    if (inserted != nullptr) inserted->parent = pivot;
  }
  void rightRotation(Node<_Key, _Value> *inserted) {
    Node<_Key, _Value> *pivot = inserted->left;
    inserted->left = pivot->right;
    if (pivot->right) {
      pivot->right->parent = inserted;
    }
    if (pivot) pivot->parent = inserted->parent;
    if (inserted->parent && inserted->parent != end_) {
      if (inserted == inserted->parent->right) {
        inserted->parent->right = pivot;
      } else {
        inserted->parent->left = pivot;
      }
    } else {
      root = pivot;
    }
    pivot->right = inserted;
    if (inserted != nullptr) inserted->parent = pivot;
  }
  Node<_Key, _Value> *minValueNode(Node<_Key, _Value> *&node) {
    if (node == nullptr) {
      return node;
    }
    Node<_Key, _Value> *ptr = node;

    while (ptr->left != nullptr) ptr = ptr->left;

    return ptr;
  }
  Node<_Key, _Value> *maxValueNode(Node<_Key, _Value> *&node) {
    if (node == nullptr) {
      return node;
    }
    Node<_Key, _Value> *ptr = node;

    while (ptr->right != nullptr) ptr = ptr->right;

    return ptr;
  }
};

}  // namespace mystl
#endif  // __SRC_COMMON_RB_TREE_H__