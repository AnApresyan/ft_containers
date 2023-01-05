#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

// #include <memory>
#include "iterator.hpp"
#include "random_access_iterator.hpp"

namespace ft 
{
	template <class T, class Alloc = std::allocator<T>> 
	class vector
	{
		public: 
			//typedef
			typedef T 												value_type;
			typedef Alloc 											allocator_type;
			typedef value_type										&reference;
			typedef const value_type								&const_reference;
			typedef value_type 										*pointer;
			typedef const value_type								*const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;	
			typedef itetator_traits<iterator>::difference_type		difference_type;
			typedef size_t size_type;

			explicit vector (const allocator_type& alloc = allocator_type());
			explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type());
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type());
			vector (const vector& other);

		private:
			pointer			_arr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

	};
};

#include "vector.tpp"

#endif