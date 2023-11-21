#include "graphs.h"

/**
 * graph_create - create a graph
 * Return: Pointer to the created graph
 */
graph_t *graph_create(void)
{
	graph_t *new_graph = malloc(sizeof(graph_t));

	if (!new_graph)
		return (NULL);
	return (new_graph);
}