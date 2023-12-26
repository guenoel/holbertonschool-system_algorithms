#include "huffman.h"

/**
 * symbol_create - Creates a symbol_t data structure
 *
 * @data: The character
 * @freq: The associated frequency
 *
 * Return: Pointer to the created symbol_t, or NULL on failure
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol = malloc(sizeof(symbol_t));

	if (symbol == NULL)
		return (NULL);

	symbol->data = data; /* the char */
	symbol->freq = freq;

	return (symbol);
}
