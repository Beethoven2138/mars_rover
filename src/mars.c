#include <mars.h>

/*
y * width + x
 */

void init_map(int width, int height, CELL *map, int fill_prob)
{
	srand(time(NULL));
	for (int y = 1; y < height-1; y++)
	{
		for (int x = 1; x < width-1; x++)
		{
			if (rand() % 101 > fill_prob)
				map[y * width + x].type = DIRT;
		}
	}

	for (int y = 1; y < height-1; y++)
	{
		for (int x = 1; x < width-1; x++)
		{
		        if (neighbour_count(width, height, map, x, y) > 4)
				map[y * width + x].type = ROCK;
			else
				map[y * width + x].type = DIRT;
		}
	}
}

void print_map(int width, int height, CELL *map)
{
	printf(" ");
	for (int i = 0; i < width; i++)
		printf("%d", i);
	printf("\n");

	for (int y = 0; y < height; y++)
	{
		printf("%d",y);
		for (int x = 0; x < width; x++)
		{
			if (map[y * width + x].type == 0)
				printf("*");
			else if (map[y * width + x].type == PATH)
				printf("%d", map[y * width + x].count);
			else
				printf("_");
		}
		printf("\n");
	}
}

static int neighbour_count(int width, int height, CELL *map, int xPos, int yPos)
{
	int rock_count = 0;

	for (int y = yPos-1; y <= yPos+1; y++)
	{
		for (int x = xPos-1; x <= xPos+1; x++)
		{
			if (y >= 0 && y < height && x > 0 && x < width && (xPos != x || yPos != y))
				if (map[y * width + x].type == ROCK)
				    rock_count++;
		}
	}
	return rock_count;
}

void find_path(int width, int height, CELL *map, CORD *list_glb, int destx, int desty, int *list_length)
{
	*list_length = 1;
	for (int i = 0; i < *list_length; i++)
	{
	        /*if ((map[list_glb[i].y-1) * width + list_glb[i].x].type != ROCK &&
		  (map[list_glb[i].y-1) * width + list_glb[i].x].count)*/
		if (keep(width, height, map, list_glb, list_glb[i].x-1, list_glb[i].y, map[list_glb[i].y * width + list_glb[i].x].count+1, *list_length))
		{
			map[list_glb[i].y * width + list_glb[i].x-1].count = map[list_glb[i].y * width + list_glb[i].x].count+1;
			list_glb[*list_length].x = list_glb[i].x-1;
			list_glb[*list_length].y = list_glb[i].y;
			(*list_length)++;
		}
		if (keep(width, height, map, list_glb, list_glb[i].x+1, list_glb[i].y, map[list_glb[i].y * width + list_glb[i].x].count+1, *list_length))
		{
			map[list_glb[i].y * width + list_glb[i].x+1].count = map[list_glb[i].y * width + list_glb[i].x].count+1;
			list_glb[*list_length].x = list_glb[i].x+1;
			list_glb[*list_length].y = list_glb[i].y;
			(*list_length)++;
		}
		if (keep(width, height, map, list_glb, list_glb[i].x, list_glb[i].y-1, map[list_glb[i].y * width + list_glb[i].x].count+1, *list_length))
		{
			map[(list_glb[i].y-1) * width + list_glb[i].x].count = map[list_glb[i].y * width + list_glb[i].x].count+1;
			list_glb[*list_length].x = list_glb[i].x;
			list_glb[*list_length].y = list_glb[i].y-1;
			(*list_length)++;
		}
		if (keep(width, height, map, list_glb, list_glb[i].x, list_glb[i].y+1, map[list_glb[i].y * width + list_glb[i].x].count+1, *list_length))
		{
			map[(list_glb[i].y+1) * width + list_glb[i].x].count = map[list_glb[i].y * width + list_glb[i].x].count+1;
			list_glb[*list_length].x = list_glb[i].x;
			list_glb[*list_length].y = list_glb[i].y+1;
			(*list_length)++;
		}
	}
	for (int i = 0; i < *list_length; i++)
	{
		map[list_glb[i].y * width + list_glb[i].x].type = PATH;
	}
}

static bool keep(int width, int height, CELL *map, CORD *list_glb, int xPos, int yPos, int count, int list_length)
{
	if (map[yPos * width + xPos].type == ROCK)
		return false;

	for (int i = 0; i < list_length; i++)
	{
		if (list_glb[i].x == xPos && list_glb[i].y == yPos)
		{
			if (map[yPos * width + xPos].count <= count)
				return false;
			return true;
		}
	}
	return true;
}
