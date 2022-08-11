/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/11 04:04:06 by brunodeoliv      ###   ########.fr       */
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
	class map
	{
	public:
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef ft::pair<const Key, T>							value_type;

		typedef size_t											size_type;
		typedef ptrdiff_t										difference_type;
		typedef Compare											key_compare;
		typedef Allocator										allocator_type;

		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef T*												pointer;
		typedef const T*										const_pointer;

	private:
		class value_compare
		{
			friend class map;
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
		};

		typedef _RBTree<value_type, value_compare, Allocator>	RBTree;
		typedef typename RBTree::node_ptr					node_ptr;

	public:
		typedef typename RBTree::iterator					iterator;
		typedef typename RBTree::const_iterator				const_iterator;			//un truc a faire ici avec const
		typedef typename RBTree::reverse_iterator			reverse_iterator;
		typedef typename RBTree::const_reverse_iterator		const_reverse_iterator;	//un truc a faire ici avec const

	private:
		RBTree			_tree;

	public:
		/*===================================================================*/
		/*====                     Member Function                       ====*/
		/*===================================================================*/

		explicit map( const Compare& comp = key_compare(),
					  const Allocator& alloc = allocator_type()) :
			_tree(RBTree(value_compare(comp), alloc))
		{}

		template< class InputIt >
		map( InputIt first, InputIt last,
			const Compare& comp = Compare(),
			const Allocator& alloc = Allocator() ) :
			_tree(RBTree(first, last, value_compare(comp), alloc))
		{}

		map( const map& other ) :
			_tree(RBTree(other.begin(), other.end(), other.key_comp(), other.get_allocator()))
		{}

		~map( void ) { _tree.clear(); }

		map& operator=( const map& other )
		{
			if (this == &other )
				return *this;

			_tree = other._tree;
			return *this;
		}

		allocator_type get_allocator() const { return Allocator(); }

		/*===================================================================*/
		/*====                     Element access                        ====*/
		/*===================================================================*/

		T& at( const Key& key )
		{
			node_ptr node = _tree.getNode(value_type(key, ""));

			if (node)
				return node->content.second;
			throw std::out_of_range("ft::map::at");
		}

		const T& at( const Key& key ) const
		{
			node_ptr node = _tree.getNode(value_type(key, ""));

			if (node)
				return node->content.second;
			throw std::out_of_range("ft::map::at");
		}

		T& operator[]( const Key& key ) { return at(key); }

		/*===================================================================*/
		/*====                        Iterator                           ====*/
		/*===================================================================*/

		iterator				begin()		{ return _tree.begin(); }
		iterator				end()		{ return _tree.end(); }
		reverse_iterator		rbegin()	{ return _tree.rbegin(); }
		reverse_iterator		rend()		{ return _tree.rend(); }

		const_iterator			begin() const	{ return _tree.begin(); }
		const_iterator			end() const		{ return _tree.end(); }
		const_reverse_iterator	rbegin() const	{ return _tree.rbegin(); }
		const_reverse_iterator	rend() const	{ return _tree.rend(); }

		/*===================================================================*/
		/*====                       Capacity                            ====*/
		/*===================================================================*/

		bool		empty() const		{ return _tree.size() == 0; }
		size_type	size() const		{ return _tree.size(); }
		size_type	max_size() const	{ return _tree.max_size(); }  // should be corrected


		/*===================================================================*/
		/*====                       Modifiers                           ====*/
		/*===================================================================*/

		void clear();

		ft::pair<iterator, bool> insert( const value_type& value ) //should be changed
		{
			iterator	it = _tree.insert(value).first;
			bool		b = it.base();

			return ft::pair<iterator, bool>(it, b);
		}
		iterator insert( iterator hint, const value_type& value );

		template< class InputIt >
		void insert( InputIt first, InputIt last );

		void erase( iterator pos )
		{
			_tree.deleteNode(pos.base());
		}

		void erase( iterator first, iterator last );

		size_type erase( const Key& key )
		{
			_tree.deleteNode(key);
			return _tree.size();
		}

		void swap( map& other ) { _tree.swap(other._tree); }

		/*===================================================================*/
		/*====                        Lookup                             ====*/
		/*===================================================================*/

		size_type count( const Key& key ) const { return _tree.count(key); }

		iterator find( const Key& key ) { return _tree.find(key); }
		const_iterator find( const Key& key ) const { return _tree.find(key); }

		std::pair<iterator,iterator> equal_range( const Key& key ) { return _tree.equal_range(key); }
		std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const { return _tree.equal_range(key); }

		iterator lower_bound( const Key& key ) { return _tree.lower_bound(key); }
		const_iterator lower_bound( const Key& key ) const { return _tree.lower_bound(key); }

		iterator upper_bound( const Key& key ) { return _tree.upper_bound(key); }
		const_iterator upper_bound( const Key& key ) const { return _tree.upper_bound(key); }

		/*===================================================================*/
		/*====                       Observers                           ====*/
		/*===================================================================*/

		key_compare key_comp() const { return Compare(); }
		value_compare value_comp() const { return _tree.key_comp(); }

		/*===================================================================*/
		/*====                       Optional                            ====*/
		/*===================================================================*/

#ifdef TEST
		void	printTree() const { _tree.printTree(); }
		void	print() const { _tree.print(); }
#endif
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