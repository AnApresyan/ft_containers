#include "vector.hpp"
// #include <vector>
#include <iostream>
#include <Iterator>

int main()
{
    // // std::vector<int> vect;
    // ft::vector<int> vect;
    // // ft::vector<int> vect(3, 10);
    // ft::vector<int> vect1(10);
    // std::cout << "Vect1 size: " << vect1.size() << std::endl;
    // for (int i = 0; i < vect1.size(); i++)
    //     std::cout << vect1[i] << ' ';
    // std::cout << vect.size() << std::endl;
    // // std::cout << vect.max_size() << std::endl;
    // // vect.reserve(5);
    // vect.push_back(10);
    // vect.push_back(11);
    // vect.push_back(12);
    // vect.push_back(13);
    // vect.push_back(14);
    // vect.push_back(15);
    // vect.push_back(16);
    // vect.push_back(17);
    // std::cout << "---------" << std::endl;
    // std::cout << "Size: " << vect.size() << std::endl;
    // std::cout << "Front: " << vect.front() << std::endl;
    // std::cout << "Back: " << vect.back() << std::endl;
    // vect.pop_back();
    // std::cout << "---------" << std::endl;
    // std::cout << "Size: " << vect.size() << std::endl;
    // std::cout << "Front: " << vect.front() << std::endl;
    // std::cout << "Back: " << vect.back() << std::endl;
    // for (int i = 0; i < vect.size(); i++)
    //     std::cout << vect[i] << ' ';
    // std::cout << std::endl;

    // vect.resize(5);
    // // vect.clear();
    // std::cout << "---------" << std::endl;
    // std::cout << "Size: " << vect.size() << std::endl;
    // std::cout << "Front: " << vect.front() << std::endl;
    // std::cout << "Back: " << vect.back() << std::endl;
    // for (int i = 0; i < vect.size(); i++)
    //     std::cout << vect[i] << ' ';
    // std::cout << std::endl;
    // // std::vector<int>::iterator it = vect.begin();

    // ft::vector<int>::iterator it = vect.begin();
    // for (int i = 0; i < vect.size(); i++)
    //     std::cout << it[i] << " ";
    // std::cout << std::endl;
    // it+=1;
    // std::cout << it[0] << std::endl;
    // it--;
    // std::cout << it[0] << std::endl;
    // it++;
    // std::cout << it[0] << std::endl;
    // it+=4;
    // std::cout << it[0] << std::endl;
    // it = it - 3;
    // std::cout << it[0] << std::endl;
    // std::cout << *it << std::endl;

    ft::vector<int> c1(3, 100);
    print(1, c1);
 
    auto it = c1.begin();
    it = c1.insert(it, 200);
    print(2, c1);
 
    c1.insert(it, 2, 300);
    print(3, c1);
 
    // `it` no longer valid, get a new one:
    it = c1.begin();
 
    ft::vector<int> c2(2, 400);
    c1.insert(std::next(it, 2), c2.begin(), c2.end());
    print(4, c1);
 
    int arr[] = {501, 502, 503};
    c1.insert(c1.begin(), arr, arr + std::size(arr));
    print(5, c1);
 
    c1.insert(c1.end(), {601, 602, 603});
    print(6, c1);

}