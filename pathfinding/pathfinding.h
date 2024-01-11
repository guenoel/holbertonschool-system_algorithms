#ifndef __PATHFINDER__
#define __PATHFINDER__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "queues.h"
#include "graphs.h"

/**
* struct point_s - Structure storing coordinates
*
* @x: X coordinate
* @y: Y coordina
*
*/
typedef struct point_s
{
	int x;
	int y;
} point_t;

/**
 * struct data_s - Structure storing data for Dijkstra's algorithm
 * @vertices: Array of vertices
 * @from: Array of vertices from which the current vertex is reached
 * @costs: Array of costs to reach the current vertex
 */
typedef struct data_s
{
	vertex_t **vertices;
	vertex_t **from;
	int *costs;
} data_t;

queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start, point_t const *target);

int is_vertex_visited(const vertex_t *next, graph_t *visited);
int backtrack_find_path(graph_t *graph, vertex_t const *start,
						vertex_t const *target, queue_t *path_queue,
						graph_t *visited);
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
							vertex_t const *target);

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
						vertex_t const *target);


#endif /* __PATHFINDER__ */
