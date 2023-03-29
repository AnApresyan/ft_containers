// #include "vector.hpp"
#include <vector>
#include <iostream>
#include <ar.h>
#include "rb_tree.hpp"
#include "rbt_helper.hpp"
#include "map.hpp"
#include "set.hpp"
#include <sstream>
#include "vector.hpp"
#include "stack.hpp"


int main()
{
    //1 leak in the stack
    
    // std::cout << "Size: " << st.size() << std::endl;
    ft::vector<char> v;
    std::vector<char> v1;

    std::cout << "ft::vector max_size: " << v.max_size() << std::endl;
    std::cout << "std::vector max_size: " << v1.max_size() << std::endl;

    std::cout << "Size max: " << SIZE_MAX << std::endl;
    std::cout << "ptrdiff_t: " << PTRDIFF_MAX << std::endl;



    //Works with input iterators
    // std::istringstream str("1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    // std::istreambuf_iterator<char> it(str), end;

    // ft::vector<char> v(it, end);
    // std::cout << "Size: " << v.size() << std::endl;

    //Vector length exceeding max size
    // ft::vector<int> v;
    // std::cout << "Max size: " << v.max_size() << std::endl;

    // ft::vector<int> another(v.max_size() + 1);


    //Deallocating non-allocated memory
    // std::istringstream str("");
    // std::istreambuf_iterator<char> it(str), end;

    // ft::vector<char> v(it, end);

    //Memory leak in vector
    // ft::vector<int> v;

    // v.insert(v.end(), 10, 64);
        // v.insert(v.begin(), 0, 64);

        // // CHECK_AND_PRINT_ALL(v);

        // v.insert(v.end(), 0, 64);

        // CHECK_AND_PRINT_ALL(v);

        // v.insert(v.end(), 10, 64);

        // CHECK_AND_PRINT_ALL(v);

        // v.insert(v.begin(), 5, -1);

        // // CHECK_AND_PRINT_ALL(v);

        // v.insert(v.begin() + 1, 1, -9);

        // CHECK_AND_PRINT_ALL(v);

        // v.insert(v.begin() + 7, 9, 88);
        // std::cout << "Begin: " << *v.begin() << std::endl;
        // for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++)
        //     std::cout << *it << std::endl;
        // std::cout << "Size: " << v.size() << std::endl;


    // std::string str_arr[7] = {"QE", "na", "25", "tS", "7Z", "Wh", "8v"};

    // ft::set<std::string> m(str_arr, str_arr + 6);
    // for (ft::set<std::string>::iterator it = m.begin(); it != m.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }
    // ft::set<std::string> m;

    // m.insert("QE");
    // ft::set<std::string>::iterator it = m.find("ABCD");
    // m.insert("QE");



    // ft::pair<int, char> p1(10, 'a');

    // ft::map<int, char> map;

    // map.insert(p1);

    // for (ft::rbt_iterator<ft::pair<const int, char> > it = map.begin(); it != map.end(); it++)
    // {
    //     std::cout << it->first << std::endl;

    // }    

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