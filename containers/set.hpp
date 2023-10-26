#include "tree.hpp"


namespace mystl{
template <typename _Key>
class Set : protected RBTree<_Key, _Key>{

    class SetIterator : public RBTree<_Key, _Key>::Iterator{
        using key_type = _Key;
        using value_type = _Key;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = const value_type *;
        using Iterator = SetIterator;

   public:
    
    SetIterator(const typename RBTree<_Key, _Key>::Iterator &other):RBTree<_Key, _Key>::Iterator(other) {  }
    SetIterator(typename RBTree<_Key, _Key>::Iterator &&other):RBTree<_Key, _Key>::Iterator(other){
    }
    
    const_reference operator*(){
        return (this->node->data.first);
    }
    // const value_type* operator->(){
    // }
    };


  using key_type = _Key;
  using value_type = _Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using Iterator = SetIterator;
public:
  public:
    Set():RBTree<_Key, _Key>(){}
        
    Set(const Set& other):RBTree<_Key,_Key>(other){
    }
    Set(Set&& other):RBTree<_Key,_Key>(other){
    }
    Set(std::initializer_list<value_type> list):RBTree<_Key, _Key>(list){
    }

    bool empty(){
        return RBTree<_Key,_Key>::empty();
    }
    size_t size(){
        return RBTree<_Key,_Key>::size();
    }
    size_t max_size(){
        return RBTree<_Key,_Key>::max_size();
    }
    bool contains(const _Key &key) { return RBTree<_Key,_Key>::contains(key); }

    void erase(Iterator pos) { deleteNode(pos.node); }
    void swap(Set &other) {
        RBTree<_Key,_Key>::swap(other);
    }
    void merge(Set &other) {
        RBTree<_Key,_Key>::merge(other);
    }
    void clear() {
        RBTree<_Key,_Key>::clear();
    }
    Iterator insert(value_type value) {
        return SetIterator(RBTree<_Key,_Key>::insert({value,value}));
    }

  Iterator begin() { return RBTree<_Key,_Key>::begin(); }
  Iterator end() { return RBTree<_Key,_Key>::end(); }

  Iterator find(const _Key &key) {
    return RBTree<_Key,_Key>::find(key);
  }

  template <typename  ...Args>
  std::vector<std::pair<Iterator,bool>> insert_many(Args&&... args){
      std::vector<std::pair<Iterator,bool>> vec;
      (vec.push_back({insert(args),true}),...);
      return vec;
  }

};
}