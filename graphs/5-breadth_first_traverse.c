#include "graphs.h"
#include <stdbool.h>

size_t go_trought_function(vertex_t *list_vertices,
							vertex_t *current_vertex,
							int *visited_vertex,
							size_t *queue,
							size_t *depth_change,
							size_t depth,
							void (*action)(const vertex_t *v, size_t depth))
{
	size_t q_w_index = 0;
	size_t q_r_index = 0;
	edge_t *current_edge = NULL;
	vertex_t *temp = NULL;
	size_t i = 0;

	depth_change[1] = 1;
	queue[q_w_index] = current_vertex->index;
	while (q_w_index + 1 >= q_r_index)
	{
		if (depth_change[q_r_index] == 1)
			depth++;
		/* print tab, index and town name */
		if (!visited_vertex[current_vertex->index])
			action(current_vertex, depth);
		/* check current vertex as visited */
		visited_vertex[current_vertex->index] = 1;
		/* enqueue neighbours of current vertex */
		current_edge = current_vertex->edges;
		while (current_edge)
		{
			if (visited_vertex[current_edge->dest->index] == 0)
			{
				bool is_in_queue = false;

				for (i = 0; i <= q_w_index; i++)
				{
					if (queue[i] == current_edge->dest->index)
						is_in_queue = true;
				}
				if (!is_in_queue)
				{
					q_w_index++;
					queue[q_w_index] = current_edge->dest->index;
				}
				if (current_edge->next == NULL)
					depth_change[q_w_index + 2] = 1;
			}
			current_edge = current_edge->next;
		}

		/* to find current vertex in main list of vertices */
		temp = list_vertices;
		while (temp)
		{
			if (queue[q_r_index] == temp->index)
			{
				current_vertex = temp;
				break;
			}
			temp = temp->next;
		}
		/* increase read index is like dequeue */
		q_r_index++;
	}

	return (depth);
}

size_t breadth_first_traverse(const graph_t *graph,
								void (*action)(const vertex_t *v, size_t depth))
{
	vertex_t *current_vertex = NULL;
	int *visited_vertex = NULL;
	size_t *queue = NULL;
	size_t *depth_change = NULL;
	size_t depth = 0;

	if (!graph || !action)
		return (0);
	visited_vertex = (int *)calloc(graph->nb_vertices, sizeof(int));
	if (!visited_vertex)
		return (0);
	queue = (size_t *)calloc(graph->nb_vertices, sizeof(size_t));
	if (!queue)
		return (0);
	depth_change = (size_t *)calloc(graph->nb_vertices, sizeof(size_t));
	if (!queue)
		return (0);
	current_vertex = graph->vertices;
	depth = go_trought_function(current_vertex, current_vertex, visited_vertex,
								queue, depth_change, depth, action);
	free(visited_vertex);
	free(queue);
	return (depth);
}
