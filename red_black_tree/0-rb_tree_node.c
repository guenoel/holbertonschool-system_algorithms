#include "rb_trees.h"

/**
 * rb_tree_node - create new node for the tree
 * @parent: parent node
 * @value: integer in node
 * @color: color of the node (red or black)
 * Return: new node
*/
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new_node;

	new_node = (rb_tree_t *)malloc(sizeof(rb_tree_t));
	if (new_node == NULL)
		return (NULL);
	new_node->n = value;
	new_node->color = color;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
