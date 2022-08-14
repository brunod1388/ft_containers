/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:46:42 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/09 19:33:51 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include <iostream>
#include <functional>
#include <cstddef>
#include "bidirectional_iterator.hpp"
#include "utility.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

namespace ft
{
	/*-------------------------------------------------------------------------
	*                       ft::_RBTree fct list
	*
	* - Element Access
	*	operator[]:					access or _insertNode element
	*	getRoot():					returns root
	*	_getNode(const Key&):			returns node corresponding to key  TO MODIFY WITH KEZ_COMPARE
	*	first():					returns smallest node
	*	last():						returns biggest node
	*
	* - Modifiers
	*	_insertNode(const Key&)			_insertNode node by key
	*	deleteKey(const Key&)			delete node by key
	*	_deleteNode(const node_ptr&)	delete node by node_ptr
    *
	*	PUBLIC
	*
	* - Coplien form
	*	(constructor):				Constructs the _RBTree
	*	(destructor)				Destructs the _RBTree
	*
    * - Capacity:
    *	empty(): 					Test whether container is empty
    *	size(): 					Return container size
     *	max_size(): 				Return maximum size
	*	operator=:					assigns values to the container
	*
	 * - Modifiers:
     *	insert: 		Insert elements
     *	erase: 			Erase elements
     *	swap: 			Swap content
     *	clear: 			Clear content
	*
     * - Operations:
     *	find: 			Get iterator to element
     *	count: 			Count elements with a specific key
     *	lower_bound: 	Return iterator to lower bound
     *	upper_bound: 	Return iterator to upper bound
     *	equal_range  	Get range of equal elements
	*
     * - Observers:
     *	key_comp: 		Return key comparison object
     *	value_comp: 	Return value comparison object   * - Iterators:
    *
	* - Iterators:
	*	begin(): 					Return iterator to beginning
    *	end(): 						Return iterator to end
    *	rbegin(): 					Return reverse iterator to reverse beginning
    *	rend(): 					Return reverse iterator to reverse end
	*
	* - Optional (must define TEST)
	*	printTree()					print _RBTree
	*	print()						print _RBTree
	*-------------------------------------------------------------------------*/

	template<
		class Key,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator<Key> >
	class _RBTree
	{
	private:
		typedef enum {BLACK, RED} 		_color_type;

		/*-------------------------------------------------------------------------
		*                       ft::_RBNode fct list
		*
		* - Coplien form
		*	(constructor):		Constructs the _RBTree
		*	(destructor)		Destructs the _RBTree
		*	operator=:			assigns values to the container
		*
		* - Element Access
		*	getRoot():			returns root
		*	next():				return the next node
		*	previous():			return the prev node
		*	mini():				return the min node
		*	maxi():				return the max node
		*
		* - Operator:
		*	== / !=				relational operator for _RBNodes
		*-------------------------------------------------------------------------*/
		struct _RBNode
		{
			typedef Key		value_type;
			typedef Key&	reference;
			typedef Key*	pointer;

			Key			content;
			_RBNode*	parent;
			_color_type	color;
			_RBNode*	left;
			_RBNode*	right;

			_RBNode(const Key& content = Key(),
				   	_RBNode* parent = NULL,
				   	_color_type color = BLACK,
				   	_RBNode* left = NULL,
				   	_RBNode* right = NULL) :
				content(content),
				parent(parent),
				color(color),
				left(left),
				right(right)
			{}

			~_RBNode(void) {}

			reference	operator*(void) const { return content; }
			pointer		operator->(void) const { return &content; }

			bool	operator==(const _RBNode &rhs)
			{
				return (parent == rhs.parent) && (left == rhs.left) && (right == rhs.right);
			}

			bool	operator!=(const _RBNode &rhs) { return !(*this == rhs); }

