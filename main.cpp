#include "tree.hpp"


int main(){

    mystl::RBTree<int, int> a,b;

    a.insert({123,13});
    a.insert({12,13});
    a.insert({121,13});
  
    b.insert({1111,13});
    b.insert({1,13});
    b.insert({2,13});
  
    for(auto it = a.begin(); it !=a.end();++it){
       std::cout << it->first<< " ";
    }
    std::cout <<'\n';

    for(auto it = b.begin(); it !=b.end();++it){
       std::cout << it->first<< " ";
    }
    std::cout <<'\n';
    a.merge(b);
    for(auto it = a.begin(); it !=a.end();++it){
       std::cout << it->first<< " ";
    }

}