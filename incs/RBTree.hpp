/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:46:42 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/12 01:15:25 by brunodeoliv      ###   ########.fr       */
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
	*                       ft::RBTree fct list
	*
	* - Coplien form
	*	(constructor):		Constructs the RBTree
	*	(destructor)		Destructs the RBtree
	*	operator=:			assigns values to the container
	*
	* - Element Access
	*	operator[]:			access or insert element
	*	getRoot():			returns root
	*	getNode(const T&):	returns node corresponding to key  TO MODIFY WITH KEZ_COMPARE
	*	first():			returns smallest node
	*	last():				returns biggest node
	*
    * - Capacity:
    *	empty(): 			Test whether container is empty
    *	size(): 			Return container size
     *	max_size(): 		Return maximum size
	*
	* - Modifiers
	*	insert(const T&)	insert node by key
	*	delete(const T&)	delete node by key
	*	clear()				clear TBTree
     *	erase(): 			Erase elements
     *	swap(): 			Swap content
	*
	*	print()				print RBTree
	*
    * - Iterators:
    *	begin(): 			Return iterator to beginning
    *	end(): 				Return iterator to end
     *	rbegin(): 			Return reverse iterator to reverse beginning
     *	rend(): 			Return reverse iterator to reverse end
	*-------------------------------------------------------------------------*/

	template<
		class T,
		class Compare = std::less<T>,
		class Allocator = std::allocator<T> >
	class RBTree
	{
	public:
		typedef T												value_type;
		typedef size_t											size_type;
		typedef ptrdiff_t										difference_type;
		typedef Compare											compare;
		typedef Allocator										allocator_type;

		typedef T&												reference;
		typedef const T&										const_reference;
		typedef T*												pointer;
		typedef const T*										const_pointer;

		typedef enum {BLACK, RED} 								color_type;

		/*-------------------------------------------------------------------------
		*                       ft::RBNode fct list
		*
		* - Coplien form
		*	(constructor):		Constructs the RBTree
		*	(destructor)		Destructs the RBtree
		*	operator=:			assigns values to the container
		*
		* - Element Access
		*	getRoot():			returns root
		*	next():				return the next node
		*	prev():				return the prev node
		*
		* - Operator:
		*	== / !=				relational operator for RBNodes
		*-------------------------------------------------------------------------*/
		struct RBNode
		{
			typedef T									value_type;

			T			content;
			RBNode*		parent;
			color_type	color;
			RBNode*		left;
			RBNode*		right;

			RBNode(T content = T(),
				   RBNode *parent = NULL,
				   color_type color = BLACK,
				   RBNode *left = NULL,
				   RBNode *right = NULL) :
				content(content),
				parent(parent),
				color(color),
				left(left),
				right(right)
			{}

			RBNode(const RBNode &src) { *this = src; }
			~RBNode(void) {}

			RBNode&	operator=(const RBNode &rhs)
			{
				if (this != &rhs)
				{
					parent = rhs.parent;
					left = rhs.left;
					right = rhs.right;
					content = rhs.content;
					color = rhs.color;
				}
				return *this; 
			}

			reference	operator*(void) const { return content; }
			pointer		operator->(void) const { return &content; }

			bool	operator==(const RBNode &rhs)
			{
				return (parent == rhs.parent) && (left == rhs.left) && (right == rhs.right);
			}

			bool	operator!=(const RBNode &rhs)
			{
				return !(*this == rhs);
			}

			RBNode* getRoot(void)
			{
				RBNode*	root = this;
				RBNode*	parent = root->parent;

				while(parent)
				{
					root = parent;
					parent = parent->parent;
				}

				return root;
			}

			/*===================================================================*/
			/*====                     Element access                        ====*/
			/*===================================================================*/
			RBNode*	mini(void)
			{
				if (left)
					return left->mini();
				return this;
			}

			RBNode*	maxi(void)
			{
				if (right)
					return right->maxi();
				return this;
			}

			RBNode*	previous(void)
			{
				if (left)
					return left->maxi();

				RBNode* n = this;
				RBNode* p = n->parent;

				while (p && n == p->left)
				{
					n = p;
					p = p->parent;
				}
				return (p == this ? NULL : p);
			}

			RBNode*	next(void)
			{
				if (right)
					return right->mini();

				RBNode* n = this;
				RBNode* p = n->parent;

				while (p && n == p->right)
				{
					n = p;
					p = p->parent;
				}
				return (p == this ? NULL : p);
			}

		}; // struct RBNode -------------------------------------------------------

		typedef struct RBNode										node;
		typedef struct RBNode*										node_pointer;

		typedef typename Allocator::template rebind<node>::other	RBNodeAllocator;

		typedef typename ft::bidirectional_iterator<node, T>		iterator;
		typedef typename ft::bidirectional_iterator<node, const T>	const_iterator;			//un truc a faire ici avec const
		// typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		// typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:

		RBNodeAllocator	_alloc;
		node_pointer	_root;
		size_type		_size;

		node_pointer	_newNode(T content, RBNodeAllocator &alloc)
		{
			node_pointer	n = alloc.allocate(1);
			alloc.construct(n, RBNode(content));

			return n;
		}

		void _delRBNode(RBNodeAllocator &alloc, node_pointer n)
		{
			alloc.destroy(n);
			alloc.deallocate(n, 1);
		}

		void _printNode(node *root, std::string indent = "", bool isR = true)
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
			std::cout << root->content << "(" << (root->color == BLACK ? "BLACK" : "RED") << ")" << std::endl;
			_printNode(root->left, indent, false);
			_printNode(root->right, indent, true);
		}

		/*========================================================*/
		/*==				  Left Rotation						==*/
		/*==        p								p			==*/
		/*==		|								|			==*/
		/*==		X								Y			==*/
		/*==	   / \							   / \			==*/
		/*==      a   Y				=>			  X   c			==*/
		/*==		 / \						 / \			==*/
		/*==		b   c						a   b			==*/
		/*========================================================*/

		void	_leftRotate(node_pointer n)
		{
			node_pointer	x = n;
			node_pointer	y = n->right;
			node_pointer	p = x->parent;
			node_pointer	b = y->left;

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

		/*========================================================*/
		/*==				  Right Rotation					==*/
		/*==        p								p			==*/
		/*==		|								|			==*/
		/*==		Y								X			==*/
		/*==	   / \							   / \			==*/
		/*==      X   a				=>			  c   Y			==*/
		/*==	 / \								 / \		==*/
		/*==	c   b								b   a		==*/
		/*========================================================*/
		void	_rightRotate(node_pointer n)
		{
			node_pointer	x = n->left;
			node_pointer	y = n;
			node_pointer	p = y->parent;
			node_pointer	b = x->right;

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

		void _insertFix(node *newNode)
		{
			node_pointer	uncle;
			node_pointer	parent;

			while (newNode->parent->color == RED)
			{
				parent = newNode->parent;

				if (parent == parent->parent->left)
				{
					uncle = parent->parent->right;

					if (uncle && uncle->color == RED)
					{
						uncle->color = BLACK;
						parent->color = BLACK;
						parent->parent->color = RED;
						newNode = parent->parent;
					}
					else
					{
						if (newNode == parent->right)
						{
							newNode = parent;
							_leftRotate(newNode);
						}
						parent->color = BLACK;
						parent->parent->color = RED;
						_rightRotate(parent->parent);
					}
				}
				else
				{
					uncle = parent->parent->left;

					if (uncle && uncle->color == RED)
					{
						uncle->color = BLACK;
						parent->color = BLACK;
						parent->parent->color = RED;
						newNode = parent->parent;
					}
					else
					{
						if (newNode == parent->left)
						{
							newNode = parent;
							_rightRotate(newNode);
						}
						parent->color = BLACK;
						parent->parent->color = RED;
						_leftRotate(parent->parent);
					}
				}
				if (newNode == _root)
					break;
			}
			_root->color = BLACK;
		}

	void	_deleteFix(node_pointer x)
	{
		node_pointer	bro;

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
				else if (bro->right->color == BLACK)
				{
					bro->left->color = BLACK;
					bro->color = RED;
					_rightRotate(bro);
					bro = x->parent->right;
				}
				else
				{
					bro->color = x->parent->color;
					x->parent->color = BLACK;
					bro->right->color = BLACK;
					_leftRotate(x);
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
				if (bro->left->color == BLACK && bro->right->color == BLACK)
				{
					bro->color = RED;
					x = x->parent;
				}
				else if (bro->left->color == BLACK)
				{
					bro->right->color = BLACK;
					bro->color = RED;
					_leftRotate(bro);
					bro = x->parent->left;
				}
				else
				{
					bro->color = x->parent->color;
					x->parent->color = BLACK;
					bro->left->color = BLACK;
					_rightRotate(x);
					x = _root;
				}
			}
		}
		if (x)
			x->color = BLACK;
	}

	void	_transplant(node_pointer x, node_pointer y)
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

	node_pointer _copy(node_pointer n)
	{
		if (n == NULL)
			return NULL;

		node_pointer newNode = new node(n);
		newNode->left = copy(n->left);
		newNode->right = copy(n->right);
		newNode->left->parent = newNode;
		newNode->right->parent = newNode;
		return newNode;
	}

	void	_clearNode(RBNodeAllocator &alloc, node_pointer n)
	{
		if (n->left)
			_clearNode(alloc, n->left);
		if (n->right)
			_clearNode(alloc, n->right);
		_delRBNode(alloc, n);
	}

	public:
		/*===================================================================*/
		/*====                                                           ====*/
		/*====                     Constructor                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		RBTree(void) :
			_alloc(RBNodeAllocator()),
			_root(NULL),
			_size(0)
		{}

		RBTree(const T& src)
		{
			*this = src;
		}

		~RBTree(void) { clear(); }

		RBTree&	operator=(const RBTree& rhs)
		{
			if (this != &rhs)
			{
				_clearNode(_root);
				_alloc = rhs._alloc;
				_root = rhs._copy(rhs._root);
				_size = rhs._size;
			}
			return *this;
		}

		/*===================================================================*/
		/*====                     Element access                        ====*/
		/*===================================================================*/

		node_pointer getRoot(void) { return _root; }

		node_pointer getNode(const T&key)
		{
			node_pointer current = _root;

			while (current)
			{
				if (current->content == key)
					return current;
				if (key < current->content) // maybe <= because of deletion in case of doubles....
					current = current->left;
				else
					current = current->right;
			}
			return current;
		}

		node_pointer	first()	const
		{
			if (!_root)
				return NULL;
			return _root->mini();
		}

		node_pointer	last() const
		{
			if (!_root)
				return NULL;
			return _root->maxi();
		}
		/*===================================================================*/
		/*====                     Element access                        ====*/
		/*===================================================================*/

		bool		empty(void) { return _root ? true : false; }
		size_type	size(void) { return _size; }
		size_type	max_size() const { return _alloc.max_size(); }  //maybe add ram available?

		/*===================================================================*/
		/*====                        Modifiers                          ====*/
		/*===================================================================*/

		void insert(const T& key)
		{
			node_pointer newNode = _newNode(key, _alloc);
			node_pointer current = _root;
			node_pointer parent = NULL;

			_size++;
			newNode->color = RED;
			while (current)
			{
				parent = current;
				if (key < current->content)
					current = current->left;
				else
					current = current->right;
			}

			newNode->parent = parent;
			if (!parent)
				_root = newNode;
			else if (newNode->content < parent->content)
				parent->left = newNode;
			else
				parent->right = newNode;

			if (!parent)
			{
				newNode->color = BLACK;
				return ;
			}
			if (!parent->parent)
				return ;

			_insertFix(newNode);
		}

		bool	deleteKey(const T&key)
		{
			node_pointer		toDelete = getNode(key);
			color_type			original_color;
			node_pointer		x, y;

			if (!toDelete)
				return false;

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
			_delRBNode(_alloc, toDelete);
			if (original_color == BLACK)
				_deleteFix(x);
			_size--;
			return true;
		}

		void	clear(void)
		{
			_clearNode(_alloc, _root);
			_root = NULL;
			_size = 0;
		}

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Iterator                           ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		iterator		begin(void) 		{ return iterator(_root->mini()); }
		iterator		end(void) 			{ return iterator(NULL); }
		const_iterator	begin(void) const	{ return const_iterator(_root->mini()); }
		const_iterator	end(void) const		{ return const_iterator(NULL); }

		// reverse_iterator		rbegin(void);
		// const_reverse_iterator	rbegin(void) const;
		// reverse_iterator		rend(void);
		// const_reverse_iterator	rend(void) const;

		void	print(void)
		{
			_printNode(_root);
			std::cout << "size : " << _size << std::endl;
		}

	}; // class RBTree

} // namespace ft

#endif
