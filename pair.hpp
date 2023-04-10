#ifndef U1TILITY_HPP
#define U1TILITY_HPP

namespace ft
{
	template <typename T1, typename T2> 
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair();
		pair (const first_type& a, const second_type& b);

		template<typename U1, typename U2>
		pair (const pair<U1,U2>& pr);


		pair& operator= (const pair& pr);
	};

	template <typename T1, typename T2> 
	pair<T1, T2>::pair(): first(), second() {}

	template <typename T1, typename T2> 
	template<typename U1, typename U2 >
	pair<T1, T2>::pair(const pair< U1,U2 >& pr): first(pr.first), second(pr.second) {}

	template <typename T1, typename T2> 
	pair<T1, T2>::pair(const first_type& a, const second_type& b): first(a), second(b) {}


	template <typename T1, typename T2> 
	pair<T1, T2> &pair<T1, T2>::operator=(const pair& pr)
	{
		first = pr.first;
		second = pr.second;
		return (*this);
	}

	template <typename T1, typename T2>
	pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1,T2>(x,y));
	}

	template <typename T1, typename T2>
	bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ 
		return lhs.first==rhs.first && lhs.second==rhs.second; 
	}

	template <typename T1, typename T2>
	bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ 
		return !(lhs==rhs); 
	}

	template <typename T1, typename T2>
	bool operator<  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ 
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); 
	}

	template <typename T1, typename T2>
	bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ 
		return !(rhs<lhs); 
	}

	template <typename T1, typename T2>
	bool operator>  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ 
		return (rhs<lhs); 
	}

	template <typename T1, typename T2>
	bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ 
		return !(lhs<rhs); 
	}
};

#endif