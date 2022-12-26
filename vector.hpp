#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>

namespace ft 
{
	template < class T, class Alloc = std::allocator<T> > 
	class vector
	{
		public: 
			//typedef
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef value_type &reference;
			typedef const value_type &const_reference;
			typedef value_type *pointer;
			typedef const value_type *const_pointer;
			typedef size_t size_type;

			//Capacity
			size_type size() const;
			



		private: 
			size_type _size;
			size_type _capacity;

	};
};

#endif