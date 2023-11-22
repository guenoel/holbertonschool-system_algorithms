#include "graphs.h"
#include <stdbool.h>
#include <string.h>

/**
 * check_src_dest - check if source and destination both exists
 * @graph: pointer to the graph
 * @src: string of source
 * @dest: string of destination
 * Return: 1 if exist 0 if one or more does not exists
 */
int check_src_dest(graph_t *graph, const char *src, const char *dest)
{
	bool is_src = 0;
	bool is_dest = 0;
	vertex_t *current_vertex = graph->vertices;

	while (current_vertex)
	{
		if (strcmp(current_vertex->content, src) == 0)
			is_src = 1;
		if (strcmp(current_vertex->content, dest) == 0)
			is_dest = 1;
		current_vertex = current_vertex->next;
	}
	if (is_src && is_dest)
		return (1);
	return (0);
}

/**
 * vertex_find - find corresponding vertex in list
 * @content: string that have to correspond to content of vertex
 * @vertices: linked list of vertices
 * Return: Pointer to the corresponding vertex
 */
vertex_t *vertex_find(const char *content, vertex_t *vertices)
{
	vertex_t *current_vertex = vertices;

	while (current_vertex)
	{
		if (strcmp(current_vertex->content, content) == 0)
			return (current_vertex);
		current_vertex = current_vertex->next;
	}
	return (NULL);
}

/**
 * edge_create - create struct vertice vertices
 * @graph: pointer to the graph
 * @dest: string of destinationl
 * Return: pointer to the new edge
 */
edge_t *edge_create(graph_t *graph, const char *dest)
{
	edge_t *new_edge = (edge_t *)malloc(sizeof(edge_t));

	if (!new_edge)
		return (NULL);
	new_edge->dest = vertex_find(dest, graph->vertices);
	new_edge->next = NULL;
	return (new_edge);
}

/**
 * add_edge_in_vertex - add edges in a vertex
 * @vertex: vertex to add edge to
 * @edge: edge to be added in vertex
 */
void add_edge_in_vertex(vertex_t *vertex, edge_t *edge)
{
	edge_t *tmp_edge = NULL;

	tmp_edge = vertex->edges;
	if (tmp_edge)
	{
		while (tmp_edge->next)
			tmp_edge = tmp_edge->next;
		tmp_edge->next = edge;
	} else
	{
		vertex->edges = edge;
	}
}

/**
 * graph_add_edge - add edges between vertices
 * @graph: pointer to the graph
 * @src: string of source
 * @dest: string of destination
 * @type: type of edge directional or bidirectional
 * Return: 1 if success 0 if fail
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
					edge_type_t type)
{
	edge_t *src_new_edge = NULL;
	edge_t *dest_new_edge = NULL;
	vertex_t *src_vertex = NULL;
	vertex_t *dest_vertex = NULL;

	if (!graph || !src || !dest)
		return (0);
	if (!graph->vertices)
		return (0);
	if (check_src_dest(graph, src, dest) == 0)
		return (0);
	src_new_edge = edge_create(graph, dest);
	src_vertex = vertex_find(src, graph->vertices);
	add_edge_in_vertex(src_vertex, src_new_edge);

	if (type == BIDIRECTIONAL)
	{
		dest_vertex = src_new_edge->dest;
		dest_new_edge = edge_create(graph, src);
		add_edge_in_vertex(dest_vertex, dest_new_edge);
	}
	src_vertex->nb_edges++;
	return (1);
}
