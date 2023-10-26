#include "tree.hpp"


int main(){

    mystl::RBTree<int, int> a;

    a.insert({123,13});
    a.insert({12,13});
    a.insert({121,13});
  
    a.insert({1111,13});
    a.insert({1,13});
    a.insert({2,13});
  
    for(auto it = a.begin(); it !=a.end();++it){
       std::cout << it->first<< " ";
    }

    std::cout<<"\n";

    auto fr = a.find(2);
    auto sc = a.find(1);

    a.erase(fr);
    a.erase(sc);

    sc=a.find(123);
    a[111]=123;
    a.at(111);
    for(auto it = a.begin(); it !=a.end();++it){
       std::cout << it->first<< " ";
    }
    std::cout <<'\n';
     for(auto it = a.begin(); it !=a.end();++it){
       std::cout << it->second<< " ";
    }

}