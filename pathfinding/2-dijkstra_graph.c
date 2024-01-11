#include "pathfinding.h"
#include <limits.h>

/**
 * init_arrays - initializes arrays
 * @graph: the graph to navigate
 * @start: the starting vertex
 * @data: the data struct
 * Return: queue with the path to target
 */
int init_arrays(graph_t *graph, vertex_t const *start, data_t *data)
{
	vertex_t *cur_vertex;

	data->vertices = calloc(graph->nb_vertices, sizeof(*(data->vertices)));
	if (!data->vertices)
		return (0);
	data->costs = calloc(graph->nb_vertices, sizeof(*(data->costs)));
	if (!data->costs)
	{
		free(data->vertices);
		return (0);
	}
	data->from = calloc(graph->nb_vertices, sizeof(*(data->from)));
	if (!data->from)
	{
		free(data->vertices);
		free(data->costs);
		return (0);
	}

	for (cur_vertex = graph->vertices; cur_vertex; cur_vertex = cur_vertex->next)
	{
		data->vertices[cur_vertex->index] = cur_vertex;
		data->costs[cur_vertex->index] = INT_MAX;
	}
	data->costs[start->index] = 0;
	data->from[start->index] = NULL;
	return (1);
}

/**
 * fill_queue - fills the queue with the path
 * @data: the data struct
 * @start: the starting vertex
 * @i: the index of the vertex
 * Return: queue with the path to target
 */
queue_t *fill_queue(data_t *data, vertex_t const *start, ssize_t i)
{
	queue_t *path_queue = queue_create();

	if (!queue_push_front(path_queue, strdup(data->vertices[i]->content)))
		queue_delete(path_queue);
	while (i != (ssize_t)(start->index))
	{
		if (!queue_push_front(path_queue, strdup(data->from[i]->content)))
			queue_delete(path_queue);
		i = data->from[i]->index;
	}
	if (!path_queue->front) /* If the path_queue is empty, return NULL */
	{
		free(path_queue);
		return (NULL);
	}
	return (path_queue);
}

/**
 * check_edges - checks edges of a vertex
 * @data: the data struct
 * @i: the index of the vertex
 */
void check_edges(data_t *data, ssize_t i)
{
	edge_t *cur_edge = NULL;

	for (cur_edge = data->vertices[i]->edges; cur_edge;
													cur_edge = cur_edge->next)
		/* if destination is not visited and */
		if (data->costs[cur_edge->dest->index] >= 0 &&
		/* if actual cost + edge cost < cost of edge destination */
			data->costs[i] + cur_edge->weight < data->costs[cur_edge->dest->index])
		{
			/* then update destination cost */
			data->costs[cur_edge->dest->index] = data->costs[i] + cur_edge->weight;
			/* update best path at "step-1" */
			data->from[cur_edge->dest->index] = data->vertices[i];
		}
}

/**
 * dijkstra_graph - finds a path in the graph using Dijkstra's algorithm
 * @graph: the graph to navigate
 * @start: the starting vertex
 * @target: the target vertex
 * Return: queue with the path to target
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
						vertex_t const *target)
{
	data_t data;
	queue_t *path_queue = NULL;
	ssize_t min_cost = INT_MAX, j, i = -1;

	if (!graph || !start || !target)/* Check for invalid input */
		return (NULL);
	init_arrays(graph, start, &data);
	while (i != (ssize_t)target->index)
	{
		/* check which vertex have the min cost (if unknown: int_max) */
		i = -1;
		min_cost = INT_MAX;
		for (j = 0; j < (ssize_t)(graph->nb_vertices); j++)
		{
			/* if not visited and is min cost and not unknown (== int_max) */
			if (data.costs[j] >= 0 && data.costs[j] < min_cost)
			{
				min_cost = data.costs[j]; /* update min cost for next loop */
				i = j; /* switch to best town */
			}
		}
		if (i == -1) /* if not reachable */
			break;
		printf("Checking %s, distance from %s is %d\n",
			data.vertices[i]->content, start->content, data.costs[i]);
		check_edges(&data, i);
		data.costs[i] = -1; /* tag as visited */
	}
	if (i != -1)
		path_queue = fill_queue(&data, start, i);
	free(data.vertices);
	free(data.costs);
	free(data.from);

	return (path_queue);
}
