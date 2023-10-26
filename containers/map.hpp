#include "tree.hpp"
#include <asm-generic/errno-base.h>
#include <cstddef>
#include <initializer_list>


namespace mystl {

template <typename _Key,typename _Value>
class Map : protected RBTree<_Key,_Value>{

  


    using key_type = _Key;
    using mapped_type = _Value;
    using value_type = std::pair<key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using Iterator = typename RBTree<_Key,_Value>::Iterator;
public:
    Map():RBTree<_Key, _Value>(){}
        
    Map(const Map& other):RBTree<_Key,_Value>(other){
    }
    Map(Map&& other):RBTree<_Key,_Value>(other){
    }
    Map(std::initializer_list<value_type> list):RBTree<_Key, _Value>(list){
    }

    bool empty(){
        return RBTree<_Key,_Value>::empty();
    }
    size_t size(){
        return RBTree<_Key,_Value>::size();
    }
    size_t max_size(){
        return RBTree<_Key,_Value>::max_size();
    }
    bool contains(const _Key &key) { return RBTree<_Key,_Value>::contains(key); }

    void erase(Iterator pos) { deleteNode(pos.node); }
    void swap(Map &other) {
        RBTree<_Key,_Value>::swap(other);
    }
    void merge(Map &other) {
        RBTree<_Key,_Value>::merge(other);
    }
    void clear() {
        RBTree<_Key,_Value>::clear();
    }
    Iterator insert(value_type value) {
        return RBTree<_Key,_Value>::insert(value);
    }

  Iterator begin() { return RBTree<_Key,_Value>::begin(); }
  Iterator end() { return RBTree<_Key,_Value>::end(); }

  _Value &at(const _Key &key) {
    return RBTree<_Key,_Value>::at(key);
  }
  Iterator find(const _Key &key) {
    return RBTree<_Key,_Value>::find(key);
  }

  _Value &operator[](const _Key &key) {
    return RBTree<_Key,_Value>::operator[](key); 
  }
  template <typename  ...Args>
  std::vector<std::pair<Iterator,bool>> insert_many(Args&&... args){
      std::vector<std::pair<Iterator,bool>> vec;
      (vec.push_back({insert(args),true}),...);
      return vec;
  }

};

}