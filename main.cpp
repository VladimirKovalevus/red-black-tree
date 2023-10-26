#include "tree.hpp"
#include <utility>


int main(){

    mystl::RBTree<int, int> a({{4488,2},{8844,3}}),b;


    a.insert({123,13});
    a.insert({12,13});
    a.insert({121,13});
  
    auto vec = b.insert_many<std::pair<int, int>,std::pair<int, int>,std::pair<int, int>>({1111,13},{58,13},{63,13});
    for(int i =0;i<vec.size();i++){
      std::cout << vec[i].first->first<<" ";
      std::cout << vec[i].second<<" ";
    }
    std::cout <<'\n';
      
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