			/*===================================================================*/
			/*====                     Element access                        ====*/
			/*===================================================================*/
			_RBNode*	mini(void) { return (left ? left->mini() : this); }
			_RBNode*	maxi(void) { return (right ? right->maxi() : this); }

			_RBNode*	previous(void)
			{
				if (left)
					return left->maxi();

				_RBNode* n = this;
				_RBNode* p = n->parent;

				while (p && n == p->left)
				{
					n = p;
					p = p->parent;
				}
				return (p);
			}

			_RBNode*	next(void)
			{
				if (right)
					return right->mini();

				_RBNode* n = this;
				_RBNode* p = n->parent;

				while (p && n == p->right)
				{
					n = p;
					p = p->parent;
				}
				return (p);
			}

		}; // struct _RBNode -------------------------------------------------------


	public:
		typedef Key																value_type;
		typedef size_t															size_type;
		typedef ptrdiff_t														difference_type;
		typedef Compare															key_compare;
		typedef Allocator														allocator_type;

		typedef value_type&														reference;
		typedef const value_type&												const_reference;
		typedef value_type*														pointer;
		typedef const value_type*												const_pointer;

		typedef struct _RBNode													node_type;
		typedef struct _RBNode*													node_ptr;
		typedef typename Allocator::template rebind<node_type>::other			_RBNodeAllocator;

		typedef typename ft::BidirectionalIterator<node_type, value_type>		iterator;
		typedef typename ft::BidirectionalIterator<node_type, const value_type>	const_iterator;			//un truc a faire ici avec const
		typedef typename ft::BidirectionalIterator_reverse<iterator>			reverse_iterator;
		typedef typename ft::BidirectionalIterator_reverse<const_iterator>		const_reverse_iterator;

	private:
		_RBNodeAllocator	_nodeAlloc;
		allocator_type		_alloc;
		key_compare			_comp;
		node_ptr			_root;
		size_type			_size;

		node_ptr	_newNode(const_reference content)
		{
			node_ptr	n = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(n, _RBNode(content));

			return n;
		}

		node_ptr getRoot() const { return _root; }

		void _del_RBNode(_RBNodeAllocator &alloc, node_ptr n) const
		{
			alloc.destroy(n);
			alloc.deallocate(n, 1);
		}

		void _printNode(node_type *root, std::string indent = "", bool isR = true) const
		{
			if (!root)
				return ;
			std::cout << indent;
			if (isR)
			{
				std::cout << "R----";
				indent += "    ";
			}
			else
			{
				std::cout << "L----";
				indent += "|  ";
			}
			std::cout << root->content << "(" << (root->color == BLACK ? "BLACK" : "\033[0;31mRED\033[0m") << ")" << std::endl;
			_printNode(root->left, indent, false);
			_printNode(root->right, indent, true);
		}

		void	_leftRotate(node_ptr n)
		{
			node_ptr	x = n;
			node_ptr	y = n->right;
			node_ptr	p = x->parent;
			node_ptr	b = y->left;

			x->right = b;
			if (b)
				b->parent = x;
			y->parent = p;
			if (!p)
				_root = y;
			else if (p->right == x)
				p->right = y;
			else
				p->left = y;
			y->left = x;
			x->parent = y;
		}

		void	_rightRotate(node_ptr n)
		{
			node_ptr	x = n->left;
			node_ptr	y = n;
			node_ptr	p = y->parent;
			node_ptr	b = x->right;

			x->right = y;
			if (b)
				b->parent = y;
			x->parent = p;
			if (!p)
				_root = x;
			else if (p->right == y)
				p->right = x;
			else
				p->left = x;
			y->left = b;
			y->parent = x;
		}

