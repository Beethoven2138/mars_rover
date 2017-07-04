#include <stdlib.h>
#include <stdio.h>

#include <mars.h>


int main(int argc, char *argv[])
{
	int width;
	int height;
	int fill_prob;

	CORD *start = (CORD*)malloc(sizeof(CORD));
	//CORD *end = (CORD*)malloc(sizeof(CORD));

	if (argc >= 3)
	{
		width = atoi(argv[1]);
		height = atoi(argv[2]);
	}

	else
	{
		width = 10;
		height = 10;
	}

	if (argc >= 4)
		fill_prob = atoi(argv[3]);
	else
		fill_prob = 10;

	CELL *map = (CELL*)malloc(sizeof(CELL) * width * height);
	//LIST_NODE *list_glb = (LIST_NODE*)malloc(sizeof(LIST_NODE));
	CORD *list_glb = (CORD*)malloc(sizeof(CORD) * width * height);

	init_map(width, height, map, fill_prob);
	print_map(width, height, map);

	printf("Enter the start coordinate and end coordinate in the form of: start_xPos 10 start_yPos 10 end_xPos 10 end_yPos 10\n");

        scanf("%d", &start->x);
	scanf("%d", &start->y);
	scanf("%d", &list_glb[0].x);
	scanf("%d", &list_glb[0].y);

	int list_length;

	find_path(width, height, map, list_glb, *start, &list_length);

	print_map(width, height, map);

	free(list_glb);
	free(start);
	free(map);

	return 0;
}
