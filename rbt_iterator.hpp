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
			friend bool operator==(const ft::rbt_iterator<T1>& lhs,const ft::rbt_iterator<T1>& rhs);
			
			template <typename T1>  
			friend bool operator!=(const ft::rbt_iterator<T1>& lhs,const ft::rbt_iterator<T1>& rhs);
			
			template <typename T1>  
			friend class const_rbt_iterator;

			template <typename T1>  
			friend bool operator==(const ft::const_rbt_iterator<T1>& lhs,const ft::rbt_iterator<T1>& rhs);
			
			template <typename T1>  
			friend bool operator==(const ft::rbt_iterator<T1>& lhs,const ft::const_rbt_iterator<T1>& rhs);
			
			template <typename T1>  
			friend bool operator!=(const ft::const_rbt_iterator<T1>& lhs,const ft::rbt_iterator<T1>& rhs);
			
			template <typename T1>  
			friend bool operator!=(const ft::rbt_iterator<T1>& lhs,const ft::const_rbt_iterator<T1>& rhs);

			template <class K1, class T1, class KOV1, class C1, class A1>
			friend class rb_tree;
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
				// return _node->element;
				return ((static_cast<rb_node<T>*>(_node))->element);
			}

			rbt_iterator& operator++()
			{
				// std::cout << "\nIncrementing started\n";
				// std::cout << _node->right->element.first << std::endl;
				// std::cout << "\n\n\nBefore\n";
				if (is_internal(_node->right))
				{
					// std::cout << "\nFirst if\n" << std::endl;
					_node = _node->right;
					while (is_internal(_node->left))
						_node = _node->left;
				}
				else if (is_internal(_node->p))
				{
					// std::cout << "\nSecond if\n" << std::endl;
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
					_node = _node->left;
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
					_node = _node->p;
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
				// else
				// 	_node = _node->right;
				return (*this);
			}

			rbt_iterator  operator--(int)
			{
				ft::rbt_iterator<T> temp = *this;
  				--(*this);
  				return temp;
			}
			
			// operator rbt_iterator<const T> ()
			// {
			// 	return (rbt_iterator<const T>(_node));
			// }

			private:
				bool is_internal(const rb_base_node *n)
				{
					// std::cout << "Is internal: " << n << std::endl; 
					// // if (n)
					// // 	std::cout << "First condition holds\n";
					// // if (n->left)
					// // 	std::cout << "Second condition holds\n";
					// // std::cout << (static_cast<const rb_node<T>*>(n)->left)->element.first;
					// return (n && n->left && n->right);
					return (!is_external(n));
				}

				bool is_external(const rb_base_node *n)
				{
					// std::cout << n->left << std::endl;
					return (n && !n->left);
				}
	};

	template <typename T> 
	class const_rbt_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		private:
			template <typename T1, typename T2>  
			friend bool operator==(const ft::const_rbt_iterator<T1>& lhs,const ft::const_rbt_iterator<T2>& rhs);
			
			template <typename T1, typename T2>  
			friend bool operator!=(const ft::const_rbt_iterator<T1>& lhs,const ft::const_rbt_iterator<T2>& rhs);
			
			template <class K1, class T1, class KOV1, class C1, class A1>
			friend class rb_tree;
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
				// return _node->element;
				// std::cout << "\n\nOf aman esim e 2.1\n\n";
				return (static_cast<const rb_node<T>*>(this->_node)->element);

			}

			const_rbt_iterator& operator++()
			{
				// std::cout << (static_cast<const rb_node<T>*>(_node->p))->element.first;
				if (is_internal(_node->right))
				{
					_node = _node->right;
					while (is_internal(_node->left))
						_node = _node->left;
				}
				else if (is_internal(_node->p))
				{
					// std::cout << "WTFFF\n";
					if (_node == _node->p->left)
					{
						// std::cout 
						_node = _node->p;
					}             
					else
					{
						while (is_internal(_node->p) && _node == _node->p->right)
							_node = _node->p;
						_node = _node->p;
						// std::cout << "Of de aman esim e\n";
						// std::cout << (static_cast<const rb_node<T>*>(_node))->element.first;

					}
				}
				else
				{
					// std::cout << "of de aman esim e 2.0\n";
					_node = _node->right;
				}
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
				// std::cout << "\nof aman esim e\n";
				if (!is_internal(_node))
				{
					// std::cout << "\nMtaaaavvv\n";
					_node = _node->p;
				// std::cout << "Paaaaarent: " <<(static_cast<const rb_node<T>*>(_node))->element.first << std::endl;
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
				// else
				// 	_node = _node->left;
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
					// std::cout << "Is internal: " << n << std::endl; 
					// // if (n)
					// // 	std::cout << "First condition holds\n";
					// // if (n->left)
					// // 	std::cout << "Second condition holds\n";
					// // std::cout << (static_cast<const rb_node<T>*>(n)->left)->element.first;
					// return (n && n->left && n->right);
					return (!is_external(n));
				}

				bool is_external(const rb_base_node *n)
				{
					// std::cout << n->left << std::endl;
					return (n && !n->left);
				}
	};

	template <typename T, typename U>  
	bool operator==(const ft::rbt_iterator<T>& lhs,const ft::rbt_iterator<U>& rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <typename T, typename U>
	bool operator!=(const ft::rbt_iterator<T>& lhs,const ft::rbt_iterator<U>& rhs)
	{
		return (lhs._node != rhs._node);
	}

	template <typename T1>  
	 bool operator==(const ft::const_rbt_iterator<T1>& lhs,const ft::rbt_iterator<T1>& rhs)
	 {
		return (lhs._node == rhs._node);
	 }
	
	template <typename T1>  
	 bool operator==(const ft::rbt_iterator<T1>& lhs,const ft::const_rbt_iterator<T1>& rhs)
	 {
		return (lhs._node == rhs._node);

	 }
	
	template <typename T1>  
	bool operator!=(const ft::const_rbt_iterator<T1>& lhs,const ft::rbt_iterator<T1>& rhs)
	{
	return (lhs._node != rhs._node);
 	}
	
	template <typename T1>  
	bool operator!=(const ft::rbt_iterator<T1>& lhs,const ft::const_rbt_iterator<T1>& rhs)
	{
		return (lhs._node != rhs._node);
	}

	template <typename T, typename U>  
	bool operator==(const ft::const_rbt_iterator<T>& lhs,const ft::const_rbt_iterator<U>& rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <typename T, typename U>
	bool operator!=(const ft::const_rbt_iterator<T>& lhs,const ft::const_rbt_iterator<U>& rhs)
	{
		return (lhs._node != rhs._node);
	}
};

#endif
