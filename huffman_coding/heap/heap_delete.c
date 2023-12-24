#include "heap.h"

/**
 * free_heap - Frees a heap data structure
 *
 * @node: Pointer to the root node of the heap
 * @free_data: Pointer to a function that frees the data stored in a node
 */
void free_heap(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (node == NULL)
		return;

	free_heap(node->left, free_data);
	free_heap(node->right, free_data);
	if (free_data)
		free_data(node->data);
	free(node);
}

/**
 * heap_delete - Deletes a heap data structure
 *
 * @heap: Pointer to the heap to delete
 * @free_data: Pointer to a function that frees the data stored in a node
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (heap == NULL)
		return;

	free_heap(heap->root, free_data);
	free(heap);
}
