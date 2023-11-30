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

	/* printf("added stack: %s\n", vertex->content); */
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
	temp = *stack;
	if (temp->next)
	{
		while (temp->next)
		{
			prev = temp;
			temp = temp->next;
		}
	}
	else
		prev = NULL;
	/* printf("poped stack: %s\n", temp->vertex->content); */
	/* printf("new_tail: %s\n", prev->vertex->content); */
	if (prev)
		prev->next = NULL;
	/* free(*stack); */
	return (prev);
}

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
	pushed_vertex = (bool *)calloc(graph->nb_vertices, sizeof(bool));
	if (!pushed_vertex)
		return (0);
	head = push_in_stack(&head, graph->vertices, depth);
	pushed_vertex[graph->vertices->index] = true;
	tail = head;
	depth++;
	while (tail)
	{
		edge_t *current_edge = tail->vertex->edges;

		/* printf("prev depth: %ld\n", prev_depth); */
		/* printf("tail->depth: %ld\n", tail->depth); */

		if (tail->depth > prev_depth)
			depth++;
		while (current_edge)
		{
			if (!pushed_vertex[current_edge->dest->index])
			{
				push_in_stack(&head, current_edge->dest, depth);
				pushed_vertex[current_edge->dest->index] = true;
			}
			current_edge = current_edge->next;
		}
		/* printf("depth: %lu\n", tail->depth); */
		/* fflush(stdout); */
		action(tail->vertex, tail->depth);
		prev_depth = tail->depth;
		tail = pop_from_fifo_stack(&head);
	}
	return (depth - 1);
}
