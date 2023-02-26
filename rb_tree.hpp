#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include "rbt_iterator.hpp"
# include <memory>
# include "rbt_helper.hpp"
# include "rb_node.hpp" 
# include "pair.hpp"

namespace ft
{

	template < class Key, class T, class KeyOfValue, class Compare = less<Key>, class Alloc = std::allocator<T> >
	class rb_tree 
	{
		public:
			typedef Key 									key_type;
			typedef T 										value_type;
			typedef Compare									key_compare;
			typedef Alloc 									allocator_type;
			typedef value_type& 							reference;
			typedef const value_type& 						const_reference;
			typedef value_type* 							pointer;
			typedef const value_type*						const_pointer;
			typedef ft::rbt_iterator<T> 					iterator;
			typedef ft::rbt_iterator<const T> 				const_iterator;
			typedef ft::reverse_iterator<iterator> 			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef ptrdiff_t 								difference_type;
			typedef size_t									size_type;
		private:
			typedef rb_node<T>	node;
			typedef typename Alloc::template rebind<node>::other	node_allocator_type; // what is thisss????
			
			node				_chief;
			node				_sentinel;
			size_type			_size;
			key_compare 		_comp;
			node_allocator_type	_alloc;
		
		public:
			//constructors
			explicit rb_tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _chief(), _sentinel(), _size(), _comp(comp), _alloc(alloc)
			{
				_chief.p = _sentinel;
				_chief.right = _sentinel;
				_chief.left = _sentinel;
				_chief.color = BLACK;
			}

			template <class InputIterator>
			rb_tree (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),const allocator_type& alloc = allocator_type())
			{
				_chief.p = _sentinel;
				_chief.right = _sentinel;
				_chief.left = _sentinel;
				_chief.color = BLACK;
				insert(first, last);
			}

			rb_tree (const rb_tree& x)
			{
				_chief.p = _sentinel;
				_chief.right = _sentinel;
				_chief.left = _sentinel;
				_chief.color = BLACK;
				insert(x.begin(), x.end());
			}
			
			//operator=
			rb_tree& operator=(const rb_tree& x)
			{
				//. . .
				return (*this);
			}

			//Iterators
			iterator begin()
			{
				return iterator(_chief.left);
			}

			const_iterator begin() const
			{
				return const_iterator(_chief.right);
			}

			iterator end()
			{
				return iterator(&_sentinel);
			}
			
			const_iterator end() const
			{
				return const_iterator(&_sentinel);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
			
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}

			//Capacity
			bool empty() const
			{
				return (_size == 0);
			}

			size_type size() const
			{
				return (_size);
			}

			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			//Modifiers

			pair<iterator,bool> insert (const value_type& val)
			{
				rb_node<T> *y = _sentinel;
				rb_node<T> *x = root();

				while (is_internal(x))
				{
					y = x;
					if (_comp(keyof(val), keyof(x)))
						x = x->left;
					else
						x = x->right;
				}
				if (!_comp(keyof(val), keyof(y)) && !_comp(keyof(y), keyof(val)))
					return (make_pair(iterator(y), false));
				rb_node<T> *z = create_node(val);
				z->p = y;
				if (is_external(y))
					_chief.p = z;
				else if (_comp(keyof(val), keyof(y)))
					y->left = z;
				else
					y->right = z;
				z->left = _sentinel;
				z->right = _sentinel;
				z->color = RED;
				_size++;
				if (_comp(keyof(val), keyof(_chief.left)))
					_chief.left = z;
				else if (_comp(keyof(_chief.right), keyof(val)))
					_chief.right = z;
				insert_fixup(z);
				return (make_pair(iterator(z), true));
			}

