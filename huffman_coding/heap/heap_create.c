#include "heap.h"

/**
 * heap_create - Creates a heap data structure
 *
 * @data_cmp: Pointer to a function that compares two nodes
 *
 * Return: Pointer to the created heap_t, or NULL on failure
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap = malloc(sizeof(heap_t));

	if (heap == NULL)
		return (NULL);

	heap->size = 0;
	heap->data_cmp = data_cmp;
	heap->root = NULL;

	return (heap);
}
