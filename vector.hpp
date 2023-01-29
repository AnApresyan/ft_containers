#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

// #include <memory>
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include <memory>
#include <iostream>

namespace ft 
{
	template <class T, class Alloc = std::allocator<T>> 
	class vector
	{
		public: 
			//typedef
			typedef T 														value_type;
			typedef Alloc 													allocator_type;
			typedef value_type												&reference;
			typedef const value_type										&const_reference;
			typedef value_type 												*pointer;
			typedef const value_type										*const_pointer;
			typedef ft::random_access_iterator<value_type>					iterator;
			typedef ft::random_access_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;	
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t size_type;

			explicit vector (const allocator_type& alloc = allocator_type()): _size(0), _alloc(alloc), _capacity(5)
			{
				std::cout << "Here 0" << std::endl;
				_arr = _alloc.allocate(_capacity);
			}

			explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type()): _size(0)
			{
				_arr = _alloc.allocate(n);
				_capacity = n;
				try
				{
					for (size_type i = 0; i < n; i++)
						push_back(val);
				}
				catch(...)
				{	
					this->clear();
					this->_alloc.deallocate(this->_arr, n);
					throw ;
				}
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename std::enable_if<!is_integral<InputIterator>::value, bool>::type): _alloc(alloc), _size(ft::distance(first, last))
			{
				try 
				{
					_arr = m_alloc.allocate(_size);
					for (size_type i = 0; first != last; ++first, ++i)
						m_alloc.construct(_arr + i, *first);
				} 
				catch (const std::bad_alloc& e) 
				{
					this->clear();
					this->_alloc.deallocate(this->_arr, n);
					throw e;
				}
			}

			//Iterators
			iterator begin()
			{
				return iterator(_arr);
			}
			const_iterator begin() const
			{
				return const_iterator(_arr);
			}
			iterator end()
			{
				return iterator(_arr + _size);
			}
			const_iterator end() const
			{
				return const_iterator(_arr + _size);
			}
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}
			

			//Capacity
			size_type size() const
			{
				return _size;
			}
			size_type max_size() const
			{
				return _alloc.max_size();
			}
			
			void resize (size_type n, value_type val = value_type())
			{
				size_type tmp = _size;
				
				if (n < _size)
					for (size_type i = n; i < tmp; i++)
						pop_back();
				if (n > _size)
					while (n > _capacity)
						reserve(2 * _capacity);
					insert(iterator(end()), n - _size, val);
			}

			size_type capacity() const
			{
				return _capacity;
			}
			bool empty() const
			{
				return (_size == 0);
			}

			void reserve(size_type n) 
			{
				if (n > this->capacity()) {
					size_type curr_size = this->size();
					this->resize(n);
					this->resize(curr_size);
				}
			}
			// void reserve (size_type n)
			// {
			// 	if (n > _capacity)
			// 	{
			// 		pointer 	temp;
			// 		size_type	i;

			// 		// try
			// 		// {
			// 			temp = _alloc.allocate(n);
			// 			for (i = 0; i < _size; i++)
			// 			{	_alloc.construct(temp + i, _arr[i]);
			// 				_alloc.destroy(_arr + i);		//if try catch needed move to the bottom
			// 			}
			// 		// }
			// 		// catch(...)
			// 		// {
			// 		// 	for (size_type j = 0; j < i; j++)
			// 		// 		_alloc.destroy(_alloc.address(temp + i));
			// 		// 	_alloc.deallocate(temp, n);
			// 		// }
			// 		// for (i = 0; i < _size; i++)
			// 		_alloc.deallocate(_arr, _capacity);
			// 		_capacity = n;
			// 		_arr = temp;
			// 	}
			// }

			//element access
			reference operator[] (size_type n)
			{
				return _arr[n];
			}
			
			const_reference operator[] (size_type n) const
			{
				return _arr[n];
			}

			reference at (size_type n)
			{
				if (n < _size)
					return _arr[n];
				throw std::out_of_range("Given index is out of range");
			}

			const_reference at (size_type n) const
			{
				if (n < _size)
					return _arr[n];
				throw std::out_of_range("Given index is out of range");
			}

			reference front()
			{
				return _arr[0];
			}
			
			const_reference front() const
			{
				return _arr[0];
			}
			reference back()
			{
				return _arr[_size - 1];
			}

			const_reference back() const
			{
				return _arr[_size - 1];
			}

			value_type* data() noexcept
			{
				return _arr;
			}

			const value_type* data() const noexcept
			{
				return _arr;
			}

			//modifiers
			template <class InputIterator>  
			void assign (InputIterator first, InputIterator last)		//probably enable if the iterator is input iterator
			{
				clear();
				while (first++ != last)
					push_back(&first);
			}

			void assign (size_type n, const value_type& val)
			{
				clear();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			void push_back (const value_type& val)
			{
				if (_size == _capacity)
					reserve(_capacity * 2);
				_alloc.construct(_arr + _size, val);
				_size++;
			}

			void pop_back()
			{
				_alloc.destroy(_arr + (--_size));
				_size--;
			}

			iterator insert(iterator position, const T& val) 
			{
				size_t pos = position - _arr;
				push_back(val);
				for (iterator i = end() - 1; i != _arr + pos; --i)
					*(i) = *(i - 1);
				*(_arr + pos) = val;
				return _arr + pos;
    		}

			void insert(iterator position, size_type n, const T& val)
			{
				size_t pos = position - _arr;
				size_t currentSize = size();
				resize(currentSize + n);
				for (size_t i = currentSize - 1; i >= pos; --i)
					_arr[i + n] = _arr[i];
				for (size_t i = pos; i < pos + n; ++i)
					_arr[i] = val;
   			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last)
			{
				iterator &vec = *this;
				size_t new_size = 0;
				for (InputIterator it = first; it != last; it++)
					new_size++;
				size_t old_size = vec.size();
				size_t pos = position - vec.begin();
				vec.resize(old_size + new_size);
				for(size_t i = old_size - 1; i >= pos; i--)
					vec[i + new_size] = vec[i];
				for(size_t i = 0; i < new_size; i++)
					vec[pos + i] = *(first + i);
			}

			iterator erase(iterator first, iterator last)
			{
				iterator it = first;
				while (last != this->end()) 
				{
					*it = *last;
					it++;
					last++;
				}
				resize(this->size() - (last - first));
				return first;
			}

			void clear() 
			{
				this->erase(this->begin(), this->end());
			}

		private:
			pointer			_arr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

	};

	template <typename InputIterator>
	typename std::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		typename std::iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first)
			++n;
		return n;
	}
};

#endif