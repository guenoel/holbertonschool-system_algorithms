#include "heap.h"

/**
 * binary_tree_node - Creates a binary tree node
 *
 * @parent: Pointer to the parent node
 * @data: Pointer to the data to store in the new node
 *
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *node = malloc(sizeof(binary_tree_node_t));

	if (node == NULL)
		return (NULL);

	node->data = data;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;

	return (node);
}
