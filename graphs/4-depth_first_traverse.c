#include "graphs.h"
#include <stdbool.h>

size_t recursion_traverse(const vertex_t *current_vertex,
							bool *visited_vertex,
							size_t depth,
							void (*action)(const vertex_t *v, size_t depth))
{
	edge_t *current_edge = NULL;
	size_t max_depth = depth;

	if (!current_vertex || visited_vertex[current_vertex->index])
		return (false);

	visited_vertex[current_vertex->index] = true;

	action(current_vertex, depth);

	current_edge = current_vertex->edges;
	while (current_edge != NULL)
	{
		if (!visited_vertex[current_edge->dest->index])
		{
/* 			printf("%ld\n", current_edge->dest->index); */
			size_t current_depth = recursion_traverse(current_edge->dest,
												visited_vertex, ++depth, action);
			max_depth = (current_depth > max_depth) ? current_depth : max_depth;
		}
		current_edge = current_edge->next;
	}

	return (max_depth);

}

size_t depth_first_traverse(const graph_t *graph,
							void (*action)(const vertex_t *v, size_t depth))
{
	size_t i;
	size_t depth = 0;
	vertex_t *current_vertex = NULL;
	bool visited_vertex[graph->nb_vertices];

	if (!graph || !action)
		return (0);
	current_vertex = graph->vertices;
	for (i = 0; i < graph->nb_vertices; i++)
		visited_vertex[i] = false;

	depth = recursion_traverse(current_vertex->edges->dest, visited_vertex,
								0, action);

	return (depth);
}
