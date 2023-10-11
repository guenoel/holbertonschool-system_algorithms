
#include "rb_trees.h"

/**
 * recursive_check - check if red black tree is valid
 * @tree: root of red-black tree
 * Return: 1 if rules are OK, 0 if rules are not OK
*/
int recursive_check(const rb_tree_t *tree)
{
	if (tree == NULL)
		return (1);
	if (tree->color == RED && tree->parent->color == RED)
		return (0);
	if (tree->color == RED && (!tree->left != !tree->right))
		return (0);
	return (recursive_check(tree->left) && recursive_check(tree->right));
}

/**
 * rb_tree_is_valid - check if red black tree is valid
 * @tree: root of red-black tree
 * Return: 1 if true 0 if false
*/
int rb_tree_is_valid(const rb_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	if (tree->color != BLACK)
		return (0);
	return (recursive_check(tree));
}
