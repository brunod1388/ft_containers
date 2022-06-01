/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/06/01 19:42:54 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <ostream>
#include <cstddef>
#include "vector_iterator.hpp"
#include "utility.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

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

		typedef typename ft::vector_iterator<T>							iterator;
		typedef typename ft::vector_iterator<const T> const				const_iterator;			//un truc a faire ici avec const
		typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const		const_reverse_iterator;	//un truc a faire ici avec const

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
			for (size_type i = 0; i < _size; i++)  //maybe const
				alloc.construct(_data + i, value);
		}

		// template< class InputIt >   // test and correct if needed
		// vector( InputIt first,
		// 		ft::enable_if<ft::is_integral<InputIt>::value, InputIt>::type last,
		// 		const Allocator& alloc = Allocator() ) :
		// 		_alloc(alloc),
		// 		_size(ft::distance(first, last)),
		// 		_capacity(_size),
		// 		_data(alloc.allocate(_capacity))
		// {
		// 	for (size_type i = 0; i < _size; i++, first++)
		// 		_alloc.construct(_data + i, *first);
		// }

		vector( const vector<T> &other ) :
			_alloc(other._alloc),
			_size(other._size),
			_capacity(other._capacity),
			_data(_alloc.allocate(_capacity))
		{
			for (size_t i = 0; i < _size; i++)
				_alloc.construct(_data + i, other._data[i]);
		}

		vector& operator= (const vector& x)
		{
			clear();
			_alloc.dealocate(_data, _capacity);
			_alloc = Allocator(x._alloc);
			_size = x._size;
			_capacity = x._capacity;
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < size; i++)
				_alloc.construct(_data + i, x._data[i]);
			return *this;
		}

		~vector( void )
		{
			clear();
			_alloc.deallocate(_data, _capacity);
		}

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			return ;
		}


		void assign( size_type count, const T& value )
		{
			if (_capacity < count)
				reserve(count);
			for (size_type i = 0; i < _size; i++)
			{
				if (i < count)
					_data[i] = value;
				else
					_alloc.destroy(_data + i);
			}
		}

		allocator_type get_allocator() const { return _alloc; }

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                     Element access                        ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		reference 		at( size_type pos )
		{
			if (pos >= _size)
				throw std::out_of_range("vector: index out of range");
			return _data[pos];
		}

		const_reference at( size_type pos ) const
		{
			if (pos >= _size)
				throw std::out_of_range("vector: index out of range");
			return _data[pos];
		}

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

		iterator				begin() { return iterator(_data); }
		const_iterator			begin() const { return const_iterator(_data); }
		iterator				end() { return iterator(_data + _size); }
		const_iterator			end() const { return iterator(_data + _size); }
		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const{ return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const{ return const_reverse_iterator(begin()); }

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Capacity                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		bool		empty() const { return _size == 0; }
		size_type	size() const { return _size; }
		size_type	max_size() const { return _alloc.max_size() ; }  //maybe add ram available?
		void		reserve( size_type new_cap )
		{
			if (_capacity > new_cap)
				return;

			if (new_cap > max_size())
				throw std::length_error("New_cap bigger than max_size");

			pointer newData = _alloc.allocate(new_cap);

			for (size_t i = 0; i < _size; i++)
			{
				_alloc.allocate(newData + i, _data[i]);
				_alloc.destroy(_data + i);
			}
			_alloc.deallocate(_data, _capacity);
			_capacity = new_cap;
			_data = newData;
		}

		size_type	capacity() const { return _capacity; }

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Modifiers                          ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		void		clear(void)
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data + i);
			_size = 0;
		}

		iterator	insert( iterator pos, const T& value );
		void		insert( iterator pos, size_type count, const T& value );

		template< class InputIt >
		void	insert( iterator pos, InputIt first, InputIt last );

		iterator	erase( iterator pos )
		{
			_alloc.destroy(&(*pos));

			for (iterator it(pos); it < end() - 1; it++)
				it[0] = it[1];
			_size--;
		}

		iterator	erase( iterator first, iterator last )
		{
			difference_type diff = last - first;

			while (first != end())
			{
				if (first < end() - diff)
					first[0] = first[diff];
				else
					_alloc.destroy(&(*first));
				first++;
			}
			_size -= diff;
			return last - diff;
		}

		void	push_back( const T& value )
		{
			if (_size==capacity)
				reserve(_capacity * 2);   //maybe a different behavour when near max size
			_alloc.allocate(_data + _size++, value);
		}
		void	pop_back()
		{
			if (!_size)
				return;
			_alloc.destroy(_data + --_size);
		}
		void 	resize ( size_type n, value_type val = value_type() );
		
		void swap ( vector& arg )
		{
			std::swap(_size, arg._size);
			std::swap(_capacity, arg._capacity);
			std::swap(_data, arg._data);
			std::swap(_alloc, arg._alloc);
		}

	};	//class vector

	/*===================================================================*/
	/*====                                                           ====*/
	/*====                  Non member function                      ====*/
	/*====                                                           ====*/
	/*===================================================================*/

	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs,const vector<T,Alloc>& rhs )
	{
		return rhs < lhs;
	}

	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs,const vector<T,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

	// not sur about this, should it be more generic?
	template< class T, class Alloc >
	void swap( vector<T,Alloc>& lhs, vector<T,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}

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