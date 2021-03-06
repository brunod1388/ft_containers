/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/09 02:34:21 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>   //TODELETE

#include <memory>
#include <ostream>
#include <cstddef>
#include "vector_iterator.hpp"
#include "utility.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

namespace ft{

	/*-------------------------------------------------------------------------
	*							ft::vector<T>
	*
	* - Coplien form:
	* 	(constructor):	Construcucts the vector
	*					vector()
	*					vector( const Allocator& )
	*					vector( size_type count,
	*					 		const T& value = T(),
	*					 		const Allocator& alloc = Allocator())
	*					vector( InputIt first,
	*							InputIt last,
	*							const Allocator& alloc = Allocator() )
	*					vector( const vector &other )
	*
	* 	(destructor):	Destructs the vector
	*					~vector( void )
	*
	* 	operator=:		assigns values to the container
	*					vector& operator= (const vector& x)
	*
	* - Iterators:
	* 	begin:			return iterator to beginning
	* 	end:			return iterator to end
	* 	rbegin:			return reverse iterator to reverse beginning
	* 	rend:			return reverse iterator to reverse end
	*
	*
    * - Capacity:
    * 	size:			Return size
    * 	max_size:		Return maximum size
    * 	resize:			Change size
    * 	capacity:		Return size of allocated storage capacity
    * 	empty:			Test whether vector is empty
    * 	reserve:		Request a change in capacity
    *
    * - Element access:
    *	operator[]:		Access element
    *	at:				Access element
    *	front:			Access first element
    *	back:			Access last element
    *
    * - Modifiers:
    * 	assign:			Assign vector content
	*					void assign ( InputIt first, InputIt last )
	*					void assign( size_type count, const T& value )
    * 	push_back:		Add element at the end
    * 	pop_back:		Delete last element
    * 	insert:			Insert elements
    * 	erase:			Erase elements
    * 	swap:			Swap content
    * 	clear:			Clear content
    *
    * - Non-member function overloads:
    *	relational operators: Relational operators for vector
    *	swap:                 Exchange contents of two vectors
	*-------------------------------------------------------------------------*/

	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
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
		typedef typename ft::vector_iterator<const T>					const_iterator;			//un truc a faire ici avec const
		typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;	//un truc a faire ici avec const

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
			_data(NULL)
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
			_data(_alloc.allocate(_capacity))
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_data + i, value);
		}

		template< class InputIt >
		vector( InputIt first,
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last,
				const Allocator& alloc = Allocator() ) :
				_alloc(alloc),
				_size(ft::distance(first, last)),
				_capacity(_size),
				_data(_alloc.allocate(_capacity))
		{
			for (size_type i = 0; i < _size; i++, first++)
				_alloc.construct(_data + i, *first);
		}

		vector( const vector &other ) :
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
			if (_capacity < x._capacity || _alloc != x._alloc)
			{
				_alloc.deallocate(_data, _capacity);
				_alloc = Allocator(x._alloc);
				_capacity = x._capacity;
				_data = _alloc.allocate(_capacity);
			}
			_size = x._size;
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_data + i, x._data[i]);
			return *this;
		}

		~vector( void )
		{
			clear();
			_alloc.deallocate(_data, _capacity);
		}

		template <class InputIt>
		void assign ( InputIt first,
					  typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last )
		{
			// size_type	diff = (size_type) (last - first);
			size_type	diff = ft::distance(first, last);

			if (_capacity < diff)
				reserve(diff);
			for (size_type i = 0; first != last; i++, first++)
			{
				if (i < size())
					_data[i] = *first;
				else
					_alloc.construct(_data + i, *first);
			}
			for (size_type i = diff; i < size(); i++)
				_alloc.destroy(_data + i);
			_size = diff;
		}

		void assign( size_type count, const T& value )
		{
			if (_capacity < count)
				reserve(count);
			for (size_type i = 0; i < count || i < _size; i++)
			{
				if (i < count && i < _size)
					_data[i] = value;
				else if (i >= _size && i < count)
					_alloc.construct(_data + i, value);
				else
					_alloc.destroy(_data + i);
			}
			_size = count;
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
		reference 		front()	{ return *begin(); }
		reference 		back()	{ return *(end() - 1); }
		T*				data()	{ return _data; }

		const_reference operator[]( size_type pos ) const { return _data[pos]; }
		const_reference front() const	{ return *begin(); }
		const_reference back() const	{ return *(end() - 1); }
		const T* 		data() const	{ return _data; }

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Iterator                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		iterator				begin()		{ return iterator(_data); }
		iterator				end()		{ return iterator(_data + _size); }
		reverse_iterator		rbegin()	{ return reverse_iterator(end() - 1); }
		reverse_iterator		rend()		{ return reverse_iterator(begin() - 1); }

		const_iterator			begin() const	{ return const_iterator(_data); }
		const_iterator			end() const		{ return const_iterator(_data + _size); }
		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end() - 1); }
		const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin() - 1); }

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Capacity                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		bool		empty() const		{ return _size == 0; }
		size_type	size() const		{ return _size; }
		size_type	max_size() const	{ return _alloc.max_size(); }  //maybe add ram available?
		size_type	capacity() const	{ return _capacity; }

		void		reserve( size_type new_cap )
		{
			if (_capacity > new_cap)
				return;

			if (new_cap >= max_size())
				throw std::length_error("cannot create std::vector larger than max_size()");

			pointer newData = _alloc.allocate(new_cap);

			for (size_t i = 0; i < _size; i++)
			{
				_alloc.construct(newData + i, _data[i]);
				_alloc.destroy(_data + i);
			}
			_alloc.deallocate(_data, _capacity);
			_capacity = new_cap;
			_data = newData;
		}


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

		iterator	insert( iterator pos, const T& value )
		{
			size_type ipos = pos - begin();

			push_back(value);
			for (size_type i = _size - 1; i > ipos; i--)
			{
				_data[i] = _data[i - 1];
			}
			_data[ipos] = value;
			return iterator(_data + ipos);
		}

		void		insert( iterator pos, size_type count, const T& value )
		{
			size_type	ipos = pos - begin();

			if (_size + count > _capacity)
			{
				size_type new_cap = _capacity ? _capacity : 1;
				while (new_cap < _size + count)
					new_cap *= 2;
				reserve(new_cap);
			}
			if (_size && ipos != _size)
			{
				for (size_type i = _size - 1; i >= ipos; i--)
				{
					if (i + count >= _size)
						_alloc.construct(_data + i + count, _data[i]);
					else
						_data[i + count] = _data[i];
					if (i == 0)
						break;
				}
			}
			for (size_t i = ipos; i < ipos + count; i++)
				if (i >= _size)
					_alloc.construct(_data + i, value);
				else
					_data[i] = value;
			_size += count;
		}

		template< class InputIt >
		void	insert( iterator pos,
						typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first,
						InputIt last )
		{
			size_type	count = last - first;
			size_type	ipos = pos - begin();

			if (last <= first)
				return;

			if (_size + count > _capacity)
			{
				size_type new_cap = _capacity ? _capacity : 1;
				while (new_cap < _size + count)
					new_cap *= 2;
				reserve(new_cap);
			}

			if (_size && ipos != _size)
			{
				for (size_type i = _size - 1; i >= ipos; i--)
				{
					if (i + count >= _size)
						_alloc.construct(_data + i + count, _data[i]);
					else
						_data[i + count] = _data[i];
					if (i == 0)
						break;
				}
			}

			for (size_t i = ipos; i < ipos + count; i++, first++)
				if (i >= _size)
					_alloc.construct(_data + i, *first);
				else
					_data[i] = *first;

			_size += count;
		}

		iterator	erase( iterator pos )
		{
			_alloc.destroy(&(*pos));

			for (iterator it(pos); it < end() - 1; it++)
				it[0] = it[1];
			_size--;
			return pos;
		}

		iterator	erase( iterator first, iterator last )
		{
			difference_type diff = last - first;

			if (first == last || first == end())
				return first;
			while (first != end())
			{
				if (first < end() - diff)
					first[0] = first[diff];
				else
					_alloc.destroy(&(*first));
				first++;
			}
			_size -= diff;
			return iterator(&_data[diff]);
		}

		void	push_back( const T& value )
		{
			if (_size == _capacity)
				reserve(_capacity > 0 ? _capacity * 2 : 1);   //maybe a different behavour when near max size

			_alloc.construct(_data + _size++, value);
		}

		void	pop_back()
		{
			if (!_size)
				return;
			_alloc.destroy(_data + --_size);
		}

		void 	resize( size_type n, value_type val = value_type() )
		{
			if (n > _capacity)
				reserve(n);
			for (size_t i = _size; i < n; i++)
				_alloc.construct(_data + i, val);
			for (size_t i = n; i < _size; i++)
				_alloc.destroy(_data + i);
			_size = n;
		}

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