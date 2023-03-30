// #include <iostream>
// #include <string>
// #include <deque>
// #if 1 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
// 	#include <map.hpp>
// 	#include <stack.hpp>
// 	#include <vector.hpp>
// #endif

// #include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };


// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	ft::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}
	
// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }





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
	//Volodya's tester
	// const std::string       vec_example17(double &_time)
	// {
		std::ostringstream      ss;

		ft::vector<int> vec(5, int(42));
		ss << " " << vec.capacity();
		ss << " " << vec.size();
		for (size_t i = 0; i < vec.size(); ++i)
				ss << ' ' << vec[i];
		vec.assign(11, 48);
		ss << " " << vec.capacity();
		ss << " " << vec.size();
		for (size_t i = 0; i < vec.size(); ++i)
				ss << ' ' << vec[i];
		vec.assign(3, 21);
		ss << " " << vec.capacity();
		ss << " " << vec.size();
		for (size_t i = 0; i < vec.size(); ++i)
				ss << ' ' << vec[i];
		vec.assign(0, 2);
		ss << " " << vec.capacity();
		ss << " " << vec.size();
		for (size_t i = 0; i < vec.size(); ++i)
				ss << ' ' << vec[i];
		// _time = 0;
		std::cout << ss.str();
	// }



    //1 leak in the stack
    
    // std::cout << "Size: " << st.size() << std::endl;
    // ft::vector<char> v;
    // std::vector<char> v1;

    // std::cout << "ft::vector max_size: " << v.max_size() << std::endl;
    // std::cout << "std::vector max_size: " << v1.max_size() << std::endl;

    // std::cout << "Size max: " << SIZE_MAX << std::endl;
    // std::cout << "ptrdiff_t: " << PTRDIFF_MAX << std::endl;



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