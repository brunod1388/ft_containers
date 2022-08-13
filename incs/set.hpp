/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/12 05:26:14 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "RBTree.hpp"

namespace ft{

    /*------------------------------------------------------------- 
     *						ft:set
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
     *	operator[]:		Access element
     *	at:				access element
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
		class Compare = ft::less<Key>,
		class Allocator = std::allocator<Key> >
	class set : public ft::_RBTree<Key, compare, Allocator>
	{
	private:
		typedef ft::_RBTree<Key, compare, Allocator>	Base;
	public:
		set() : Base() {}
		explicit map( const Compare& comp = key_compare(),
					  const Allocator& alloc = allocator_type()) :
			Base(value_compare(comp), alloc)
		{}

		template< class InputIt >
		map( InputIt first, InputIt last,
			const Compare& comp = Compare(),
			const Allocator& alloc = Allocator() ) :
			RBTree(first, last, comp, alloc)
		{}

		map( const map& other ) : Base(other) {}

		~set(void) : ~Base() {}

		set&	operator=(const set& rhs) { *this = rhs}

	};	// class set

}	//namespace ft

#endif
