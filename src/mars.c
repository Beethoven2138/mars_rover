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
	printf("  ");
	for (int i = 0; i < width; i++)
	{
		if (i > 9)
			printf("%d ", i);
		else
			printf("0%d ", i); 
	}
	printf("\n");

	for (int y = 0; y < height; y++)
	{
		if (y > 9)
			printf("%d ", y);
		else
			printf("0%d ", y);
		for (int x = 0; x < width; x++)
		{
			if (map[y * width + x].type == 0)
				printf(ANSI_COLOR_GREEN "*" ANSI_COLOR_RESET);
			else if (map[y * width + x].type == PATH)
				//printf("%d", map[y * width + x].count);
				printf(ANSI_COLOR_CYAN "=" ANSI_COLOR_RESET);
			else
				printf(ANSI_COLOR_RED "0" ANSI_COLOR_RESET);
			printf("  ");
		}
		if (y > 9)
			printf("%d", y);
		else
			printf("0%d", y);
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

void find_path(int width, int height, CELL *map, CORD *list_glb, CORD start, int *list_length)
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
	/*for (int i = 0; i < *list_length; i++)
	  {
	  map[list_glb[i].y * width + list_glb[i].x].type = PATH;
	  }*/
	map[start.y * width + start.x].type = PATH;
	while (start.x != list_glb->x || start.y != list_glb->y)
	{
		start = min_cell(width, height, map, start);
		map[start.y * width + start.x].type = PATH;
	}
	map[list_glb->y * width + list_glb->x].type = PATH;
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

static CORD min_cell(int width, int height, CELL *map, CORD cord)
{
	CORD result;
	result.x = cord.x+1;
	result.y = cord.y;

	if ((map[cord.y * width + cord.x-1].count < map[result.y * width + result.x].count && map[cord.y * width + cord.x-1].type != ROCK) || map[result.y * width + result.x].count == 0)
		result.x = cord.x-1;

	if ((map[(cord.y+1) * width + cord.x].count < map[result.y * width + result.x].count && map[(cord.y+1) * width + cord.x].type != ROCK) || map[result.y * width + result.x].count == 0)
	{
		result.y = cord.y+1;
		result.x = cord.x;
	}

	if ((map[(cord.y-1) * width + cord.x].count < map[result.y * width + result.x].count && map[(cord.y-1) * width + cord.x].type != ROCK) || map[result.y * width + result.x].count == 0)
	{
		result.y = cord.y-1;
		result.x = cord.x;
	}

	return result;
}
