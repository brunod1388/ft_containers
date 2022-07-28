/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/29 00:29:14 by brunodeoliv      ###   ########.fr       */
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

    /*------------------------------------------------------------- 
     *
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
     * ------------------------------------------------------------- */
	template<
		class Key,
		class T,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef std::pair<const Key, T>							value_type;

		typedef size_t											size_type;
		typedef ptrdiff_t										difference_type;
		typedef Compare											key_compare;
		typedef Allocator										allocator_type;

		typedef std::pair<const Key, T>&						reference;
		typedef const std::pair<const Key, T>&					const_reference;
		typedef T*												pointer;
		typedef const T*										const_pointer;

		typedef typename ft::bidirectional_iterator<T>			iterator;
		typedef typename ft::bidirectional_iterator<const T>	const_iterator;			//un truc a faire ici avec const

		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;	//un truc a faire ici avec const


		class value_compare
		{
		protected:
			key_compare comp;

			value_compare( Compare c) : comp(c) {}

		public:
			typedef bool				result_type;
			typedef value_type			first_argument_type;
			typedef value_type			second_argument_type;

			bool operator()( const value_type& lhs, const value_type& rhs ) const
			{
				return comp(lhs.first, rhs.first);
			}
		}

	private:
		allocator_type	_alloc;
		size_type		_size;
		RBTree			_tree;
		key_compare		_comp;

	public:
		/*===================================================================*/
		/*====                                                           ====*/
		/*====                     Member Function                       ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		map( void ) :
			_alloc(Allocator()),
			_size(0),
			_tree(RBTree< ft::pair< Key, T >, Compare, Allocator >())
		{}

		explicit map( const Compare& comp,
              const Allocator& alloc = Allocator() ) :
			_alloc(alloc),
			_size(0),
			_tree(RBTree< ft::pair< Key, T >, , Allocator >())
		{}

		template< class InputIt >
		map( InputIt first, InputIt last,
			const Compare& comp = Compare(),
			const Allocator& alloc = Allocator() );

		map( const map& other );

		~map( void )
		{
			_tree.clear();
		}

		map& operator=( const map& other );

		allocator_type get_allocator() const;

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                     Element access                        ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		T& at( const Key& key );
		const T& at( const Key& key ) const;

		T& operator[]( const Key& key );

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Iterator                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		iterator				begin()		{}
		iterator				end()		{}
		reverse_iterator		rbegin()	{}
		reverse_iterator		rend()		{}

		const_iterator			begin() const	{}
		const_iterator			end() const		{}
		const_reverse_iterator	rbegin() const	{}
		const_reverse_iterator	rend() const	{}

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                       Capacity                            ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		bool		empty() const		{ return _size == 0; }
		size_type	size() const		{ return _size; }
		size_type	max_size() const	{ return _alloc.max_size(); }  // should be corrected


		/*===================================================================*/
		/*====                                                           ====*/
		/*====                       Modifiers                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		void clear();

		std::pair<iterator, bool> insert( const value_type& value );
		iterator insert( iterator hint, const value_type& value );

		template< class InputIt >
		void insert( InputIt first, InputIt last );

		void erase( iterator pos );
		void erase( iterator first, iterator last );

		size_type erase( const Key& key );
		void swap( map& other );

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Lookup                             ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		size_type count( const Key& key ) const;

		iterator find( const Key& key );
		const_iterator find( const Key& key ) const;

		std::pair<iterator,iterator> equal_range( const Key& key );
		std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

		iterator lower_bound( const Key& key );
		const_iterator lower_bound( const Key& key ) const;

		iterator upper_bound( const Key& key );
		const_iterator upper_bound( const Key& key ) const;

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                       Observers                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		key_compare key_comp() const;
		std::map::value_compare value_comp() const;
	
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