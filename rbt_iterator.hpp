#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

# include "iterator.hpp"
# include "rb_node.hpp"

namespace ft
{
	template <typename T> 
	class rbt_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		private:
			rb_node<T> *_node;
		public:
			typedef ft::iterator<std::bidirectional_iterator_tag, T>	it;
			typedef typename it::difference_type 						difference_type;
			typedef typename it::value_type 							value_type;
			typedef typename it::pointer 								pointer;
			typedef typename it::reference 								reference;
			typedef typename it::iterator_category 						iterator_category;	
	
			rbt_iterator(): _node() {}
			rbt_iterator(const rbt_iterator &other): _node(other._node) {}
			rbt_iterator(rb_node<T> *other): _node(other) {}							//Do I need this? If not what is the point of rai?
			virtual ~rbt_iterator() {}

			rbt_iterator &operator=(const rbt_iterator &other)
			{
				_node = other._node;
				return (*this);
			}

			pointer operator->() const
			{
				return *(_node->element);		//how does this work?
			}

			reference operator*() const
			{
				return _node->element;
			}

			rbt_iterator& operator++()
			{
				if (is_internal(_node->right))
				{
					_node = _node->right;
					while (is_internal(_node->left))
						_node = _node->left;
				}
				else if (_node->p)
				{
					if (_node == _node->p->left)
						_node = _node->p;
					else
					{
						while (_node->p && _node == _node->p->right)
							_node == _node->p;
						_node = _node.p;
					}
				}
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
				if (is_internal(_node->left))
				{
					_node = _node->left;
					while (is_internal(_node->right))
						_node = _node->right;
				}
				else if (_node->p)
				{
					if (_node == _node->p->right)
						_node = _node->p;
					else
					{
						while (_node->p && _node == _node->p->left)
							_node == _node->p;
						_node = _node.p;	
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
			
			operator rbt_iterator<const T> ()
			{
				return (rbt_iterator<const T>(_node));
			}

			private:
				bool is_internal(const rb_node<T> *n)
				{
					return (n && n.left && n.right);
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
};

#endif