			iterator insert (iterator position, const value_type& val)
			{
				//for now I will disregard the hint
				return insert(val).first;
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first++ != last)
					insert(*first);
			}

			
			void swap (rb_tree& x)
			{
				ft::sswap(_chief, x._chief);
				ft::sswap(_size, x._size);
				ft::sswap(_sentinel, x._sentinel);
				ft::sswap(_alloc, x._alloc);
				ft::sswap(_comp, x._comp);
			}

			void clear()
			{

			}

			//Observers
			key_compare key_comp() const
			{
				return (_comp);
			}

			//Operations
			iterator find (const key_type& k)
			{
				if (empty())
					return (_sentinel);
				rb_node<T> *temp(root());
	
				while (is_internal(temp) && (_comp(keyof(temp), k) || _comp(k, keyof(temp))))
				{
					if (_comp(k, keyof(temp)))
						temp = temp.left;
					else
						temp = temp.right;
				}
				if (_comp(keyof(temp), k) || _comp(k, keyof(temp)))
					return (iterator(temp));
				return (end());
			}
			
			const_iterator find (const key_type& k) const
			{
				return const_iterator(find(k));		//how does this part work?????
			}

			size_type count (const key_type& k) const
			{
				if (is_internal(find(k)))
					return (1);
				return (0);
			}

			iterator lower_bound (const key_type& k)
			{
				if (empty())
					return (_sentinel);
				rb_node<T> *temp(root());
	
				while (is_internal(temp) && (_comp(keyof(temp), k) || _comp(k, keyof(temp))))
				{
					if (_comp(k, keyof(temp)))
					{
						if (is_external(temp->left))
							break;
						temp = temp->left;
					}	
					else
					{
						if (is_external(temp->right))
							break;
						temp = temp->right;
					}
				}
				if (_comp(keyof(temp), k))
					return ++iterator(temp);
				return iterator(temp);
			}

			const_iterator lower_bound (const key_type& k) const
			{
				return const_iterator(lower_bound(k));				//idkkkk how does this work(
			}

			iterator upper_bound (const key_type& k)
			{
				if (empty())
					return (_sentinel);
				rb_node<T> *temp(root());
	
				while (is_internal(temp) && (_comp(keyof(temp), k) || _comp(k, keyof(temp))))
				{
					if (_comp(k, keyof(temp)))
					{
						if (is_external(temp->left))
							break;
						temp = temp->left;
					}
					else
					{
						if (is_external(temp->right))
							break;
						temp = temp->right;
					}
				}
				return ++iterator(temp);
			}

			const_iterator upper_bound (const key_type& k) const
			{
				return const_iterator(upper_bound(k));
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (make_pair(lower_bound(k), upper_bound(k)));
			}
			
			pair<iterator,iterator> equal_range (const key_type& k)
			{
				return (make_pair(lower_bound(k), upper_bound(k)));
			}

			//Allocator
			allocator_type get_allocator() const
			{
				return (_alloc);
			}

			//destructor
			~rb_tree()
			{
				clear();
			}

		private:
			//helper functions
			rb_node<T> *min()
			{
				return (_chief->left);
			}
			
			rb_node<T> *max()
			{
				return (_chief->right);
			}

			node *root() const
			{
				return (_chief.p);
			}

			bool is_root(const node *n)
			{
				return (n && !n.p);
			}

			bool is_internal(const node *n)
			{
				return (!is_external(n));
			}

			bool is_external(const node *n)
			{
				return (!n || n == _sentinel);
			}
			
			bool is_chief(const node *n)
			{
				if (empty())
					return (true);
				else if (!(n.p).p)
					return (true);
				return (false);
			}

			void left_rotate(rb_node<T> *x)
			{
				if (is_external(x->right))
					return;
				rb_node<T> *y = x->right;
				x->right = y->left;
				if (is_internal(y->left))
					y->left->p = x;
				y->p = x->p;
				if (is_external(x->p))
					_chief->p = y;
				else if (x == x->p->left)
					x->p->left = y;
				else
					x->p->right = y;
				y->left = x;
				x->p = y;
			}

			void right_rotate(rb_node<T> *x)
			{
				if (is_external(x->left))
					return;
				rb_node<T> *y = x->left;
				x->left = y->right;
				if (is_internal(y->right))
					y->right->p = x;
				y->p = x->p;
				if (is_external(x->p))
					_chief->p = y;
				else if (x == x->p->right)
					x->p->right = y;
				else
					x->p->left = y;
				y->right = x;
				x->p = y;
			}

			Key keyof(rb_node<T> *x)
			{
				return (KeyOfValue()(x->element));
			}

			Key keyof(const value_type& val)
			{
				return (KeyOfValue()(val));
			}

			void insert_fixup(rb_node<T> *z)
			{
				while (z->p->color == RED)
				{
					if (z->p == z->p->p->left)
					{
						rb_node<T> *y = z->p->p->right;
						if (y->color == RED)
						{
							z->p->color = BLACK;
							y->color = BLACK;
							z->p->p->color = RED;
							z = z->p->p;
						}
						else
						{
							if (z == z->p->right)
							{
								z = z->p;
								left_rotate(z);
							}
							z->p->color = BLACK;
							z->p->p->color = RED;
							right_rotate(z->p->p);
						}
					}
					else
					{
						rb_node<T> *y = z->p->p->left;
						if (y->color == RED)
						{
							z->p->color = BLACK;
							y->color = BLACK;
							z->p->p->color = RED;
							z = z->p->p;
						}
						else
						{
							if (z == z->p->left)
							{
								z = z->p;
								right_rotate(z);
							}
							z->p->color = BLACK;
							z->p->p->color = RED;
							left_rotate(z->p->p);
						}
					}
				}
				root()->color = BLACK;
			}

			rb_node<T> *create_node(const value_type& val)				//taken from Alex :DDDDDDDDDD
			{
				rb_node<T>	*new_node = this->_alloc.allocate(1);
				try
				{
					allocator_type	alloc(this->_alloc);
					alloc.construct(&new_node->data, val);
				}
				catch (...)
				{
					this->_alloc.deallocate(new_node, 1);
					throw ;
				}
				return (new_node);
			}
	};

};

#endif