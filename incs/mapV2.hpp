/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/10 18:42:18 by brunodeoliv      ###   ########.fr       */
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
#include "RBTree.hpp"

namespace ft{

	template<class T1, class T2, class value_type, class Compare = ft::less<T1> >
	class firstArgPair_compare
	{

	public:
		typedef bool				result_type;
		typedef value_type			first_argument_type;
		typedef value_type			second_argument_type;

		Compare comp;
		firstArgPair_compare( Compare c) : comp(c) {}

		bool operator()( const value_type& lhs, const value_type& rhs ) const
		{
			return comp(lhs.first, rhs.first);
		}
	};

    /*------------------------------------------------------------- 
     *						ft:map
     *
     * - Coplien form:
     *	(constructor):	Construct map
     *	(destructor):	Map destructor
     *	operator=:		Assign map
     *
     * - Iterators:
     *	begin: 			Return iterator to beginning
     *	end: 			Return iterator to end
     *	rbegin: 		Return reverse iterator to reverse beginning
     *	rend: 			Return reverse iterator to reverse end
     *
     * - Capacity:
     *	empty: 			Test whether container is empty
     *	size: 			Return container size
     *	max_size: 		Return maximum size
     *
     * - Element access:
     *	operator:		Access element
     *
     * - Modifiers:
     *	insert: 		Insert elements
     *	erase: 			Erase elements
     *	swap: 			Swap content
     *	clear: 			Clear content
     *
     * - Observers:
     *	key_comp: 		Return key comparison object
     *	value_comp: 	Return value comparison object
     *
     * - Operations:
     *	find: 			Get iterator to element
     *	count: 			Count elements with a specific key
     *	lower_bound: 	Return iterator to lower bound
     *	upper_bound: 	Return iterator to upper bound
     *	equal_range  	Get range of equal elements
	 *
	 * - optional:
	 * 	printTree:			print Tree
	 *	print:				print map
     * ------------------------------------------------------------- */
	template<
		class Key,
		class T,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map :
		public _RBTree<ft::pair<const Key, T>, ft::firstArgPair_compare<Key, T, Compare>, Allocator>
	{

	public:
		typedef typename Allocator::value_type						value_type;
		typedef typename ft::firstArgPair_compare<Key, T, Compare>	value_compare;

		typedef _RBTree<value_type, value_compare, Allocator>		_Tree;
		using typename _Tree::										node_ptr;

		typedef Key													key_type;
		typedef T													mapped_type;
		typedef Compare												key_compare;

		using typename _Tree::										size_type;
		using typename _Tree::										difference_type;
		using typename _Tree::										allocator_type;

		using typename _Tree::										reference;
		using typename _Tree::										const_reference;
		using typename _Tree::										pointer;
		using typename _Tree::										const_pointer;

		using typename _Tree::										iterator;
		using typename _Tree::										const_iterator;
		using typename _Tree::										reverse_iterator;
		using typename _Tree::										const_reverse_iterator;

		// typedef Key												key_type;
		// typedef T												mapped_type;
		// typedef ft::pair<const Key, T>							value_type;

		// typedef size_t											size_type;
		// typedef ptrdiff_t										difference_type;
		// typedef Compare											key_compare;
		// typedef Allocator										allocator_type;

		// typedef value_type&										reference;
		// typedef const value_type&								const_reference;
		// typedef T*												pointer;
		// typedef const T*										const_pointer;

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                     Member Function                       ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		map() : _Tree(value_compare(Compare()), Allocator()) {}

		explicit map( const Compare& comp,
					  const Allocator& alloc = allocator_type()) :
			_Tree(value_compare(comp), alloc)
		{}

		template< class InputIt >
		map( InputIt first, InputIt last,
			const Compare& comp = Compare(),
			const Allocator& alloc = Allocator() ) :
			_Tree(first, last, value_compare(comp), alloc)
		{}

		map( const map& other ) : _Tree(other) {}

		~map( void ) {}

		map& operator=( const map& other )
		{
			if (this == &other )
				return *this;

			this->clear();
			this->_alloc = other._alloc;
			this->_nodeAlloc = other._nodeAlloc;
			this->_keyComp = other._keyComp;
			this->_comp = other._comp;
			this->_root = copy(other._root);
			this->_size = other._size;
			return *this;
		}

		/*===================================================================*/
		/*====                     Element access                        ====*/
		/*===================================================================*/

		T& at( const Key& key )
		{
			node_ptr	node = this->_getNode(value_type(key, T()));

			if (node)
				return node->content.second;
			throw std::out_of_range("ft::map::at");
		}

		const T& at( const Key& key ) const
		{
			node_ptr	node = this->_getNode(value_type(key, T()));

			if (node)
				return node->content.second;
			throw std::out_of_range("ft::map::at");
		}

		T& operator[]( const Key& key ) { return at(key); }

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                       Observers                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		virtual key_compare		key_comp() const { return Compare(); }
		virtual value_compare	value_comp() const { return this->_comp; }

	};	//class map

	/*===================================================================*/
	/*====                                                           ====*/
	/*====                    Non member function                    ====*/
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