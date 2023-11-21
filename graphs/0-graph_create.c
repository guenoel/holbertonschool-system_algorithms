#include "graphs.h"

/**
 * graph_create - create a graph
 * Return: Pointer to the created graph
 */
graph_t *graph_create(void)
{
	graph_t *new_graph = (graph_t *)malloc(sizeof(graph_t));

	if (!new_graph)
		return (NULL);
	new_graph->nb_vertices = 0;
	new_graph->vertices = NULL;
	return (new_graph);
}
