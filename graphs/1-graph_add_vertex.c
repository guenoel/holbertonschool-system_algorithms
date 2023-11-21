#include "graphs.h"
#include <string.h>

/**
 * graph_add_vertex - add vertex in a graph
 * @graph: pointer to the graph to add to
 * @str: string to copy in vertex
 * Return: Pointer to the vertex added
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex = (vertex_t *)malloc(sizeof(vertex_t));

	if (!new_vertex)
		return (NULL);

	strcpy(new_vertex->content, str);
	new_vertex->edges = NULL;
	new_vertex->index = 0;
	new_vertex->nb_edges = 0;
	new_vertex->next = NULL;
	return (new_vertex);
}
