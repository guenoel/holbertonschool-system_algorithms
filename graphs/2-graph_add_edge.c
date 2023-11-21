#include "graphs.h"

/**
 * graph_delete - delete a graph
 * @graph: Pointer to the first vertice of the graph
 */
void graph_delete(graph_t *graph)
{
	vertex_t *current_vertex = graph->vertices;
	vertex_t *tmp = NULL;

	while (current_vertex->next)
	{
		tmp = current_vertex->next;
		free(current_vertex->content);
		free(current_vertex);
		current_vertex = tmp;
	}
}
