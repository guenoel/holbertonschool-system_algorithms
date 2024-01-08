#include "pathfinding.h"

point_t *move(point_t const *point, point_t const *move)
{
	point_t *new = malloc(sizeof(point_t));
	if (!new)
		return (NULL);
	new->x = point->x + move->x;
	new->y = point->y + move->y;
	return (new);
}

queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start, point_t const *target)
{
	int i = 0, j = 0;
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

	queue_push_front(path, (void *)start);
	printf("Checking coordinates [%d, %d]\n", start->x, start->y);
	while (((point_t *)path->front->ptr)->x != target->x
		|| ((point_t *)path->front->ptr)->y != target->y)
	{
		i = 0;
		while (i < 4)
		{
			point_t *new_position = move(path->front->ptr, &moves[i]);
			i++;
			if (map[new_position->y][new_position->x] == '0'
				&& visited[new_position->y][new_position->x] == 0)
			{
				printf("Checking coordinates [%d, %d]\n", new_position->x, new_position->y);
				visited[new_position->y][new_position->x] = 1;
				queue_push_front(path, (void *)new_position);
				i = 0;
			}
			if (((point_t *)path->front->ptr)->x == target->x
				&& ((point_t *)path->front->ptr)->y == target->y)
				return (path);
		}
		dequeue(path);
	}
	return (path);
}