		void _insertFix(node_ptr newNode)
		{
			node_ptr uncle;

			while (newNode->parent->color == RED)
			{
				if (newNode->parent == newNode->parent->parent->right)
				{
					uncle = newNode->parent->parent->left;
					if (uncle && uncle->color == RED)
					{
						uncle->color = BLACK;
						newNode->parent->color = BLACK;
						newNode->parent->parent->color = RED;
						newNode = newNode->parent->parent;
					}
					else
					{
						if (newNode == newNode->parent->left)
						{
							newNode = newNode->parent;
							_rightRotate(newNode);
						}
						newNode->parent->color = BLACK;
						newNode->parent->parent->color = RED;
						_leftRotate(newNode->parent->parent);
					}
				}
				else
				{
					uncle = newNode->parent->parent->right;

					if (uncle && uncle->color == RED)
					{
						uncle->color = BLACK;
						newNode->parent->color = BLACK;
						newNode->parent->parent->color = RED;
						newNode = newNode->parent->parent;
					}
					else
					{
						if (newNode == newNode->parent->right) {
							newNode = newNode->parent;
							_leftRotate(newNode);
						}
						newNode->parent->color = BLACK;
						newNode->parent->parent->color = RED;
						_rightRotate(newNode->parent->parent);
					}
				}
				if (newNode == _root)
					break;
			}
   		_root->color = BLACK;
  		}

		void	_deleteFix(node_ptr x)
		{
			node_ptr	bro;

			while (x && x != _root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					bro = x->parent->right;
					if (bro->color == RED)
					{
						bro->color = BLACK;
						x->parent->color = RED;
						_leftRotate(x->parent);
						bro = x->parent->right;
					}

					if (bro->right->color == BLACK && bro->left->color == BLACK)
					{
						bro->color = RED;
						x = x->parent;
					}
					else
					{
						if (bro->right->color == BLACK)
						{
							bro->left->color = BLACK;
							bro->color = RED;
							_rightRotate(bro);
							bro = x->parent->right;
						}
						bro->color = x->parent->color;
						x->parent->color = BLACK;
						bro->right->color = BLACK;
						_leftRotate(x->parent);
						x = _root;
					}
				}
				else
				{
					bro = x->parent->left;
					if (bro->color == RED)
					{
						bro->color = BLACK;
						x->parent->color = RED;
						_rightRotate(x->parent);
						bro = x->parent->left;
					}
					if (bro->right->color == BLACK && bro->right->color == BLACK)
					{
						bro->color = RED;
						x = x->parent;
					}
					else
					{
						if (bro->left->color == BLACK)
						{
							bro->right->color = BLACK;
							bro->color = RED;
							_leftRotate(bro);
							bro = x->parent->left;
						}
						bro->color = x->parent->color;
						x->parent->color = BLACK;
						bro->left->color = BLACK;
						_rightRotate(x->parent);
						x = _root;
					}
				}
			}
			if (x)
				x->color = BLACK;
		}

		void	_transplant(node_ptr x, node_ptr y)
		{
			if (!x->parent)
				_root = y;
			else if (x->parent->left == x)
				x->parent->left = y;
			else
				x->parent->right = y;
			if (y)
				y->parent = x->parent;
		}

		void	_clearNode(_RBNodeAllocator &alloc, node_ptr n) const
		{
			if (!n)
				return ;
			if (n->left)
				_clearNode(alloc, n->left);
			if (n->right)
				_clearNode(alloc, n->right);
			_del_RBNode(alloc, n);
		}


		node_ptr _getNode(const_reference key) const
		{
			node_ptr current = _root;

			while (current)
			{
				if (!_comp(key, current->content) && !_comp(current->content, key))
					return current;
				if (_comp(key, current->content))
					current = current->left;
				else
					current = current->right;
			}
			return current;
		}

