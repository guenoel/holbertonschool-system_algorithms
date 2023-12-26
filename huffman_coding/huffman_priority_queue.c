#include "huffman.h"

/**
* symbol_cmp - Compares two symbols based on their frequencies.
* @p1: First symbol pointer.
* @p2: Second symbol pointer.
*
* Return: Difference between the frequencies of the two symbols.
*/
int symbol_cmp(void *p1, void *p2)
{
	symbol_t *sym1, *sym2;

	sym1 = ((binary_tree_node_t *)p1)->data;
	sym2 = ((binary_tree_node_t *)p2)->data;
	return (sym1->freq - sym2->freq);
}

/**
 * huffman_priority_queue - Creates a priority queue for the Huffman coding
 * algorithm
 *
 * @data: Array of characters
 * @freq: Array of frequencies
 * @size: Size of both arrays
 *
 * Return: Pointer to the created heap_t, or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue = heap_create(symbol_cmp);
	binary_tree_node_t *nested = NULL;

	for (size_t i = 0; i < size; i++)
	{
		symbol_t *symbol = symbol_create(data[i], freq[i]);

		nested = binary_tree_node(NULL, symbol);
		heap_insert(priority_queue, nested);
	}
	return (priority_queue);
}
