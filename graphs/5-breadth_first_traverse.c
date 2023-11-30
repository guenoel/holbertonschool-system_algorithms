#include "graphs.h"
#include <stdbool.h>

/**
 * push_in_stack - add a new node at the beginning of a stack_t list
 * @stack: pointer to the head of the stack
 * @vertex: vertex to add
 * @depth: depth of the vertex
 * Return: pointer to the new node (begining of the stack)
 */
stack_t *push_in_stack(stack_t **stack, vertex_t *vertex, size_t depth)
{
	stack_t *new_node = NULL;

	new_node = (stack_t *)malloc(sizeof(stack_t));
	if (!new_node)
		return (NULL);
	new_node->vertex = vertex;
	new_node->depth = depth;
	new_node->next = *stack;
	*stack = new_node;
	return (new_node);
}

/**
 * pop_from_fifo_stack - removes the top element of a stack_t stack
 * @stack: pointer to the head of the stack
 * Return: pointer to the tail element of the stack
 */
stack_t *pop_from_fifo_stack(stack_t **stack)
{
	stack_t *prev = NULL;
	stack_t *temp = NULL;

	if (!stack || !*stack)
		return (NULL);
	temp = *stack; /* necessary when vertex is alone */
	if (temp->next) /* if vertex not alone... */
	{
		while (temp->next) /* ...go to tail of stack */
		{
			prev = temp;
			temp = temp->next;
		}
		temp = prev->next; /* save pointer to free (re-using same variable) */
		prev->next = NULL; /* unlink vertex poped*/
	}
	else /* if alone */
		prev = NULL;
	free(temp); /* free vertex poped */
	return (prev);
}

/**
 * breadth_first_traverse - goes through a graph using the breadth-first
 * traversal algorithm
 * @graph: pointer to the graph to traverse
 * @action: pointer to a function to be called for each visited vertex
 * Return: the max depth reached, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
								void (*action)(const vertex_t *v, size_t depth))
{
	stack_t *head = NULL;
	stack_t *tail = NULL;
	size_t depth = 0;
	size_t prev_depth = 0;
	bool *pushed_vertex = NULL;

	if (!graph || !action)
		return (0);
	if (!graph->vertices)
		return (0);
	pushed_vertex = (bool *)calloc(graph->nb_vertices, sizeof(bool));
	if (!pushed_vertex)
		return (0);
	/* init stack with first vertex */
	head = push_in_stack(&head, graph->vertices, depth);
	pushed_vertex[graph->vertices->index] = true;
	tail = head;
	depth++;
	while (tail)
	{
		edge_t *current_edge = tail->vertex->edges;

		/* condition to increase depth for next pushed vertices */
		if (tail->depth > prev_depth)
			depth++;
		while (current_edge) /* loop to push neighbours */
		{
			if (!pushed_vertex[current_edge->dest->index])
			{
				push_in_stack(&head, current_edge->dest, depth);
				pushed_vertex[current_edge->dest->index] = true;
			}
			current_edge = current_edge->next;
		}
		action(tail->vertex, tail->depth);
		prev_depth = tail->depth;
		tail = pop_from_fifo_stack(&head);
	}
	free(pushed_vertex);
	return (depth - 1);
}
