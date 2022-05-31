/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/05/31 04:42:12 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <ostream>
#include <cstddef>
#include "vector_iterator.hpp"
#include "vector_rev_iterator.hpp"
#include "utility.hpp"

namespace ft{

	template < class T, class Allocator = std::allocator<T> >
	class vector{

	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef size_t										size_type;
		typedef ptrdiff_t									difference_type;

		typedef T&											reference;
		typedef const T&									const_reference;
		typedef T*											pointer;
		typedef const T*									const_pointer;

		typedef typename ft::vector_iterator<T>				iterator;
		typedef typename ft::vector_iterator<const T>		const_iterator;			//un truc a faire ici avec const
		typedef typename ft::vector_rev_iterator<T>			reverse_iterator;
		typedef typename ft::vector_rev_iterator<const T>	const_reverse_iterator;	//un truc a faire ici avec const

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

		vector() :
			_alloc(Allocator()),
			_size(0),
			_capacity(0),
			_data(_alloc.allocate(_capacity))
		{}

		explicit vector( const Allocator& alloc ) :
			_alloc(alloc),
			_size(0),
			_capacity(0),
			_data(alloc.allocate(_capacity))
		{}

		explicit vector( size_type count,
						 const T& value = T(),
						 const Allocator& alloc = Allocator()) :
			_alloc(alloc),
			_size(count),
			_capacity(count),
			_data(alloc.allocate(_capacity))
		{
			for (size_t i = 0; i < count; i++)
				_data[i] = value;
		}

		template< class InputIt >
		vector( InputIt first, InputIt last,
				const Allocator& alloc = Allocator() );

		vector( const vector<T> &other ) :
			_alloc(other._alloc),
			_size(other._size),
			_capacity(other._capacity),
			_data(_alloc.allocate(_capacity))
		{
			for (size_t i = 0; i < _size; i++)
				_data[i] = other._data[i];
		}
		
		vector& operator= (const vector& x) {}
		~vector( void ){}

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);
		void assign( size_type count, const T& value );
		allocator_type get_allocator() const { return _alloc; }

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                     Element access                        ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		reference 		at( size_type pos );
		const_reference at( size_type pos ) const;
		reference 		operator[]( size_type pos ) { return _data[pos]; }
		const_reference operator[]( size_type pos ) const { return _data[pos]; }
		reference 		front() { return *begin(); }
		const_reference front() const { return *begin(); }
		reference 		back() { return *(end() - 1); }
		const_reference back() const { return *(end() - 1); }
		T*				data() { return _data; }
		const T* 		data() const { return _data; }

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Iterator                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		iterator	begin() { return iterator(_data); } // not sur i need both....
		const_iterator	begin() const { return const_iterator(_data); }

		iterator	end() { return iterator(_data + _size); }
		const_iterator	end() const { return iterator(_data + _size); }
		reverse_iterator	rbegin() { return const_reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const{ return const_reverse_iterator(end()); }
		reverse_iterator	rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const{ return const_reverse_iterator(begin()); }

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Capacity                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		bool		empty() const { return _size == 0; }
		size_type	size() const { return _size; }
		size_type	max_size() const { return _alloc.max_size() ; }  //maybe add ram available?
		void		reserve( size_type new_cap );
		size_type	capacity() const { return _capacity; }

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Modifiers                          ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		void		clear();
		iterator	insert( iterator pos, const T& value );
		void		insert( iterator pos, size_type count, const T& value );

		template< class InputIt >
		void	insert( iterator pos, InputIt first, InputIt last );

		iterator	erase( iterator pos );
		iterator	erase( iterator first, iterator last );
		void	push_back( const T& value );
		void	pop_back();
		void 	resize ( size_type n, value_type val = value_type() );
		
		void swap ( vector& arg )
		{
			swap(_size, arg._size);
			swap(_capacity, arg._capacity);
			swap(_data, arg._data);
			swap(_alloc, arg._alloc);
		}

	};	//class vector

	/*===================================================================*/
	/*====                                                           ====*/
	/*====                  Non member function                      ====*/
	/*====                                                           ====*/
	/*===================================================================*/

	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs,const vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs,const vector<T,Alloc>& rhs );

	// not sur about this, should it be more generic?
	template< class T, class Alloc >
	void swap( vector<T,Alloc>& lhs, vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	std::ostream &operator<<( std::ostream &os, const vector<T, Alloc>& rhs )
	{
		os << "(";
		for (size_t i = 0; i < rhs.size(); i++)
			os << rhs[i] << (i < rhs.size() - 1 ? ", " : "");
		os << ")";
		return os;
	}

};	//namespace ft


#endif