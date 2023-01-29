#ifndef RANDOM_ACCESS_ITERATOR
#define RANDOM_ACCESS_ITERATOR

#include "iterator.hpp"

namespace ft
{
	template <typename T> 
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef ft::iterator<ft::random_access_iterator_tag, T> it;
			typedef typename it::difference_type 					difference_type;
			typedef typename it::value_type 						value_type;
			typedef typename it::pointer 							pointer;
			typedef typename it::reference 							reference;
			typedef typename it::iterator_category 					iterator_category;

			random_access_iterator(): ptr() {}
			random_access_iterator(random_access_iterator const &other): ptr(other.ptr) {}
			random_access_iterator(pointer p): ptr(p) {}							//Do I need this? If not what is the point of rai?
			virtual ~random_access_iterator() {}

			random_access_iterator &operator=(random_access_iterator const &other)
			{
				ptr = other.ptr;
				return (*this);
			}

			pointer	base() const
			{
				return ptr;
			}

			reference operator*() const
			{
				return *ptr;
			}

			pointer operator->() const
			{
				return ptr;
			}

			random_access_iterator operator+(difference_type n) const
			{
				return ft::random_access_iterator<T>(ptr + n);
			}
			random_access_iterator& operator++()
			{
				ptr++;
				return (*this);
			}
			random_access_iterator  operator++(int)
			{
				ft::random_access_iterator<T> temp = *this;
  				++(*this);
  				return temp;
			}
			random_access_iterator& operator+=(difference_type n)
			{
				ptr += n;
				return (*this);
			}
			random_access_iterator operator-(difference_type n) const
			{
				// iterator tmp(*this);
				// tmp.ptr += n;
				return ft::random_access_iterator<T>(ptr - n);
			}
			random_access_iterator& operator--()
			{

				ptr--;
				return (*this);
			}
			random_access_iterator  operator--(int)
			{
				ft::random_access_iterator<T> temp = *this;
  				--(*this);
  				return temp;
			}
			random_access_iterator& operator-=(difference_type n)
			{
				ptr -= n;
				return (*this);
			}

			reference operator[](difference_type n) const
			{
				return (ptr[n]);
			}

		protected:
			pointer ptr;
	};
	template <typename T>  
	bool operator==(const ft::random_access_iterator<T>& lhs,const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.ptr == rhs.ptr);
	}
	template <typename T>
	bool operator!=(const ft::random_access_iterator<T>& lhs,const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.ptr != rhs.ptr);
	}
	template <typename T>
	bool operator<(const ft::random_access_iterator<T>& lhs,const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.ptr > rhs.ptr);
	}
	template <typename T>
	bool operator>(const ft::random_access_iterator<T>& lhs,const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.ptr < rhs.ptr);
	}
	template <typename T>
	bool operator<=(const ft::random_access_iterator<T>& lhs,const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.ptr >= rhs.ptr);
	}
	template <typename T>
	bool operator>=(const ft::random_access_iterator<T>& lhs,const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.ptr <= 	rhs.ptr);
	}
	template <typename T>
	random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n,const ft::random_access_iterator<T>& rand_it)
	{
		return (rand_it + n);
	}
	template <typename T>
	random_access_iterator<T> operator-(typename ft::random_access_iterator<T>::difference_type n,const ft::random_access_iterator<T>& rand_it)
	{
		return (rand_it - n);
	}	
}

#endif