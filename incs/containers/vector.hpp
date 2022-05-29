/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/05/28 02:47:50 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "vector_iterator.hpp"
#include "vector_rev_iterator.hpp"


namespace ft{

	template <class T, class Allocator = std::allocator<T>>
	class vector{

	public:
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef size_t									size_type;
		typedef ptrdiff_t								difference_type;

		typedef T&										reference;
		typedef const T&								const_reference;
		typedef T*										pointer;
		typedef const T*								const_pointer;

		typedef typename ft::vector_iterator<T>			iterator;
		typedef typename ft::vector_iterator<T>			const_iterator;			//un truc a faire ici avec const
		typedef typename ft::vector_rev_iterator<T>		reverse_iterator;
		typedef typename ft::vector_rev_iterator<T>		const_reverse_iterator;	//un truc a faire ici avec const

	private:
		Allocator	_alloc;
		size_type	_size;

	public:
		/*===================================================================
		/*====                                                           ====
		/*====                     Member Function                       ====
		/*====                                                           ====
		/*===================================================================
		*/
		vector<T>(void)
		{
			std::cout << "test vector" << std::endl;
		}
		vector<T>(const vector<T> &src);
		vector<T>(T &val);
		~vector(void){}

		void assign( size_type count, const T& value );
		allocator_type get_allocator() const;

		/*===================================================================
		/*====                                                           ====
		/*====                     Element access                        ====
		/*====                                                           ====
		/*===================================================================
		*/
		reference 		at( size_type pos );
		const_reference at( size_type pos ) const;
		reference 		operator[]( size_type pos );
		const_reference operator[]( size_type pos ) const;
		reference 		front();
		const_reference front() const;
		reference 		back();
		const_reference back() const;

		/*===================================================================
		/*====                                                           ====
		/*====                        Iterator                           ====
		/*====                                                           ====
		/*===================================================================
		*/

		iterator		begin();
		const_iterator	begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		/*===================================================================
		/*====                                                           ====
		/*====                        Capacity                           ====
		/*====                                                           ====
		/*===================================================================
		*/
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		void reserve( size_type new_cap );
		size_type capacity() const;

		/*===================================================================
		/*====                                                           ====
		/*====                        Modifiers                           ====
		/*====                                                           ====
		/*===================================================================
		*/
		void clear();
		iterator insert( iterator pos, const T& value );
		void insert( iterator pos, size_type count, const T& value );

		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last );

		iterator erase( iterator pos );
		iterator erase( iterator first, iterator last );
		void push_back( const T& value );
		void pop_back();
		void resize( size_type count, T value = T() );
		void swap( vector& other );

	};	//class vector

	/*===================================================================
	/*====                                                           ====
	/*====                  Non member function                      ====
	/*====                                                           ====
	/*===================================================================
	*/
	template< class T, class Alloc >
	bool operator==( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator!=( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator<( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator<=( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator>( const std::vector<T,Alloc>& lhs,const std::vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator>=( const std::vector<T,Alloc>& lhs,const std::vector<T,Alloc>& rhs );

	// not sur about this, should it be more generic?
	template< class T, class Alloc >
	void swap( std::vector<T,Alloc>& lhs, std::vector<T,Alloc>& rhs );

};	//namespace ft


#endif