/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/06/18 02:46:50 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include <ostream>
#include <cstddef>
#include "bidirectional_iterator.hpp"
#include "utility.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

namespace ft{

	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const Key, T>						value_type;
		typedef size_t										size_type;
		typedef ptrdiff_t									difference_type;
		typedef Compare										key_compare;
		typedef Allocator									allocator_type;

		typedef std::pair<const Key, T>&					reference;
		typedef const std::pair<const Key, T>&				const_reference;
		typedef T*											pointer;
		typedef const T*									const_pointer;

		typedef typename ft::bidirectional_iterator<T>			iterator;
		typedef typename ft::bidirectional_iterator<const T>	const_iterator;			//un truc a faire ici avec const
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;	//un truc a faire ici avec const

	private:
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
		pointer			_data;

	public:
		/*===================================================================*/
		/*====                                                           ====*/
		/*====                     Member Function                       ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		
		/*===================================================================*/
		/*====                                                           ====*/
		/*====                     Element access                        ====*/
		/*====                                                           ====*/
		/*===================================================================*/


		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Iterator                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		// iterator				begin()		{ return iterator(_data); }
		// iterator				end()		{ return iterator(_data + _size); }
		// reverse_iterator		rbegin()	{ return reverse_iterator(end() - 1); }
		// reverse_iterator		rend()		{ return reverse_iterator(begin() - 1); }

		// const_iterator			begin() const	{ return const_iterator(_data); }
		// const_iterator			end() const		{ return const_iterator(_data + _size); }
		// const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end() - 1); }
		// const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin() - 1); }

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Capacity                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		bool		empty() const		{ return _size == 0; }
		size_type	size() const		{ return _size; }
		size_type	max_size() const	{ return _alloc.max_size(); }  //maybe add ram available?


		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Modifiers                          ====*/
		/*====                                                           ====*/
		/*===================================================================*/


	};	//class map

	/*===================================================================*/
	/*====                                                           ====*/
	/*====                  Non member function                      ====*/
	/*====                                                           ====*/
	/*===================================================================*/

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const map<Key, T, Compare, Alloc >& lhs, const map<Key, T, Compare, Alloc >& rhs )
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const map<Key, T, Compare, Alloc >& lhs, const map<Key, T, Compare, Alloc >& rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const map<Key, T, Compare, Alloc >& lhs, const map<Key, T, Compare, Alloc >& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const map<Key, T, Compare, Alloc >& lhs, const map<Key, T, Compare, Alloc >& rhs )
	{
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const map<Key, T, Compare, Alloc >& lhs,const map<Key, T, Compare, Alloc >& rhs )
	{
		return rhs < lhs;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const map<Key, T, Compare, Alloc >& lhs,const map<Key, T, Compare, Alloc >& rhs )
	{
		return !(lhs < rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( map<Key, T, Compare, Alloc >& lhs, map<Key, T, Compare, Alloc >& rhs )
	{
		lhs.swap(rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	std::ostream &operator<<( std::ostream &os, const map<Key, T, Compare, Alloc >& rhs )
	{
		os << "(";
		for (size_t i = 0; i < rhs.size(); i++)
			os << rhs[i] << (i < rhs.size() - 1 ? ", " : "");
		os << ")";
		return os;
	}

};	//namespace ft


#endif