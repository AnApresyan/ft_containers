#ifndef ITERATOR_H
#define ITERATOR_H

#include <iterator>

namespace ft
{
	template <class Iterator> 
	struct iterator_traits
	{
		typedef typename Iterator::difference_type 		difference_type;
		typedef typename Iterator::value_type 			value_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference 			reference;
		typedef typename Iterator::iterator_category 	iterator_category;
	};


	template <class T> 
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T* 								pointer;
		typedef T& 								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};


	template <class T> 
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T* 						pointer;
		typedef const T& 						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class Iterator> 
	class reverse_iterator
	{
		private:
			Iterator _base;
		public: 
			typedef 		 Iterator 										iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

			reverse_iterator(): _base() {}
			explicit reverse_iterator (iterator_type it): _base(it) {}
			template <class Iter>  
			reverse_iterator (const ft::reverse_iterator<Iter>& rev_it): _base(rev_it._base);

			iterator_type base() const
			{
				return _base;
			}
			reference operator*() const
			{
				return *(--_base);
			}
			reverse_iterator operator+(difference_type n) const
			{
				return ft::reverse_iterator(_base - n);
			}
			reverse_iterator& operator++()
			{
				_base--;
				return (*this);
			}
			reverse_iterator  operator++(int)
			{
				ft::reverse_iterator temp = *this;
  				++(*this);
  				return temp;
			}
			reverse_iterator& operator+=(difference_type n)
			{
				_base -= n;
				return (*this);
			}
			reverse_iterator operator-(difference_type n) const
			{
				return ft::reverse_iterator(_base + n);
			}
			reverse_iterator& operator--()
			{
				_base++;
				return (*this);
			}
			reverse_iterator  operator--(int)
			{
				ft::reverse_iterator temp = *this;
  				--(*this);
  				return temp;
			}
			reverse_iterator& operator-=(difference_type n)
			{
				_base += n;
				return (*this);
			}
			pointer operator->() const
			{
				return &(operator*());
			}
			reference operator[](difference_type n) const
			{
				return (base()[-n-1]);
			}
	};
	template <class Iterator>  
	bool operator==(const ft::reverse_iterator<Iterator>& lhs,const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool operator!= (const ft::reverse_iterator<Iterator>& lhs,const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class Iterator>
	bool operator<(const ft::reverse_iterator<Iterator>& lhs,const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	bool operator>(const ft::reverse_iterator<Iterator>& lhs,const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	bool operator<=(const ft::reverse_iterator<Iterator>& lhs,const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator>
	bool operator>=(const ft::reverse_iterator<Iterator>& lhs,const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= 	rhs.base());
	}
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n,const ft::reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}
	template <class Iterator>
	reverse_iterator<Iterator> operator-(typename ft::reverse_iterator<Iterator>::difference_type n,const ft::reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it - n);
	}
};

#endif
