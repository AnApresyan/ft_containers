#ifndef TYPE_TRAITS
#define TYPE_TRAITS

namespace ft
{
	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		operator T() { return v; }
	};
	
	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template< class T > struct remove_cv                   { typedef T type; };
	template< class T > struct remove_cv<const T>          { typedef T type; };
	template< class T > struct remove_cv<volatile T>       { typedef T type; };
	template< class T > struct remove_cv<const volatile T> { typedef T type; };

	template<typename> struct is_integral_base : false_type {};
	template <> struct is_integral_base<bool> : true_type {};
	template <> struct is_integral_base<char> : true_type {};
	template <> struct is_integral_base<wchar_t> : true_type {};
	template <> struct is_integral_base<signed char> : true_type {};
	template <> struct is_integral_base<short int> : true_type {};
	template <> struct is_integral_base<int> : true_type {};
	template <> struct is_integral_base<long int> : true_type {};
	template <> struct is_integral_base<long long int> : true_type {};
	template <> struct is_integral_base<unsigned char> : true_type {};
	template <> struct is_integral_base<unsigned short int> : true_type {};
	template <> struct is_integral_base<unsigned int> : true_type {};
	template <> struct is_integral_base<unsigned long int> : true_type {};
	template <> struct is_integral_base<unsigned long long int> : true_type {};

	template<typename T> struct is_integral: is_integral_base<typename remove_cv<T>::type> {};

	//ENABLE IF
	template<bool B, typename T = void>
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};


}

#endif