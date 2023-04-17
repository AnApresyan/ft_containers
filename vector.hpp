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
				reserve(other.capacity());
				while (this->_size != other._size)
					push_back(other[this->_size]);
			}

			~vector() 
			{
				//std::cout << "In the destructor\n";
				//std::cout << "Size: " << _size << std::endl;
				//std::cout << "Capacity: " << _capacity << std::endl;
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
							// //std::cout << "Enters?\n";
							_alloc.destroy(_arr + i);
						}
						if (_capacity > 0)
							_alloc.deallocate(_arr, _capacity);
						// //std::cout << "reached here\n\n\n\n";
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
				if (n > _capacity)
					reserve(n);
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			void push_back (const value_type& val)
			{

				value_type copy = val;
				if (_capacity == 0)
				{
					_capacity = 1;
					_arr = _alloc.allocate(_capacity);
				}
				else if (_size == _capacity)
					reserve(_capacity * 2);
				// //std::cout << "Also here\n";
				_alloc.construct(_arr + _size, copy);
				// //std::cout << "Pushed " << (_arr + _size) << std::endl;
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
				// //std::cout << "Position: " << position.base() << std::endl;
				for (iterator it = end() - 1; it != position; it--)
				{
					// //std::cout << it.base() << std::endl;
					*it = *(it - 1);
				}
				// //std::cout << "HEREEEE\n";
				*position = copy;
				return begin() + offset;
    		}

			void insert(iterator position, size_type n, const T& val)
			{
				// //std::cout << "Should be here\n";
				if (n + size() > max_size())
					throw std::length_error("More than the max size.");
				value_type copy = val;
				size_t offset = position - begin();
				if (size() + n > _capacity)
				{
					// //std::cout << "Here\n";
					// reserve(size() + n);
					if (size() + n > 2*size())
						reserve(size() + n);
					else
						reserve(size()*2);
					position = begin() + offset;
				}
				if (position != end())
				{
					size_t initial_n = n;
					size_t shifted = end() - position - 1;
					while (offset + shifted + n >= size())
					{
						_alloc.construct(_arr + offset + shifted + n, *(position + shifted));
						if (shifted == 0)
							break;
						shifted--;
					}
					if (shifted != 0 || (shifted == 0 && offset + shifted + n < size()))
					{
						while (shifted >= 0)
						{
							*(position + shifted + n) = *(position + shifted);
							if (shifted == 0)
								break;
							shifted--;
						}
					}
					while (offset < size() && n > 0)
					{
						*position = copy;
						position++;
						offset++;
						n--;
					}
					while (n-- > 0)
					{
						_alloc.construct(_arr + offset, copy);
						offset++;
					}
					_size += initial_n;
				}
				else
				{
					// //std::cout << "Hopefully here\n";
					// //std::cout << "n: " << n << std::endl;
					while (n-- > 0)
					{
						_alloc.construct(_arr + _size, copy);
						_size++;
					}
					// _size += initial_n;
						// push_back(copy);
				}
				// while (n-- > 0)
				// {
				// 	insert(position, copy);
				// 	position++;
				// }
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
				// value_type copy = *first;
				size_t offset = position - begin();
				size_t n = ft::distance(first, last);
				
				if (n + size() > _capacity)
				{
					if (n + size() > 2 * size())
						reserve(n + size());
					else
						reserve(size() * 2);
				}
				// //std::cout << "Capacity " << _capacity << std::endl;
				position = begin() + offset;
				size_t shifted = end() - position - 1;
				if (position != end())
				{
					while (offset + shifted + n >= size())
					{
						_alloc.construct(_arr + offset + shifted + n, *(position + shifted));
						if (shifted == 0)
							break;
						shifted--;
					}
					if (shifted != 0 || (shifted == 0 && offset + shifted + n < size()))
					{
						while (shifted >= 0)
						{
							*(position + shifted + n) = *(position + shifted);
							if (shifted == 0)
								break;
							shifted--;
						}
					}
					while (offset < size() && first != last)
					{
						value_type copy = *(first++);
						*position = copy;
						position++;
						offset++;
					}
					while (first != last)
					{
						// value_type copy = *(first++);
						_alloc.construct(_arr + offset, *(first++));
						offset++;
					}
					_size += n;
				}
				else
				{
					// //std::cout << "here?\n";
					// value_type copy;
					while (first != last)
					{
						// //std::cout << "\n\n\nHEREEEE?" << std::endl;

						// //std::cout << ": " << std::endl;
							// try
							// {
							// 	// copy = *first;
							// 	//std::cout << "Axpor pes eli\n";
							// }
							// catch(const std::exception& e)
							// {
							// 	//std::cout << "CAUGHT\n";
							// 	//std::cout << "Size in the catch block: " << _size << std::endl;
							// 	throw e;
							// }
							// //std::cout << "Do you reach here?\n";
							try
							{
								 
								// //std::cout << "HERE?\n";
								// copy = static_cast<value_type>(*first);
								_alloc.construct(_arr + _size, *first);
								// //std::cout << "Construction done\n";
								_size++;
								first++;

							}
							catch(...)
							{
								
								// //std::cout << "AAAAAAAAAAAA\n";

								// //std::cout << "Size: " << _size << std::endl;
								// //std::cout << "Capacity: " << _capacity << std::endl;
								clear_deallocate();
								// //std::cout << "Here?\n";
								throw ;
							}

								
							

							// //std::cout << "HM\n";
							// //std::cout << "Size: " << _size << std::endl;
							// //std::cout << "Capacity: " << _capacity << std::endl;

							// if (first != last)
							// 	//std::cout << "Moving to the next\n";
							// //std::cout << "Hereeeeeee\n";
						// }
						// catch(...)
						// {
						// 	// clear();
						// 	//std::cout << "Capacity: " << capacity() << std::endl;
						// 	throw ;
						// }
						
					}
						//std::cout << "AFTER ELSE\n";
						// push_back(*(first++));
				}
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
				{
					// //std::cout << "Destroying " << _alloc.address(*first) << std::endl;
					_alloc.destroy(_alloc.address(*(first++)));
				}
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
				// //std::cout << "HMMMMM\n";
				if (_capacity > 0)
				{
					// //std::cout << "Here\n";
					this->_alloc.deallocate(_arr, capacity());
					_capacity = 0;
					// //std::cout << "VVVVVV\n";
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