/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/06/03 02:34:48 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft{

	template <class T1, class T2>
	struct pair{
		typedef T1	firs_type;
		typedef T2	seconde_type;

		T1	first;
		T2	second;

		pair() : first(), second() {}

		pair( const T1& x, const T2& y ) : first(x), second(y) {}

		pair( const pair<T1, T2>& p ) : first(p.first), second(p.second) {} //not sur i need this one

		template< class U1, class U2 >
		pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}

		pair& operator=( const pair& rhs ) 
		{
			if (this != &rhs)
			{
				first = rhs.first;
				second = rhs.second;
			}
			return *this;
		}

		~pair( void ) {}
	}; // class pair

	template< class T1, class T2 >
	inline pair<T1,T2> make_pair( T1 t, T2 u ) { return pair<T1,T2>(t, u);}

	template< class T1, class T2 >
	inline void swap( pair<T1,T2>& x, pair<T1,T2>& y )
	{
		pair<T1, T2> tmp = x;
		x = y;
		y = tmp;
	}

	template< class T1, class T2 >
	inline bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template< class T1, class T2 >
	inline bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T1, class T2 >
	inline bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return (lhs.first != rhs.first ? lhs.first < rhs.first : lhs.second < rhs.second);
	}

	template< class T1, class T2 >
	inline bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class T1, class T2 >
	inline bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return rhs < lhs;
	}

	template< class T1, class T2 >
	inline bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return !(lhs < rhs);
	}

	template< class T1, class T2 >
	std::ostream &operator<<(std::ostream &os, const pair<T1,T2>& rhs )
	{
		os << "(" << rhs.first << ", " << rhs.second << ")";
		return os;
	}

	template< typename T>    // not sur about this
	void	swap(T a, T b)
	{
		T c;

		c = a;
		a = b;
		b = c;
	}

} // namespace ft
#endif
