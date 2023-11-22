#include "graphs.h"

void free_edges(edge_t *edges)
{
	edge_t *tmp_edge = NULL;

	while (edges != NULL)
	{
		tmp_edge = edges;
		edges = edges->next;
		free(tmp_edge);
	}
}

/**
 * graph_delete - delete a graph
 * @graph: Pointer to the first vertice of the graph
 */
void graph_delete(graph_t *graph)
{
	vertex_t *current_vertex = graph->vertices;
	vertex_t *tmp_vertex = NULL;

	while (current_vertex != NULL)
	{
		tmp_vertex = current_vertex;
		current_vertex = current_vertex->next;
		free_edges(tmp_vertex->edges);
		free(tmp_vertex->content);
		free(tmp_vertex);
	}
	free(graph);
}