		iterator _insertNode(const_reference key, node_ptr hint = NULL)
		{
			if (_getNode(key))
				return iterator(NULL, _root);

			node_ptr current = hint ? hint : _root;
			node_ptr parent = NULL;
			node_ptr newNode = _newNode(key);
			
			_size++;
			newNode->color = RED;
			while (current)
			{
				parent = current;
				if (_comp(key, current->content))
					current = current->left;
				else
					current = current->right;
			}
			newNode->parent = parent;
			if (!parent)
				_root = newNode;
			else if (_comp(newNode->content, parent->content))
				parent->left = newNode;
			else
				parent->right = newNode;

			if (!parent)
			{
				newNode->color = BLACK;
				return iterator(newNode, _root);
			}
			if (!parent->parent)
				return iterator(newNode, _root);

			_insertFix(newNode);
			return iterator(newNode, _root);
		}

		int	_deleteNode(const node_ptr toDelete)
		{
			_color_type		original_color;
			node_ptr		x, y;

			if (!toDelete)
				return 0;

			original_color = toDelete->color;
			if (!toDelete->left)
			{
				x = toDelete->right;
				_transplant(toDelete, x);
			}
			else if (!toDelete->right)
			{
				x = toDelete->left;
				_transplant(toDelete, x);
			}
			else
			{
				y = toDelete->right->mini();
				original_color = y->color;
				x = y->right;
				if (x && y->parent == toDelete)
					x->parent = y;
				else
				{
					_transplant(y, y->right);
					y->right = toDelete->right;
					if (y->right)
						y->right->parent = y;
				}
				_transplant(toDelete, y);
				y->left = toDelete->left;
				y->left->parent = y;
				y->color = toDelete->color;
			}
			_del_RBNode(_nodeAlloc, toDelete);
			if (original_color == BLACK)
				_deleteFix(x);
			_size--;
			return 1;
		}

public:
		/*===================================================================*/
		/*====                     Constructor                           ====*/
		/*===================================================================*/

		_RBTree(const key_compare& comp = key_compare(), const Allocator alloc = Allocator()) :
			_nodeAlloc(_RBNodeAllocator(Allocator())),
			_alloc(alloc),
			_comp(comp),
			_root(NULL),
			_size(0)
		{}

		template< class InputIt >
		_RBTree( InputIt first, InputIt last,
			const key_compare& comp = key_compare(),
			const Allocator& alloc = Allocator() ) :
			_nodeAlloc(_RBNodeAllocator(Allocator())),
			_alloc(alloc),
			_comp(comp),
			_root(NULL),
			_size(0)
		{
			insert(first, last);
		}

		_RBTree(const _RBTree& src) :
			_nodeAlloc(src._nodeAlloc),
			_alloc(src._alloc),
			_comp(src._comp),
			_root(NULL),
			_size(0)
		{ insert(src.begin(), src.end()); }

		~_RBTree(void) { _clearNode(_nodeAlloc, _root); }

		_RBTree& operator=(const _RBTree& rhs)
		{
			if (this == &rhs)
				return *this;

			_clearNode(_nodeAlloc, _root);
			_nodeAlloc = rhs._nodeAlloc;
			_comp = rhs._comp;
			_alloc = rhs._alloc;
			insert(rhs.begin(), rhs.end());
			return *this;
		}

		allocator_type get_allocator() const { return _alloc; }

		/*===================================================================*/
		/*====                     Capacity                              ====*/
		/*===================================================================*/

		bool		empty(void) const	{ return _root ? true : false; }
		size_type	size(void) const	{ return _size; }
		size_type	max_size() const	{ return _nodeAlloc.max_size(); }  //maybe add ram available?

		/*===================================================================*/
		/*====                        Modifiers                          ====*/
		/*===================================================================*/

		void	clear(void)
		{
			if (!_root)
				return ;
			_clearNode(_nodeAlloc, _root);
			_root = NULL;
			_size = 0;
		}

		ft::pair<iterator, bool> insert( const_reference value )
		{
			iterator	it = _insertNode(value);
			bool		b = it.base() ? true : false;

			if (!it.base())
				it = iterator(_getNode(value), _root);
			return ft::pair<iterator, bool>(it, b);
		}

