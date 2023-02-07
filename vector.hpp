#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

// #include <memory>
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include <memory>
#include <iostream>
#include "type_traits.hpp"

namespace ft 
{
	template <class T, class Alloc = std::allocator<T> > 
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

			explicit vector (const allocator_type& alloc = allocator_type()): _arr(NULL), _size(0), _capacity(0), _alloc(alloc){}

			
			explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type()): _size(0), _capacity(n), _alloc(alloc)
			{
				size_type i = 0;

				_arr = _alloc.allocate(n);
				try
				{
					for (; i < n; i++)
						push_back(val);
				}
				catch(std::exception &e)
				{	
					this->clear();
					this->_alloc.deallocate(this->_arr, i);
					throw e;
				}
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true): _size(0), _capacity(distance(first, last)), _alloc(alloc)
			{
				try 
				{
					_arr = _alloc.allocate(_capacity);
					for (; first != last; ++first)
						push_back(*first);
				} 
				catch (std::exception &e) 
				{
					this->clear();
					this->_alloc.deallocate(this->_arr, _size);
					throw e;
				}
			}

			vector(const vector &other): _size(0),  _capacity(other._capacity), _alloc(other._alloc)
			{
				this->_arr = this->_alloc.allocate(_capacity);
				while (this->_size != other._size)
					push_back(other[this->_size]);
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
				{
					while (n > _capacity)
						reserve(2 * _capacity);
					insert(iterator(end()), n - _size, val);
				}
			}

			size_type capacity() const
			{
				return _capacity;
			}
			bool empty() const
			{
				return (_size == 0);
			}

			// void reserve(size_type n) 
			// {
			// 	if (n > this->capacity()) {
			// 		size_type curr_size = this->size();
			// 		this->resize(n);
			// 		this->resize(curr_size);
			// 	}
			// }

			void reserve (size_type n)
			{
				if (n > _capacity)
				{
					pointer 	temp;
					size_type	i;

					// try
					// {
						temp = _alloc.allocate(n);
						for (i = 0; i < _size; i++)
						{	_alloc.construct(temp + i, _arr[i]);
							_alloc.destroy(_arr + i);		//if try catch needed move to the bottom
						}
					// }
					// catch(...)
					// {
					// 	for (size_type j = 0; j < i; j++)
					// 		_alloc.destroy(_alloc.address(temp + i));
					// 	_alloc.deallocate(temp, n);
					// }
					// for (i = 0; i < _size; i++)
					_alloc.deallocate(_arr, _capacity);
					_capacity = n;
					_arr = temp;
				}
			}

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

			value_type* data()
			{
				return _arr;
			}

			const value_type* data() const
			{
				return _arr;
			}

			//modifiers
			template <class InputIterator>  
			void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)		//probably enable if the iterator is input iterator
			{
				clear();
				// std::cout << "\n\nPRINTING IN ASSIGN\n\n";
				// for (iterator it = begin(); it != end(); it++)
				// 	std::cout << *it << std::endl;
				while (first != last)
					push_back(*(first++));
			}

			void assign (size_type n, const value_type& val)
			{
				clear();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			void push_back (const value_type& val)
			{
				if (_capacity == 0)
				{
					_capacity = 18;
					_arr = _alloc.allocate(_capacity);
				}
				else if (_size == _capacity)
					reserve(_capacity * 2);
				// std::cout << "Size: " << _size << std::endl;
				// std::cout << "Capacity: " << _capacity << std::endl;
				// std::cout << "Pushing: " << val << std::endl; 
				// std::cout << "Here" << std::endl;
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
				size_t offset = position - begin();
				value_type copy = val;

				push_back(copy);
				for (iterator it = end() - 1; it != position; it--)
				{
					std::cout << *it << std::endl;
					break;
					*(it) = *(it - 1);
				}	
				*(position) = copy;
				return begin() + offset;
    		}

			void insert(iterator position, size_type n, const T& val)
			{
				//size_t offset = position - begin();

				resize(size() + n);
				value_type copy = val;
				while (n-- > 0)
					insert(position++, copy);
   			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
			{
				for (; first != last; first++)
					position = insert(position, *first);
			}

			// iterator erase(iterator first, iterator last)
			// {
			// 	iterator it = first;
			// 	while (last != this->end()) 
			// 	{
			// 		*it = *last;	
			// 		it++;
			// 		last++;
			// 	}
			// 	//resize(this->size() - (last - first));
			// 	return first;
			// }

			iterator erase (iterator position)
			{
				return (this->erase(position, position + 1));
			}
			
			iterator erase (iterator first, iterator last)
			{
				int count = last - first;
				size_type ret = first - begin();
				
				while (last != end())
					*(first++) = *(last++);
				_size -= count;
				while (count-- > 0)
					_alloc.destroy(_alloc.address(*(first++)));
				return (begin() + ret);
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