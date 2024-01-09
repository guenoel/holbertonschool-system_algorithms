#include "pathfinding.h"

int point_push(queue_t **path, int x, int y)
{
	point_t *new = malloc(sizeof(point_t));
	if (!new)
		return (0);
	new->x = x;
	new->y = y;
	queue_push_front(*path, new);
	return (1);
}

int recursive_backtracker(queue_t **path, int **visited, char **map, int rows,
							int cols, point_t const *start,
							int x, int y, point_t const *target, point_t *moves)
{
	int i;

	if (x >= cols || y >= rows /* check if inside map (right and bottom) */
			|| x < 0 || y < 0 /* check if inside map (left and top) */
			|| map[y][x] == '1' /* check if wall */
			|| visited[y][x] == 1) /* check if visited */
		return (0);

	printf("Checking coordinates [%d, %d]\n", x, y);
	if (x == target->x && y == target->y) /* check if target reached */
		return (point_push(path, x, y));
	visited[y][x] = 1; /* mark as visited */

	/* check all directions - if one is possible: add to queue */
	for (i = 0; i < 4; ++i)
	{
		if (recursive_backtracker(path, visited, map, rows, cols, start,
								x + moves[i].x, y + moves[i].y, target, moves))
			return (point_push(path, x, y));
	}
	/* else back to previous */
	return (0);
}

queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start, point_t const *target)
{
	int i = 0, j = 0, ret_val;
	int **visited = NULL;
	point_t RIGHT = {1, 0};
	point_t BOTTOM = {0, 1};
	point_t LEFT = {-1, 0};
	point_t TOP = {0, -1};

	point_t *moves = malloc(sizeof(point_t *) * 4);
	if (!moves)
		return (NULL);
	moves[0] = RIGHT;
	moves[1] = BOTTOM;
	moves[2] = LEFT;
	moves[3] = TOP;

	if (!map || !*map || !rows || !cols || !start || !target)
		return (NULL);

	visited = malloc(sizeof(int *) * rows);
	/* erase all if failed */
	if (!visited)
		return (NULL);
	for (i = 0; i < rows; i++)
	{
		visited[i] = malloc(sizeof(int) * cols);
		/* erase all if failed */
		if (!visited[i])
		{
			for (j = 0; j < i; j++)
				free(visited[j]);
			free(visited);
			return (NULL);
		}
		for (j = 0; j < cols; j++)
			visited[i][j] = 0;
	}

	queue_t *path = queue_create();
	/* erase all if failed */
	if (!path)
	{
		for (i = 0; i < rows; i++)
			free(visited[i]);
		free(visited);
		return (NULL);
	}

	ret_val = recursive_backtracker(&path, visited, map, rows, cols, start,
									start->x, start->y, target, moves);
	if (!ret_val)
	{
		queue_delete(path);
		path = NULL;
	}
	free(visited);
	return (path);
}
