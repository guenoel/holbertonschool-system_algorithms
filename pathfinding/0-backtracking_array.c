#include "pathfinding.h"

/**
 * point_push - creates a point and adds to a queue
 * @queue: queue
 * @x: X coordinate
 * @y: Y coordinate
 * Return: 1 if success, 0 if failed
 */
int point_push(queue_t **queue, int x, int y)
{
	point_t *p;

	p = malloc(sizeof(*p));
	if (!p)
		return (0);
	p->x = x;
	p->y = y;
	queue_push_front(*queue, p);
	return (1);
}

/**
 * backtracker - Finds a new possible solution
 * @queue: queue with points
 * @saw: saw array
 * @map: map or maze
 * @rows: height of @map
 * @cols: width of @map
 * @x: current X coordinate
 * @y: current Y coordinate
 * @target: target point
 * Return: queue with points or NULL if failed
*/
int backtracker(queue_t **queue, int *saw, char **map, int rows,
			int cols, int x, int y, point_t const *target)
{
	int arr[][2] = {RIGHT, BOTTOM, LEFT, TOP}, i;

	if (x < 0 || x >= cols || y < 0 || y >= rows ||
	    map[y][x] == '1' || *(saw + y * cols + x) == 1)
		return (0);

	printf("Checking coordinates [%d, %d]\n", x, y);
	if (x == target->x && y == target->y)
		return (point_push(queue, x, y));
	*(saw + y * cols + x) = 1;

	for (i = 0; i < 4; ++i)
		if (backtracker(queue, saw, map, rows, cols,
					x + arr[i][0], y + arr[i][1], target))
			return (point_push(queue, x, y));
	return (0);
}

/**
 * backtracking_array -  searches for the first path from a starting point to
 * a target point within a two-dimensional array
 * @map: pointer to a read-only two-dimensional array
 * @rows: number of rows of @map
 * @cols: number of cols of @map
 * @start: stores the coordinates of the starting point
 * @target: stores the coordinates of the target point
 * Return: queue, in which each node is a point in the path from start
 * to target
 */
queue_t *backtracking_array(char **map, int rows, int cols,
	point_t const *start, point_t const *target)
{
	int *saw;
	queue_t *queue;
	int ret;

	if (!map || !*map || !start || !target || rows < 1 || cols < 1)
		return (NULL);
	saw = calloc(rows * cols, sizeof(*saw));
	if (!saw)
		return (NULL);
	queue = queue_create();
	if (!queue)
	{
		free(saw);
		return (NULL);
	}
	ret = backtracker(&queue, saw, map, rows, cols,
				  start->x, start->y, target);
	if (!ret)
	{
		queue_delete(queue);
		queue = NULL;
	}
	free(saw);
	return (queue);
}
