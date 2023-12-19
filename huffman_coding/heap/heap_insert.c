#include "heap.h"

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
	binary_tree_node_t *node = NULL;

	if (heap == NULL)
		return (NULL);

	node = binary_tree_node(NULL, data);
	if (node == NULL)
		return (NULL);

	if (heap->root == NULL)
	{
		heap->root = node;
		heap->size++;
		return (node);
	}

	return (node);
}
