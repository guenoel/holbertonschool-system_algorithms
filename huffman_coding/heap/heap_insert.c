#include "heap.h"

/**
 * swap_node - Swap two nodes in a binary tree
 *
 * @node1: Pointer to the first node
 * @node2: Pointer to the second node
 *
 * Return: Pointer to the second node
 */
binary_tree_node_t *swap_node(binary_tree_node_t *node1,
									binary_tree_node_t *node2)
{
	binary_tree_node_t *tmp_l = NULL;
	binary_tree_node_t *tmp_r = NULL;

	/* modify parent of upper node (node1) */
	if (node1->parent != NULL)
	{
		if (node1->parent->left == node1)
			node1->parent->left = node2;
		else
			node1->parent->right = node2;
	}
	/* modify parent of nodes */
	node2->parent = node1->parent;
	node1->parent = node2;

	/* save node2 childs */
	tmp_r = node2->right;
	tmp_l = node2->left;

	/* modify childs of node2 */
	if (node1->left == node2)
	{
		node2->left = node1;
		node2->right = node1->right;
	}
	else
	{
		node2->right = node1;
		node2->left = node1->left;
	}
	/* modify childs of node1 */
	node1->left = tmp_l;
	node1->right = tmp_r;

	/* return new upper node (node2) */
	return (node2);
}

/**
 * search_last_leaf - Search the last leaf in a binary tree
 *
 * @node: Pointer to the root node
 *
 * Return: Pointer to the last leaf
 */
binary_tree_node_t *search_last_leaf(binary_tree_node_t *node)
{
	if (node == NULL)
		return (NULL);

	if (node->left == NULL || node->right == NULL)
		return (node);

	/* Recursively search in the right subtree if left is NULL */
	return (search_last_leaf(node->left ? node->left : node->right));
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 *
 * @heap: Pointer to the heap in which the node has to be inserted
 * @data: Pointer containing the data to store in the new node
 *
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node = NULL;
	binary_tree_node_t *current_node = NULL;

	if (heap == NULL)
		return (NULL);

	/* Create a new node */
	new_node = binary_tree_node(NULL, data);
	if (new_node == NULL)
		return (NULL);

	heap->size++;
	/* Insert node at the root if the heap is empty */
	if (heap->root == NULL)
	{
		heap->root = new_node;
		return (new_node);
	}

	/* Insert node at the end of the heap */
	new_node->parent = search_last_leaf(heap->root);
	if (new_node->parent->left == NULL)
		new_node->parent->left = new_node;
	else
		new_node->parent->right = new_node;

	current_node = new_node;
	/* Swap nodes until the heap is ordered */
	while (current_node->parent && heap->data_cmp(current_node->data,
												current_node->parent->data) < 0)
	{
		current_node = swap_node(current_node->parent, current_node);
		if (current_node->parent == NULL)
			heap->root = current_node;
	}

	return (new_node);
}
