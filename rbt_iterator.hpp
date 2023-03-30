#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

# include "iterator.hpp"
# include "rb_node.hpp"
# include "rbt_helper.hpp"
# include <iostream>

namespace ft
{
	template<typename T>
	class const_rbt_iterator;

	template <typename T> 
	class rbt_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		private:
			template <typename T1>  
			friend class const_rbt_iterator;

			template <class K1, class T1, class KOV1, class C1, class A1>
			friend class rb_tree;

			template <typename T1>  
			friend bool operator==(const ft::rbt_iterator<T1>& lhs,const ft::rbt_iterator<T1>& rhs);
			
			template <typename T1>  
			friend bool operator==(const ft::const_rbt_iterator<T1>& lhs,const ft::rbt_iterator<T1>& rhs);
			
			template <typename T1>  
			friend bool operator==(const ft::rbt_iterator<T1>& lhs,const ft::const_rbt_iterator<T1>& rhs);

			rb_base_node *_node;
		public:
			typedef ft::iterator<std::bidirectional_iterator_tag, T>	it;
			typedef typename it::difference_type 						difference_type;
			typedef typename it::value_type 							value_type;
			typedef typename it::pointer 								pointer;
			typedef typename it::reference 								reference;
			typedef typename it::iterator_category 						iterator_category;	
	
			rbt_iterator(): _node() {}
			rbt_iterator(const rbt_iterator &other): _node(other._node) {}
			rbt_iterator(rb_base_node *other): _node(other) {}		
			virtual ~rbt_iterator() {}

			rbt_iterator &operator=(const rbt_iterator &other)
			{
				_node = other._node;
				return (*this);
			}

			pointer operator->() const
			{
				return ft::addressof(operator*());		
			}

			reference operator*() const
			{
				return ((static_cast<rb_node<T>*>(_node))->element);
			}

			rbt_iterator& operator++()
			{
				if (is_internal(_node->right))
				{
					_node = _node->right;
					while (is_internal(_node->left))
						_node = _node->left;
				}
				else if (is_internal(_node->p))
				{
					if (_node == _node->p->left)
						_node = _node->p;
					else
					{
						while (_node->p && _node == _node->p->right)
							_node = _node->p;
						_node = _node->p;
					}
				}
				else
					_node = _node->right;
				return (*this);
			}

			rbt_iterator  operator++(int)
			{
				ft::rbt_iterator<T> temp = *this;
  				++(*this);
  				return temp;
			}

			rbt_iterator& operator--()
			{
				if (!is_internal(_node))
				{
					_node = _node->p;
					return (*this);
				}	
				if (is_internal(_node->left))
				{
					_node = _node->left;
					while (is_internal(_node->right))
						_node = _node->right;
				}
				else if (is_internal(_node->p))
				{
					if (_node == _node->p->right)
						_node = _node->p;
					else
					{
						while (is_internal(_node->p) && _node == _node->p->left)
							_node = _node->p;
						_node = _node->p;	
					}
				}
				return (*this);
			}

			rbt_iterator  operator--(int)
			{
				ft::rbt_iterator<T> temp = *this;
  				--(*this);
  				return temp;
			}

			private:
				bool is_internal(const rb_base_node *n)
				{
					return (!is_external(n));
				}

				bool is_external(const rb_base_node *n)
				{
					return (n && !n->left);
				}
	};

	template <class T>
	bool	operator==(const rbt_iterator<T> &lhs, const rbt_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T>
	bool	operator!=(const rbt_iterator<T> &lhs, const rbt_iterator<T> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename T> 
	class const_rbt_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		private:
			template <class K1, class T1, class KOV1, class C1, class A1>
			friend class rb_tree;

			template <typename T1>  
			friend bool operator==(const ft::const_rbt_iterator<T1>& lhs,const ft::const_rbt_iterator<T1>& rhs);
			
			template <typename T1>  
			friend bool operator==(const ft::const_rbt_iterator<T1>& lhs,const ft::rbt_iterator<T1>& rhs);
			
			template <typename T1>  
			friend bool operator==(const ft::rbt_iterator<T1>& lhs,const ft::const_rbt_iterator<T1>& rhs);
			
			const rb_base_node *_node;
		public:
			typedef ft::iterator<std::bidirectional_iterator_tag, T>	it;
			typedef rbt_iterator<T>										iterator;
			typedef typename it::difference_type 						difference_type;
			typedef typename it::value_type 							value_type;
			typedef const T*			 								pointer;
			typedef const T&											reference;
			typedef typename it::iterator_category 						iterator_category;	
	
			const_rbt_iterator(): _node() {}
			const_rbt_iterator(const rb_base_node *other): _node(other) {}		
			const_rbt_iterator(const iterator &other): _node(other._node) {}
			
			virtual ~const_rbt_iterator() {}

			const_rbt_iterator &operator=(const iterator &other)
			{
				_node = other._node;
				return (*this);
			}

			pointer operator->() const
			{
				return ft::addressof(operator*());		
			}

			reference operator*() const
			{
				return (static_cast<const rb_node<T>*>(this->_node))->element;
			}

			const_rbt_iterator& operator++()
			{
				if (is_internal(_node->right))
				{
					_node = _node->right;
					while (is_internal(_node->left))
						_node = _node->left;
				}
				else if (is_internal(_node->p))
				{
					if (_node == _node->p->left)
						_node = _node->p;           
					else
					{
						while (is_internal(_node->p) && _node == _node->p->right)
							_node = _node->p;
						_node = _node->p;
					}
				}
				else
					_node = _node->right;
				return (*this);
			}

			const_rbt_iterator  operator++(int)
			{
				ft::const_rbt_iterator<T> temp = *this;
  				++(*this);
  				return temp;
			}

			const_rbt_iterator& operator--()
			{
				if (!is_internal(_node))
				{
					_node = _node->p;
					return (*this);
				}
				if (is_internal(_node->left))
				{
					_node = _node->left;
					while (is_internal(_node->right))
						_node = _node->right;
				}
				else if (is_internal(_node->p))
				{
					if (_node == _node->p->right)
						_node = _node->p;
					else
					{
						while (is_internal(_node->p) && _node == _node->p->left)
							_node = _node->p;
						_node = _node->p;	
					}
				}
				return (*this);
			}

			const_rbt_iterator  operator--(int)
			{
				ft::const_rbt_iterator<T> temp = *this;
  				--(*this);
  				return temp;
			}

			private:
				bool is_internal(const rb_base_node *n)
				{
					return (!is_external(n));
				}

				bool is_external(const rb_base_node *n)
				{
					return (n && !n->left);
				}
	};

	template <class T>
	bool	operator==(const const_rbt_iterator<T> &lhs, const const_rbt_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T>
	bool	operator!=(const const_rbt_iterator<T> &lhs, const const_rbt_iterator<T> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T>
	bool	operator!=(const rbt_iterator<T> &lhs, const const_rbt_iterator<T> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T>
	bool	operator!=(const const_rbt_iterator<T> &lhs, const rbt_iterator<T> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T>
	bool	operator==(const rbt_iterator<T> &lhs, const const_rbt_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T>
	bool	operator==(const const_rbt_iterator<T> &lhs, const rbt_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

};

#endif
