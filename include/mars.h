#ifndef MARS_H
#define MARS_H

#define ROCK 0
#define DIRT 1
#define PATH 2

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct CELL
{
        int type;
	int count;
} CELL;

typedef struct CORD
{
	int x, y;
	//int count;
} CORD;

typedef struct LIST_NODE
{
	CORD *cord;
	struct LIST_NODE *next;
	struct LIST_NODE *prev;
} LIST_NODE;


void init_map(int width, int height, CELL *map, int fill_prob);
void print_map(int width, int height, CELL *map);
static int neighbour_count(int width, int height, CELL *map, int xPos, int yPos);
void find_path(int width, int height, CELL *map, CORD *list_glb, CORD start, int *list_length);
static bool keep(int width, int height, CELL *map, CORD *list_glb, int xPos, int yPos, int count, int list_length);

static CORD min_cell(int width, int height, CELL *map, CORD cord);

#endif
