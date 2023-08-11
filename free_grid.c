#include <stdlib.h>

/**
 * free_grid - deallocates a 2D array
 * @grid: a 2D aray pointer
 * Return: Nothing
 */

void free_grid(char **grid)
{
	char **grid_cpy = grid;

	while (*grid != NULL)
	{
		free(*grid);
		grid++;
	}
	free(grid_cpy);
}
