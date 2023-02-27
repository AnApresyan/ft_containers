#ifndef MAP_HPP
# define MAP_HPP

#include "rb_tree.hpp"
// #include 

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map 
	{
		public:
			typedef Key 									key_type;
			typedef T 										mapped_type;
			typedef pair<const key_type,mapped_type>		value_type;
			typedef Compare									key_compare;
			class value_compare : binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
			};
			typedef Alloc 									allocator_type;
			
		private:		//again taken from Alex, I have to understand this rebind thing
			typedef typename Alloc::template rebind<value_type>::other	pair_allocator_type;
			typedef rb_tree<key_type, value_type, select_1st<value_type>, key_compare, pair_allocator_type>	tree;

		public:
			typedef typename pair_allocator_type::reference			reference;
			typedef typename pair_allocator_type::const_reference	const_reference;
			typedef typename pair_allocator_type::pointer			pointer;
			typedef typename pair_allocator_type::const_pointer		const_pointer;
			typedef typename tree::iterator							iterator;
			typedef typename tree::const_iterator					const_iterator;
			typedef typename tree::reverse_iterator					reverse_iterator;
			typedef typename tree::const_reverse_iterator			const_reverse_iterator;
			typedef ptrdiff_t 										difference_type;
			typedef size_t											size_type;

		private:
			tree _tree;

		public:
			//constructors
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc) {}
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(first, last, comp, alloc) {}
			
			map (const map& x) : _tree(x) {}

			//destructor
			~map() {}

			//operator=
			map& operator= (const map& x)
			{
				_tree = x._tree;
				return (*this);
			}

			//iterator
			iterator begin()
			{
				return _tree.begin();
			}
			
			const_iterator begin() const
			{
				return _tree.begin();
			}

			iterator end()
			{
				return _tree.end();
			}

			const_iterator end() const
			{
				return _tree.end();
			}

			reverse_iterator rbegin()
			{
				return _tree.rbegin();
			}

			const_reverse_iterator rbegin() const
			{
				return _tree.rbegin();
			}

			reverse_iterator rend()
			{
				return _tree.rend();
			}

			const_reverse_iterator rend() const
			{
				return _tree.rend();
			}

			//capacity
			bool empty() const
			{
				return _tree.empty();
			}

			size_type size() const
			{
				return _tree.size();
			}

			size_type max_size() const
			{
				return _tree.max_size();
			}

			//element access
			mapped_type& operator[] (const key_type& k)
			{
				return *(this->insert(make_pair(k,mapped_type())).second);
			}

			//don't I need at?

			//modifiers
			pair<iterator,bool> insert (const value_type& val)
			{
				return _tree.insert(val);
			}

			iterator insert (iterator position, const value_type& val)
			{
				return _tree.insert(position, val);
			}

			template <class InputIterator>  
			void insert (InputIterator first, InputIterator last)
			{
				_tree.insert(first, last);
			}

			void erase (iterator)
			{
//iterator position
			}

			// size_type erase (const key_type& k)
			// {

			// }

			void erase (iterator, iterator)
			{
//iterator first, iterator last
			}

			void swap (map& x)
			{
				_tree.swap(x);
			}

			void clear()
			{
				_tree.clear();
			}

			//Observers
			key_compare key_comp() const
			{
				return _tree.key_comp();
			}

			value_compare value_comp() const
			{
				return value_compare(key_comp());
			}

			//Operations
			iterator find (const key_type& k)
			{
				return _tree.find(k);
			}

			const_iterator find (const key_type& k) const
			{
				return _tree.find(k);
			}

			size_type count (const key_type& k) const
			{
				return _tree.count(k);
			}

			iterator lower_bound (const key_type& k)
			{
				return _tree.lower_bound(k);
			}

			const_iterator lower_bound (const key_type& k) const
			{
				return _tree.lower_bound(k);
			}

			iterator upper_bound (const key_type& k)
			{
				return _tree.upper_bound(k);
			}

			const_iterator upper_bound (const key_type& k) const
			{
				return _tree.upper_bound(k);
			}

			pair<const_iterator,const_iterator> 
			equal_range (const key_type& k) const
			{
				return _tree.equal_range(k);
			}
			
			pair<iterator,iterator>
			equal_range (const key_type& k)
			{
				return _tree.equal_range(k);
			}

			//Allocator
			allocator_type get_allocator() const
			{
				return _tree.get_allocator();
			}
			private:
				template <class Key_, class T_, class Compare_, class Alloc_>  
				friend bool operator==(const map<Key_, T_, Compare_, Alloc_>& lhs, const map<Key_, T_, Compare_, Alloc_>& rhs);
				template <class Key_, class T_, class Compare_, class Alloc_>  
				friend bool operator<(const map<Key_, T_, Compare_, Alloc_>& lhs, const map<Key_, T_, Compare_, Alloc_>& rhs);
	};

	template <class Key, class T, class Compare, class Alloc>  
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs._tree == rhs._tree);
	}

	template < class Key, class T, class Compare, class Alloc >  
	bool operator!= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}
	
	template < class Key, class T, class Compare, class Alloc >  
	bool operator<  (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),rhs.begin(), rhs.end()));
	}
	
	template < class Key, class T, class Compare, class Alloc >  
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(rhs._tree < lhs._tree);
	}
	
	template < class Key, class T, class Compare, class Alloc >  
	bool operator>  (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template < class Key, class T, class Compare, class Alloc >  
	bool operator>= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}
};

#endif