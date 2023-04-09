#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

// #include <memory>
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include <memory>
#include <iostream>
#include "type_traits.hpp"
#include "helper.hpp"
#include "algorithm.hpp"
#include <limits>

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

			explicit vector (const allocator_type& alloc = allocator_type()): _arr(), _size(0), _capacity(0), _alloc(alloc){}

			explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _alloc(alloc)
			{
				size_type i = 0;

				try
				{
					if (n > max_size())
						throw std::length_error("Exceeds max size.");
					if (n > 0)
					{
						_arr = _alloc.allocate(n);
						_capacity = n;
					}
					for (; i < n; i++)
						push_back(val);
				}
				catch(...)
				{
					this->clear();
					if (_capacity > 0)
						this->_alloc.deallocate(this->_arr, i);
					throw ;
				}
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true): _size(0), _capacity(0), _alloc(alloc)
			{
				try 
				{
					for (; first != last; ++first)
					{
						push_back(*first);
					}
				} 
				catch (std::exception &e) 
				{
						this->clear();
					if (_capacity > 0)
						this->_alloc.deallocate(this->_arr, _capacity);
					throw e;
				}
			}

			vector(const vector &other): _size(0),  _capacity(0), _alloc(other._alloc)
			{
				while (this->_size != other._size)
					push_back(other[this->_size]);
			}

			~vector() 
			{
				clear_deallocate();
			}

			vector& operator= (const vector& other)
			{
				this->assign(other.begin(), other.end());
				return (*this);
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
				return static_cast<size_type>(std::numeric_limits<ptrdiff_t>::max()) < this->_alloc.max_size() ? static_cast<size_type>(std::numeric_limits<ptrdiff_t>::max()) : this->_alloc.max_size();
			}
			
			void resize (size_type n, value_type val = value_type())
			{
				size_type tmp = _size;
				
				if (n < _size)
					for (size_type i = n; i < tmp; i++)
						pop_back();
				if (n > _size)
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

			void reserve (size_type n)
			{
				if (n > max_size())
					throw std::length_error("Length error.");
				if (n > _capacity)
				{
					pointer 	temp;
					size_type	i;

					try
					{
						temp = _alloc.allocate(n);
						for (i = 0; i < _size; i++)
						{	_alloc.construct(temp + i, _arr[i]);
							// std::cout << "Enters?\n";
							_alloc.destroy(_arr + i);
						}
						if (_capacity > 0)
							_alloc.deallocate(_arr, _capacity);
						_capacity = n;
						_arr = temp;
					}
					catch(...)
					{
						for (size_type j = 0; j < i; j++)
							_alloc.destroy(_alloc.address(*(temp + j)));
						_alloc.deallocate(temp, n);
						throw ;
					}
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
				throw std::out_of_range("Given index is out of range.");
			}

			const_reference at (size_type n) const
			{
				if (n < _size)
					return _arr[n];
				throw std::out_of_range("Given index is out of range.");
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
				assign_dispatch(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
			}

		private:
			template <class InputIterator>  
			void assign_dispatch (InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				clear();
				while (first != last)
					push_back(*(first++));
			}

			template <class InputIterator>  
			void assign_dispatch (InputIterator first, InputIterator last, std::forward_iterator_tag)
			{
				clear();

				size_type n = ft::distance(first, last);
				if (n > _capacity)
				{
					if (_capacity > 0)
						_alloc.deallocate(_arr, n);
					_capacity = n;
					_arr = _alloc.allocate(n);
				}
				while (first != last)
				{
					push_back(*first);
					first++;
				}
			}

		public:
			void assign (size_type n, const value_type& val)
			{
				clear();
				// if (n > _capacity)
				// {
				// 	if (_capacity > 0)
				// 		_alloc.deallocate(_arr, n);
				// 	_capacity = n;
				// 	_arr = _alloc.allocate(n);
				// }
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			void push_back (const value_type& val)
			{
				if (_capacity == 0)
				{
					_capacity = 1;
					_arr = _alloc.allocate(_capacity);
				}
				else if (_size == _capacity)
					reserve(_capacity * 2);
				_alloc.construct(_arr + _size, val);
				_size++;
			}

			void pop_back()
			{
				_alloc.destroy(_arr + (--_size));
			}

			iterator insert(iterator position, const T& val) 
			{
				size_t offset = position - begin();
				value_type copy = val;
				push_back(copy);
				position = begin() + offset;
				if (this->size() == 1)
					return this->begin();
				if (offset == _size - 1)
					return begin() + offset;
				// std::cout << "Position: " << position.base() << std::endl;
				for (iterator it = end() - 1; it != position; it--)
				{
					// std::cout << it.base() << std::endl;
					*it = *(it - 1);
				}
				// std::cout << "HEREEEE\n";
				*position = copy;
				return begin() + offset;
    		}

			void insert(iterator position, size_type n, const T& val)
			{
				// std::cout << "Should be here\n";
				if (n + size() > max_size())
					throw std::length_error("More than the max size.");
				value_type copy = val;
				size_t offset = position - begin();
				if (size() + n > _capacity)
				{
					// std::cout << "Here\n";
					reserve(size() + n);
					position = begin() + offset;
				}
				while (n-- > 0)
				{
					position = insert(position, copy);
					position++;
				}	
   			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
			{
				//
				insert_dispatch(position, first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
			}
		private:
			template <class InputIterator>
			void insert_dispatch(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				for (; first != last; first++)
				{	
					position = insert(position, *first);
					position++;
				}
			}

			template <class InputIterator>
			void insert_dispatch(iterator position, InputIterator first, InputIterator last, std::forward_iterator_tag)
			{
				// std::cout << "Before reserve: " << *first << std::endl;
				// std::cout << "Should be here\n";
				// std::cout << "Size" << size() << '\n';

				size_t offset = position - begin();
				// std::cout << "Offset: " << offset << std::endl;
				size_t n = ft::distance(first, last);
				// std::cout << "Distance: " << n << std::endl;
				if (n + size() > _capacity)
					reserve(n + size());
				position = begin() + offset;
				// std::cout << "Begin: " << *(begin() + 3) << std::endl;
				// std::cout << "Should work: " << *(position - 1) << std::endl;
				// std::cout << "After reserve: " << *first << std::endl;
				// for (iterator it = begin(); it != end(); it++)
				// 	std::cout << *it << std::endl;

				// for (iterator it = position; it != end(); it++)
				// 	std::cout << *it << std::endl;

				// for (size_t i = 0; position + i != end(); i++)
				// 	std::cout << *(position + i) << std::endl;
				// std::cout << "It: " << *it << std::endl;
				// if(position != end())
				// {
					// std::cout << "Enters here\n";
				size_t shifted = end() - position;
				// iterator it = position + shifted + n;
				// std::cout << "Shifted: " << shifted << '\n';

					// size_t add = size() + n;
					for(; last != first; last--)
					{
						// std::cout << "Position: " << *(position + shifted) << '\n';
						// if (position + i = end())
						// 	break;
						// std::cout << "Here: " << i << "\n";
						// std::cout << "Position + i: " << *(position + i) << '\n';
						// _alloc.construct(_arr + add, *(position + shifted));
						// add--;
						if (position != end())
						{
							*(position + shifted + n) = *(position + shifted);
							_alloc.destroy(_arr + offset + shifted);
							// if (shifted == 0)
							// 	break;
						}
						shifted--;
						// _size++;
						value_type copy = *last;
						// if (position != end())
						// 	_alloc.destroy(_arr + offset);
						//_alloc.destroy(_alloc.address(*(first++)));
						_alloc.construct(_arr + offset + shifted, copy);
						// *position = copy;
						// offset++;
						// position++;
						_size++;
						// break;
						// std::cout << "Inside loop: " << i << '\n';
				}
				// }
				// std::cout << "Here??????\n";
				// while (n-- > 0)
				// {
				// 	*(it--) = *(position + n);
				// }
				// for (; first != last; first++)
				// {	
				// 	value_type copy = *first;
				// 	// if (position != end())
				// 	// 	_alloc.destroy(_arr + offset);
				// 	//_alloc.destroy(_alloc.address(*(first++)));
				// 	_alloc.construct(_arr + offset, copy);
				// 	*position = copy;
				// 	// offset++;
				// 	position++;
				// 	// _size++;
				// }
				// std::cout << \n";
			}
	
		public:
			void swap (vector& x)
			{

				ft::sswap(this->_arr, x._arr);
				ft::sswap(this->_size, x._size);
				ft::sswap(this->_capacity, x._capacity);
			}

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
			
			allocator_type get_allocator() const
			{
				return (_alloc);
			}
		private:
			void clear_deallocate()
			{
				clear();
				if (_capacity > 0)
				{
					// std::cout << "Here\n";
					this->_alloc.deallocate(_arr, capacity());
				}
			}

		private:
			pointer			_arr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
	};

	template<class T, class Alloc>
	void swap (ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y)
	{
		x.swap(y);
	}

	template <class T, class Alloc>  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (size_t i = 0; i < lhs.size(); i++)
			if (*(lhs.begin() + i) != *(rhs.begin() + i))
				return (false);
		return (true);
	}
	
	template <class T, class Alloc>  
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}
	
	template <class T, class Alloc>  
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),rhs.begin(), rhs.end()));
	}
	
	template <class T, class Alloc>  
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}
	
	template <class T, class Alloc>  
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>  
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}


};

#endif