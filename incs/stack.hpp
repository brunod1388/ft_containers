/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/06/15 16:31:15 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include <ostream>
#include "vector.hpp"
#include "utility.hpp"

class vector;

namespace ft{

	template < class T, class Container = ft::vector<T> >
	class stack{

	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

	protected:
		Container c;

	public:

		explicit stack( const Container& cont = Container() ) : c(cont) {}

		stack(const stack& src) : c(src.c) {}

		template< class InputIt >
		stack( InputIt first, InputIt last ) : c(first, last) {}

		~stack( void ) {}

		stack& operator=(const stack& rhs) { c = rhs.c; return *this; }

		reference		top( void ) { return c.back(); }
		const_reference	top( void ) const { return c.back(); }

		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }

		void push( const value_type& value ) { c.push_back(value); }
		void pop() { c.pop_back(); }

		void swap( stack& other ) { c.swap(other.c); }

	}; // class stack

	template< class T, class Container >
	bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return lhs == rhs;
	}

	template< class T, class Container >
	bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return lhs != rhs;
	}

	template< class T, class Container >
	bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return lhs < rhs;
	}

	template< class T, class Container >
	bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return lhs <= rhs;
	}

	template< class T, class Container >
	bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return lhs > rhs;
	}

	template< class T, class Container >
	bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return lhs >= rhs;
	}

	template< class T, class Container >
	void swap( stack<T,Container>& lhs, stack<T,Container>& rhs )
	{
		lhs.swap(rhs);
	}
} // namespace ft

#endif
