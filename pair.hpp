#ifndef UTILITY_H
#define UTILITY_H

namespace ft
{
	template <class T1, class T2> 
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair();

		template<class U, class V>
		pair (const ft::pair<U,V>& pr);

		pair (const first_type& a, const second_type& b);

		pair& operator= (const pair& pr);
	};

	template <class T1, class T2> 
	pair<T1, T2>::pair(): first(), second() {};

	template <class T1, class T2> 
	template<class U, class V>
	pair<T1, T2>::pair(const ft::pair<U,V>& pr): first(pr.first), second(pr.second) {};

	template <class T1, class T2> 
	pair<T1, T2>::pair(const first_type& a, const second_type& b): first(a), second(b) {};


	template <class T1, class T2> 
	pair<T1, T2> &pair<T1, T2>::operator=(const pair& pr)
	{
		first = pr.first;
		second = pr.second;
		return (*this);
	}

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1,T2>(x,y) );
	}
}

#endif