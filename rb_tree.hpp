#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "rbt_iterator.hpp"
#include <memory>
#include "rbt_helper.hpp"
#include "rb_node.hpp"
#include "pair.hpp"
#include "algorithm.hpp"
#include <iostream>

namespace ft
{

	template <class Key, class T, class KeyOfValue, class Compare = less<Key>, class Alloc = std::allocator<T> >
	class rb_tree
	{
	public:
		typedef Key key_type;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef ft::rbt_iterator<value_type> iterator;
		typedef ft::const_rbt_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

	private:
		typedef rb_node<T> node;
		typedef typename Alloc::template rebind<node>::other node_allocator_type;

		rb_base_node _chief;
		rb_base_node _sentinel;
		size_type _size;
		key_compare _comp;
		node_allocator_type _alloc;

	public:
		// constructors
		explicit rb_tree(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _chief(), _sentinel(), _size(), _comp(comp), _alloc(alloc)
		{
			init();
		}

		template <class InputIterator>
		rb_tree(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _chief(), _sentinel(), _size(), _comp(comp), _alloc(alloc)
		{
			init();
			insert(first, last);
		}

		rb_tree(const rb_tree &x) : _chief(x._chief), _sentinel(), _size(), _comp(x._comp), _alloc(x._alloc)
		{
			init();
			insert(x.begin(), x.end());
		}

		// operator=
		rb_tree &operator=(const rb_tree &x)
		{
			clear();
			insert(x.begin(), x.end());
			return (*this);
		}

		// Iterators
		iterator begin()
		{
			return iterator(_chief.left);
		}

		const_iterator begin() const
		{
			return const_iterator(_chief.left);
		}

		iterator end()
		{
			return iterator(sentinel());
		}

		const_iterator end() const
		{
			return const_iterator(sentinel());
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

		// Capacity
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

		// Modifiers

		pair<iterator, bool>
		insert(const value_type &val)
		{
			rb_base_node *y = &_sentinel;
			rb_base_node *x = root();
			if (_size == 0)
			{
				rb_node<T> *z = create_node(val);
				_chief.p = z;
				_chief.left = z;
				_chief.right = z;
				_sentinel.p = z;
				z->left = &_sentinel;
				z->right = &_sentinel;
				z->color = BLACK;
				z->p = &_sentinel;
				_size++;
				return ft::make_pair(iterator(z), true);
			}
			while (is_internal(x))
			{
				y = x;
				if (_comp(keyof(val), keyof(x)))
					x = x->left;
				else if (_comp(keyof(x), keyof(val)))
					x = x->right;
				else
					break;
			}
			if (is_internal(y))
			{
				if (!_comp(keyof(y), keyof(val)) && !_comp(keyof(val), keyof(y)))
					return (ft::make_pair(iterator(y), false));
				if (is_internal(y->p) && !_comp(keyof(y->p), keyof(val)) && !_comp(keyof(val), keyof(y->p)))
					return (ft::make_pair(iterator(y->p), false));
			}
			rb_node<T> *z = create_node(val);
			z->p = y;
			if (is_external(y))
				_chief.p = z;
			else if (_comp(keyof(val), keyof(y)))
				y->left = z;
			else
				y->right = z;
			z->left = &_sentinel;
			z->right = &_sentinel;
			z->color = RED;
			_size++;
			if (_comp(keyof(val), keyof(_chief.left)))
				_chief.left = z;
			else if (_comp(keyof(_chief.right), keyof(val)))
			{
				_chief.right = z;
				_sentinel.p = z;
			}
			insert_fixup(z);
			return (ft::make_pair(iterator(z), true));
		}

		iterator insert(const_iterator it, const value_type &val)
		{
			return (insert(iterator(const_cast<rb_base_node*>(it._node)), val));
		}

		iterator insert(iterator, const value_type &val)
		{
			return insert(val).first;
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		void erase(const_iterator position)
		{
			erase(iterator(const_cast<rb_base_node*>(position._node)));
		}

		void erase(iterator position)
		{
			rb_base_node *z = position._node;
			rb_base_node *y = z;
			node_color original_color_y = y->color;
			rb_base_node *x;
			if (position._node == _chief.left)
			{
				_chief.left = (++position)._node;
				position--;
			}
			if (position._node == _chief.right)
			{
				_chief.right = (--position)._node;
				_sentinel.p = _chief.right;
				position++;
			}
			if (is_external(z->left))
			{
				x = z->right;
				rb_transplant(z, z->right);
			}
			else if (is_external(z->right))
			{
				x = z->left;
				rb_transplant(z, z->left);
			}
			else
			{
				y = tree_min(z->right);
				original_color_y = y->color;
				x = y->right;
				if (y->p == z && is_internal(x))
					x->p = y;
				else
				{
					rb_transplant(y, y->right);
					y->right = z->right;
					if (is_internal(y->right))
						y->right->p = y;
				}
				rb_transplant(z, y);
				y->left = z->left;
				y->left->p = y;
				y->color = z->color;
			}
			_size--;
			if (original_color_y == BLACK)
				delete_fixup(x);
			allocator_type	alloc(this->_alloc);
			alloc.destroy(&static_cast<node *>(z)->element);
			_alloc.deallocate(static_cast<node *>(z), 1);
		}

		size_type erase(const key_type &k)
		{
			iterator low = lower_bound(k);
			iterator high = upper_bound(k);
			size_type deletions = 0;

			while (low != high)
			{
				erase(low++);
				deletions++;
			}
			return (deletions);
		}

		void erase(const_iterator first, const_iterator last)
		{
			erase(iterator(const_cast<rb_base_node*>(first._node)), iterator(const_cast<rb_base_node*>(last._node)));
		}

		void erase(iterator first, iterator last)
		{
			iterator next = first;

			while (next != last)
			{
				next++;
				erase(first);
				first = next;
			}
		}

	private:
		void delete_fixup(rb_base_node *x)
		{
			while (is_internal(x) && !is_root(x) && x->color == BLACK)
			{
				rb_base_node *w;
				if (x == x->p->left)
				{
					w = x->p->right;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->p->color = RED;
						left_rotate(x->p);
						w = x->p->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK)
					{
						w->color = RED;
						x = x->p;
					}
					else
					{
						if (w->right->color == BLACK)
						{
							w->left->color = BLACK;
							w->color = RED;
							right_rotate(w);
							w = x->p->right;
						}
						w->color = x->p->color;
						x->p->color = BLACK;
						w->right->color = BLACK;
						left_rotate(x->p);
						x = root();
					}
				}
				else
				{
					w = x->p->left;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->p->color = RED;
						right_rotate(x->p);
						w = x->p->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK)
					{
						w->color = RED;
						x = x->p;
					}
					else
					{
						if (w->left->color == BLACK)
						{
							w->right->color = BLACK;
							w->color = RED;
							left_rotate(w);
							w = x->p->left;
						}
						w->color = x->p->color;
						x->p->color = BLACK;
						w->left->color = BLACK;
						right_rotate(x->p);
						x = root();
					}
				}
			}
			x->color = BLACK;
		}

		rb_base_node *tree_min(rb_base_node *n)
		{
			while (is_internal(n->left))
				n = n->left;
			return n;
		}

	public:
		void swap(rb_tree &x)
		{
			ft::sswap(_chief, x._chief);
			ft::sswap(_sentinel, x._sentinel);
			ft::sswap(_size, x._size);
		}

		void clear()
		{
			destroy_subtree(root());
			_size = 0;
			_chief.p = &_sentinel;
			_chief.right = &_sentinel;
			_chief.left = &_sentinel;
		}

		// Observers
		key_compare key_comp() const
		{
			return (_comp);
		}

		// Operations
		const_iterator find(const key_type &k) const
		{
			if (empty())
				return (const_iterator(&_sentinel));
			rb_base_node *temp(root());
			while (is_internal(temp) && (_comp(keyof(temp), k) || _comp(k, keyof(temp))))
			{
				if (_comp(k, keyof(temp)))
					temp = temp->left;
				else
					temp = temp->right;
			}
			if (is_internal(temp) && !_comp(keyof(temp), k) && !_comp(k, keyof(temp)))
				return (const_iterator(temp));
			return (end());
		}

		iterator find(const key_type &k)
		{
			const_iterator const_it = static_cast<const rb_tree &>(*this).find(k);
			return (iterator(const_cast<rb_base_node *>(const_it._node)));
		}

		size_type count(const key_type &k) const
		{
			if (is_internal(find(k)._node))
				return (1);
			return (0);
		}

		const_iterator lower_bound(const key_type &k) const
		{
			if (empty())
				return (const_iterator(&_sentinel));
			rb_base_node *temp(root());

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
				return ++const_iterator(temp);
			return const_iterator(temp);
		}

		iterator lower_bound(const key_type &k)
		{
			const_iterator it = static_cast<const rb_tree &>(*this).lower_bound(k);
			return (iterator(const_cast<rb_base_node *>(it._node)));
		}

		const_iterator upper_bound(const key_type &k) const
		{
			if (empty())
				return (const_iterator(&_sentinel));
			rb_base_node *temp(root());

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
			if (_comp(k, keyof(temp)))
				return const_iterator(temp);
			return ++const_iterator(temp);
		}

		iterator upper_bound(const key_type &k)
		{
			const_iterator it = static_cast<const rb_tree &>(*this).upper_bound(k);
			return (iterator(const_cast<rb_base_node *>(it._node)));
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		// Allocator
		allocator_type get_allocator() const
		{
			return (_alloc);
		}

		// destructor
		~rb_tree()
		{
			clear();
		}

	private:
		// helper functions
		rb_base_node *sentinel() const
		{
			if (_size == 0)
				return _chief.left;
			return _chief.p->p;
		}

		rb_node<T> *min()
		{
			return (_chief.left);
		}

		rb_node<T> *max()
		{
			return (_chief.right);
		}

		rb_base_node *root() const
		{
			return (_chief.p);
		}

		bool is_root(const rb_base_node *n)
		{
			return (is_external(n->p));
		}

		bool is_internal(const rb_base_node *n) const
		{
			return (!is_external(n));
		}

		bool is_external(const rb_base_node *n) const
		{
			return (!n || (n && !n->left && !n->right));
		}

		bool is_chief(const rb_base_node *n)
		{
			if (empty())
				return (true);
			else if (is_external(n->p).p)
				return (true);
			return (false);
		}

		void left_rotate(rb_base_node *x)
		{
			if (is_external(x->right))
				return;
			rb_base_node *y = x->right;
			x->right = y->left;
			if (is_internal(y->left))
				y->left->p = x;
			y->p = x->p;
			if (is_external(x->p))
				_chief.p = y;
			else if (x == x->p->left)
				x->p->left = y;
			else
				x->p->right = y;
			y->left = x;
			x->p = y;
		}

		void right_rotate(rb_base_node *x)
		{
			if (is_external(x->left))
				return;
			rb_base_node *y = x->left;
			x->left = y->right;
			if (is_internal(y->right))
				y->right->p = x;
			y->p = x->p;
			if (is_external(x->p))
				_chief.p = y;
			else if (x == x->p->right)
				x->p->right = y;
			else
				x->p->left = y;
			y->right = x;
			x->p = y;
		}

		Key keyof(rb_base_node *x) const
		{
			return (KeyOfValue()((static_cast<node *>(x))->element));
		}

		Key keyof(const value_type &val)
		{
			return (KeyOfValue()(val));
		}

		void insert_fixup(rb_base_node *z)
		{
			while (z->p->color == RED)
			{
				if (z->p == z->p->p->left)
				{
					rb_base_node *y = z->p->p->right;
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
					rb_base_node *y = z->p->p->left;
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

		rb_node<T> *create_node(const value_type &val) // taken from Alex :DDDDDDDDDD
		{
			rb_node<T> *new_node;
			try
			{
				new_node = this->_alloc.allocate(1);
				allocator_type alloc(this->_alloc);
				alloc.construct(&new_node->element, val);
			}
			catch (...)
			{
				this->_alloc.deallocate(new_node, 1);
				throw;
			}
			return (new_node);
		}

		void init()
		{
			_sentinel.color = BLACK;
			_chief.p = &_sentinel;
			_chief.right = &_sentinel;
			_chief.left = &_sentinel;
			_chief.color = BLACK;
		}

		void rb_transplant(rb_base_node *u, rb_base_node *v)
		{
			if (is_external(u->p))
				_chief.p = v;
			else if (u == u->p->left)
				u->p->left = v;
			else
				u->p->right = v;
			if (is_internal(v))
				v->p = u->p;
		}

		void destroy_subtree(rb_base_node *x)
		{
			if (is_external(x))
				return;
			destroy_subtree(x->left);
			destroy_subtree(x->right);
			allocator_type alloc(this->_alloc);
			alloc.destroy(&static_cast<node *>(x)->element);
			this->_alloc.deallocate(static_cast<node *>(x), 1);
		}
	};

	template <class Key, class T, class KeyOfValue, class Compare, class Alloc>
	bool operator==(const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class KeyOfValue, class Compare, class Alloc>
	bool operator!=(const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class KeyOfValue, class Compare, class Alloc>
	bool operator<(const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class KeyOfValue, class Compare, class Alloc>
	bool operator<=(const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class KeyOfValue, class Compare, class Alloc>
	bool operator>(const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class KeyOfValue, class Compare, class Alloc>
	bool operator>=(const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, T, KeyOfValue, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

};

#endif