		iterator insert( iterator hint, const_reference value ) { return _insertNode(value, hint.base()); }

		template< class InputIt >
		void insert( InputIt first, InputIt last )
		{
			while (first != last)
				_insertNode(*(first++));
		}

		void erase( iterator pos ) { _deleteNode(pos.base()); }

		void erase( iterator first, iterator last )
		{
			while (first != last)
				_deleteNode((first++).base());
		}

		size_type erase( const_reference key )
		{
			return _deleteNode(_getNode(key));
		}

		void swap( _RBTree& other )
		{
			std::swap(_nodeAlloc, other._nodeAlloc);
			std::swap(_alloc, other._alloc);
			std::swap(_comp, other._comp);
			std::swap(_root, other._root);
			std::swap(_size, other._size);
		}

		/*===================================================================*/
		/*====                        Lookup                             ====*/
		/*===================================================================*/

		size_type count( const_reference key ) const { return (_getNode(key) ? 1 : 0); }

		iterator find( const_reference key ) { return iterator(_getNode(key), _root); }
		const_iterator find( const_reference key ) const { return const_iterator(_getNode(key), _root); }

		iterator lower_bound( const_reference key )
		{
			node_ptr node = _root ? _root->mini() : NULL;

			if (!node)
				return (iterator(node, _root));

			while (node && _comp(node->content, key))
				node = node->next();
			return (iterator(node, _root));
		}

		const_iterator lower_bound( const_reference key ) const
		{
			node_ptr node = _root ? _root->mini() : NULL;

			if (!node)
				return (iterator(node, _root));

			while (node && _comp(node->content, key))
				node = node->next();
			return (const_iterator(node, _root));
		}

		iterator upper_bound( const_reference key )
		{
			node_ptr node = lower_bound(key).base();

			if (node && !_comp(key, node->content))
				node = node->next();
			return (iterator(node, _root));
		}

		const_iterator upper_bound( const_reference key ) const
		{
			node_ptr node = lower_bound(key).base();

			if (node && !_comp(key, node->content))
				node = node->next();
			return (const_iterator(node, _root));
		}

		ft::pair<iterator,iterator> equal_range( const_reference key )
		{
			return ft::pair<iterator,iterator>(lower_bound(key), upper_bound(key));
		}

		ft::pair<const_iterator,const_iterator> equal_range( const_reference key ) const
		{
			return ft::pair<const_iterator,const_iterator>(lower_bound(key), upper_bound(key));
		}

		/*===================================================================*/
		/*====                       Observers                           ====*/
		/*===================================================================*/

		key_compare		key_comp() const { return _comp; }

		/*===================================================================*/
		/*====                        Iterator                           ====*/
		/*===================================================================*/

		iterator				begin(void) 		{ return iterator(_root ? _root->mini() : NULL, _root); }
		iterator				end(void) 			{ return iterator(NULL , _root); }
		reverse_iterator		rbegin(void)		{ return reverse_iterator(--end()); }
		reverse_iterator		rend(void)			{ return reverse_iterator(--begin()); }

		const_iterator			begin(void) const	{ return const_iterator(_root ? _root->mini() : NULL, _root); }
		const_iterator			end(void) const		{ return const_iterator(NULL , _root); }
		const_reverse_iterator	rbegin(void) const	{ return const_reverse_iterator(--end()); }
		const_reverse_iterator	rend(void) const	{ return const_reverse_iterator(--begin()); }

#ifdef TEST
		void	printTree(void)
		{
			_printNode(_root);
			std::cout << "size : " << _size << std::endl;
		}

		void	print() const
		{
			node_ptr	current = _root ? _root->mini() : NULL;
			std::cout << "content : ";
			while (current)
			{
				std::cout << current->content << " ";
				current = current->next();
			}
			std::cout << std::endl;
			std::cout << "size :" << size() << std::endl;
		}
#endif
	}; // class _RBTree

} // namespace ft

#endif
