#include "graphs.h"
#include <string.h>

/**
 * create_vertex - add vertex in a graph
 * @str: string to copy in vertex
 * @nb_vertices: number of vertices
 * Return: Pointer to the new vertex
 */
vertex_t *create_vertex(const char *str, size_t nb_vertices)
{
	vertex_t *new_vertex = (vertex_t *)malloc(sizeof(vertex_t));

	if (!new_vertex)
		return (NULL);
	new_vertex->content = strdup(str);

	new_vertex->edges = NULL;
	new_vertex->index = nb_vertices;
	new_vertex->nb_edges = 0;
	new_vertex->next = NULL;
	return (new_vertex);
}

/**
 * graph_add_vertex - add vertex in a graph
 * @graph: pointer to the graph to add to
 * @str: string to copy in vertex
 * Return: Pointer to the vertex added
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *current_vertex, *new_vertex;

	/* Check for NULL parameters */
	if (graph == NULL || str == NULL)
		return (NULL);

	/* Case of empty graph */
	if (!graph->vertices)
	{
		new_vertex = create_vertex(str, graph->nb_vertices);
		graph->vertices = new_vertex;
		graph->nb_vertices++;
		return (new_vertex);
	}

	/* Case of non-empty graph */
	current_vertex = graph->vertices;
	while (current_vertex->next != NULL)
	{
		/* check if vertice content already exist */
		if (!strcmp(current_vertex->content, str))
			return (NULL);
		current_vertex = current_vertex->next;
	}
	new_vertex = create_vertex(str, graph->nb_vertices);
	current_vertex->next = new_vertex;
	graph->nb_vertices++;
	return (new_vertex);
}
