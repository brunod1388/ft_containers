/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:46:42 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/09 00:10:35 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include <iostream>
#include <functional>
#include <cstddef>
// #include "bidirectional_iterator.hpp"
#include "utility.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

namespace ft
{
	/*-------------------------------------------------------------------------*/
	/*                       ft::RBTree fct list                               */
	/*                                                                         */
	/*-Coplien form                                                                         */
	/*(constructor):	                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*                                                                         */
	/*-------------------------------------------------------------------------*/

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

		// typedef typename ft::bidirectional_iterator<T>			iterator;
		// typedef typename ft::bidirectional_iterator<const T>	const_iterator;			//un truc a faire ici avec const
		// typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		// typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef enum {BLACK, RED} 								color_type;

		struct RBNode
		{
			T			content;
			RBNode*		parent;
			color_type	color;
			RBNode*		left;
			RBNode*		right;

			RBNode(T content,
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

			bool	operator==(const RBNode &rhs)
			{
				return (parent == rhs.parent) && (left == rhs.left) && (right == rhs.right);
			}

			bool	operator!=(const RBNode &rhs)
			{
				return !(*this == rhs);
			}

		}; // struct RBNode

		typedef struct RBNode										node;
		typedef struct RBNode*										node_pointer;

		typedef typename Allocator::template rebind<RBNode>::other	RBNodeAllocator;

	private:

		RBNodeAllocator	_alloc;
		node_pointer	_root;

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
		/*====                     Member Function                       ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		RBTree(void) :
			_alloc(RBNodeAllocator()),
			_root(NULL)
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
				_alloc = rhs._alloc;
				_root = rhs._copy(rhs._root);
			}
			return *this;
		}

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                     Element access                        ====*/
		/*====                                                           ====*/
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

		node_pointer	minimum(node_pointer n)
		{
			while (n->left)
				n = n->left;
			return n;
		}

		node_pointer	maximum(node_pointer n)
		{
			while (n->right)
				n = n->right;
			return n;
		}

		node_pointer	previous(node_pointer n)
		{
			if (n->left)
				return maximum(n->left);

			node_pointer prev = n->parent;

			while (prev && n == prev->left)
			{
				n = prev;
				prev = prev->parent;
			}
			return prev;
		}

		node_pointer	next(node_pointer n)
		{
			if (n->right)
				return minimum(n->left);

			node_pointer nxt = n->parent;

			while (nxt && n == nxt->left)
			{
				n = nxt;
				nxt = nxt->parent;
			}
			return nxt;
		}

		/*===================================================================*/
		/*====                                                           ====*/
		/*====                        Modifiers                          ====*/
		/*====                                                           ====*/
		/*===================================================================*/

		void insert(const T& key)
		{
			node_pointer newNode = _newNode(key, _alloc);
			node_pointer current = _root;
			node_pointer parent = NULL;

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
				y = minimum(toDelete->right);
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
			return true;
		}

		void	clear(void)
		{
			_clearNode(_alloc, _root);
			_root = NULL;
		}

		void	print(void) { _printNode(_root); }

	}; // class RBTree

} // namespace ft

#endif
