/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:46:42 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/06/18 04:11:22 by brunodeoliv      ###   ########.fr       */
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

	private:

		typedef struct RBNode
		{
			T			content;
			RBNode*		parent;
			color_type	color;
			RBNode*		left;
			RBNode*		right;

			RBNode(T content,
				   RBNode *parent,
				   color_type color = "BLACK",
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

		}	node; // struct RBNode

		typedef typename Allocator::template rebind<RBNode>::other RBNodeAllocator;

		RBNodeAllocator	_alloc;
		node*			_root;
		size_type		_size;

		node*	_newNode(T content,
						 RBNode *parent = NULL,
						 color_type color = BLACK,
						 RBNode *left = NULL,
						 RBNode *right = NULL)
		{
			node*	node = _alloc.allocate(1);
			_alloc.construct(node, RBNode(content, parent, color, left, right));

			return node;
		}

		void _delRBNode(const RBNodeAllocator &alloc, RBNode* node)
		{
			alloc.destroy(node);
			alloc.deallocate(node, 1);
		}

		void print_node(node *root, std::string indent = "")
		{
			if (!root)
				return ;
			std::cout << indent;
			if (!root->left && !root->right)
			{
				std::cout << "R----";
				indent += "    ";
			}
			else
			{
				std::cout << "L----";
				indent += "|  ";
			}
			std::cout << root->content << "(" << (root->color == RED ? "RED" : "BLACK") << ")" << std::endl;
			print_node(root->left, indent);
			print_node(root->right, indent);
		}

	public:

		RBTree(void) :
			_alloc(RBNodeAllocator()),
			_root(NULL),
			_size(0)
		{}

		RBTree(const T& src)
		{
			*this = src;   // pas ca du tout en vrai, a faire
		}
		~RBTree(void) {}

		RBTree&	operator=(const RBTree& rhs)
		{
			_root = rhs._root; // shold be replaced by deep copy
			_size = rhs._size;
			_alloc = rhs._alloc;

			return *this;
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

		void	leftRotate(node* n)
		{
			node*	x = n;
			node*	y = n->right;
			node*	p = x->parent;
			node*	b = y->left;

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
		void	rightRotate(node* n)
		{
			node*	x = n->left;
			node*	y = n;
			node*	p = y->parent;
			node*	b = x->right;

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

		void insertFix(node *newNode)
		{
			node* uncle;
			while (newNode->parent->color == RED)
			{
				if (newNode->parent == newNode->parent->parent->right)
				{
					uncle = newNode->parent->parent->left;
					if (uncle->color == RED)
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
							rightRotate(newNode);
						}
						newNode->parent->color = BLACK;
						newNode->parent->parent->color = RED;
						leftRotate(newNode->parent->parent);
					}
				} else {
					uncle = newNode->parent->parent->right;

					if (uncle->color == RED)
					{
						uncle->color = BLACK;
						newNode->parent->color = BLACK;
						newNode->parent->parent->color = RED;
						newNode = newNode->parent->parent;
					}
					else
					{
						if (newNode == newNode->parent->right)
						{
							newNode = newNode->parent;
							leftRotate(newNode);
						}
						newNode->parent->color = BLACK;
						newNode->parent->parent->color = RED;
						rightRotate(newNode->parent->parent);
					}
				}
				if (newNode == _root)
					break;
			}
			_root->color = BLACK;
		}

		void insert(const T& key)
		{
			node* newNode = _newNode(key);
			node* current = _root;
			node* parent = NULL;

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

			if (!parent || !parent->parent)
				return ;

			insertFix(newNode);
		}

		void	print(void)
		{
			print_node(_root);
		}
	}; // class RBTree

} // namespace ft



#endif
