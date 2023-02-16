#ifndef HELPER_HPP
# define HELPER_HPP

# include "iterator.hpp"

namespace ft
{	
	template <class T> 
	void sswap(T& a, T& b)
	{
		T copy;

		copy = a;
		a = b;
		b = copy;
	}

	template <typename InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first)
			++n;
		return n;
	}
};

#endif