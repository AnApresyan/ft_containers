// #include "vector.hpp"
#include <vector>
#include <iostream>
#include <ar.h>
#include "rb_tree.hpp"
#include "rbt_helper.hpp"
#include "map.hpp"


int main()
{
    ft::pair<int, char> p1(10, 'a');

    ft::map<int, char> map;

    map.insert(p1);

    for (ft::rbt_iterator<ft::pair<const int, char> > it = map.begin(); it != map.end(); it++)
    {
        std::cout << it->first << std::endl;

    }    

    // ft::pair<int, char> p2(12, 'b');
    // ft::pair<int, char> p3(9, 'c');
    // ft::pair<int, char> p4(7, 'd');
    // ft::pair<int, char> p5(4, 'e');
    // ft::pair<int, char> p6(20, 'e');

    // ft::rb_tree<int, ft::pair<int, char>, ft::select_1st<ft::pair<int, char> > > tr;
    // tr.insert(p1);

    // // std::cout << (*tr.begin()).first << std::endl;

    // tr.insert(p2);
    // tr.insert(p3);
    // tr.insert(p6);
    // tr.insert(p2);
    // tr.insert(p3);
    // tr.insert(p3);
    // tr.insert(p6);
    // tr.insert(p1);
    // tr.insert(p4);
    // tr.insert(p4);
    // tr.insert(p2);

    // // int i = 0;
    // for (ft::rbt_iterator<ft::pair<int, char> > it = tr.begin(); it != tr.end(); it++)
    // {
    //     std::cout << (*it).first << std::endl;
    // }
}


// int main()
// {
    // // std::vector<int> vect;
    // std::vector<int> vect;

    // std::cout << *(vect.begin()) << std::endl;
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

    // std::vector<int>::iterator it = vect.begin();
    // for (size_t i = 0; i < vect.size(); i++)
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


	// const int start_size = 7;
	// ft::vector<int> vct(start_size, 20);
	// ft::vector<int> vct2;
	// ft::vector<int>::iterator it = vct.begin();

// }