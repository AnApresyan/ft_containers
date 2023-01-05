#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Alloc>
	vector<T, Alloc>::vector(const allocator_type& alloc): _arr(NULL), _size(0), _capacity(0), _alloc(alloc) {}

	template <class T, class Alloc>
	vector<T, Alloc> (size_type n, const value_type& val, const allocator_type& alloc): _size(n), _capacity(n), _alloc(alloc)
	{
		try
		{
			_arr = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_arr + i, val);
		}
		catch(. . .)
		{
			//destroy
			//deallocate
			//_size = 0
			throw ;
		}
		
	}

}


#endif