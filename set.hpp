#ifndef SET_HPP
# define SET_HPP

# include "rb_tree.hpp"

namespace ft
{
	template < class T, //set::key_type/value_type           
				class Compare = less<T>,        // set::key_compare/value_compare
				class Alloc = std::allocator<T>      // set::allocator_type        
				>
	class set
	{
		private:
			typedef typename Alloc::template rebind<T>::other	key_alloc_type;
			typedef rb_tree<T, T, same<T>, Compare, Alloc> tree;
		public:
			typedef T 											key_type;
			typedef T 											value_type;
			typedef Compare 									key_compare;
			typedef Compare 									value_compare;
			typedef Alloc 										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference 	const_reference;
			typedef typename allocator_type::pointer 			pointer;
			typedef typename allocator_type::const_pointer 		const_pointer;
			typedef typename tree::const_iterator 					iterator;
			typedef typename tree::const_iterator 				const_iterator;
			typedef typename tree::const_reverse_iterator 			reverse_iterator;
			typedef typename tree::const_reverse_iterator		const_reverse_iterator;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;
		private:
			tree _tree;
		public:
			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc) {}
			template <class InputIterator> 
			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(first, last, comp, alloc) {}
			set (const set& x): _tree(x._tree) {}
			
			~set() 
			{
				clear();
			}

			set& operator= (const set& x)
			{
				this->_tree = x._tree;
				return *this;
			}

			//iterators
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

			void erase (iterator position)
			{
				_tree.erase(position);
			}

			size_type erase (const key_type& k)
			{
				return (_tree.erase(k));
			}

			void erase (iterator first, iterator last)
			{
				_tree.erase(first, last);
			}

			void swap (set& x)
			{
				_tree.swap(x._tree);
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
				return _tree.key_comp();
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
				template <class T_, class Compare_, class Alloc_>  
				friend bool operator==(const set<T_, Compare_, Alloc_>& lhs, const set<T_, Compare_, Alloc_>& rhs);
				
				template <class T_, class Compare_, class Alloc_>  
				friend bool operator<(const set<T_, Compare_, Alloc_>& lhs, const set<T_, Compare_, Alloc_>& rhs);
	};

	template <class T, class Compare, class Alloc> 
	void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
	{
		x.swap(y);
	}

	template <class T, class Compare, class Alloc>  
	bool operator==(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (lhs._tree == rhs._tree);
	}

	template < class T, class Compare, class Alloc >  
	bool operator!= (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}
	
	template < class T, class Compare, class Alloc >  
	bool operator<  (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (lhs._tree < rhs._tree);
	}
	
	template < class T, class Compare, class Alloc >  
	bool operator<=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}
	
	template < class T, class Compare, class Alloc >  
	bool operator>  (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template < class T, class Compare, class Alloc >  
	bool operator>= (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

};

#endif