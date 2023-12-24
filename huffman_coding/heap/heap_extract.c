#include "heap.h"

/**
 * swap_node - Swap two nodes in a binary tree
 *
 * @node1: Pointer to the first node
 * @node2: Pointer to the second node
 *
 * Return: Pointer to the first node
 */
binary_tree_node_t *swap_node2(binary_tree_node_t *node1,
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

	/* return new lower node (node1) */
	return (node1);
}

/**
 * search_last_leaf2 - Search the last leaf in a binary tree
 *
 * @heap: Pointer to the heap to search the last leaf in
 *
 * Return: Pointer to the last leaf
 */
binary_tree_node_t *search_last_leaf2(heap_t *heap)
{
	binary_tree_node_t *current;
	binary_tree_node_t **array;
	binary_tree_node_t *last_leaf;
	int cursor = 0, index = 0;

	if (heap->size == 0 || heap->root == NULL)
		return (NULL);

	array = malloc(sizeof(binary_tree_node_t *) * heap->size);
	/* Add root to the start of the queue */
	array[index++] = heap->root;

	/* Level order traversal to find the last node */
	while (cursor < index)
	{
		/* take parent from the array which has just been filled */
		current = array[cursor++];

		/* Add left and right children of the parent to the array */
		if (current->left != NULL)
			array[index++] = current->left;
		if (current->right != NULL)
			array[index++] = current->right;
	}
	/* Return the last node */
	/* -1 cause last loop increase index once too many */
	last_leaf = array[index - 1];
	free(array);
	return (last_leaf);
}

/**
 * remove_and_replace_root - Removes the root node and replaces it with
 * the last leaf
 *
 * @heap: Pointer to the heap to remove the root node from
 * @last_leaf: Pointer to the last leaf in the heap
 *
 * Return: The data from the root node extracted
 */
void *remove_and_replace_root(heap_t *heap, binary_tree_node_t *last_leaf)
{
	binary_tree_node_t *temp = NULL;
	void *num_extracted;

	temp = heap->root; /* save previous root */
	heap->root = last_leaf; /* update new root (previous last leaf) */
	if (heap->root != temp->left) /* condition if there only 2 nodes in the heap */
		heap->root->left = temp->left;
	else
		heap->root->left = NULL;
	heap->root->right = temp->right;
	num_extracted = temp->data; /* save num extracted before free */
	free(temp);
	/* update parent of previous last leaf */
	if (last_leaf->parent->left == last_leaf)
		last_leaf->parent->left = NULL;
	else
		last_leaf->parent->right = NULL;
	last_leaf->parent = NULL;

	return (num_extracted);
}

/**
 * heap_extract - Extracts the root node from a Min Binary Heap
 *
 * @heap: Pointer to the heap to extract the root node from
 *
 * Return: Pointer to the data stored in the root node, or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	binary_tree_node_t *last_leaf = NULL, *current_node = NULL, *smallest = NULL;
	void *num_extracted;

	if (!heap || !heap->root)
		return (NULL);
	last_leaf = search_last_leaf2(heap); /* Insert node at the end of heap */
	num_extracted = remove_and_replace_root(heap, last_leaf);

	heap->size--;
	current_node = heap->root;
	/* Swap nodes until the heap is ordered */
	while ((current_node->left || current_node->right))
	{
		if (!current_node->right)
			smallest = current_node->left;
		else
			if (heap->data_cmp(current_node->left->data, current_node->right->data) < 0)
				smallest = current_node->left;
			else
				smallest = current_node->right;
		if (heap->data_cmp(smallest->data, current_node->data) < 0)
		{
			if (current_node->parent == NULL)
				heap->root = smallest;
			current_node = swap_node2(current_node, smallest);
		}
	}
	return (num_extracted);
}
