#include "point.h"

#include <stdlib.h>

struct tsnake_point
{
	int x;
	int y;
};
typedef struct tsnake_point tsnake_point_t;

void tsnake_point_create(tsnake_point_t **p, const int x, const int y)
{
	*p = (tsnake_point_t *) malloc(sizeof(tsnake_point_t));
	(*p)->x = x;
	(*p)->y = y;
}

void tsnake_point_destroy(tsnake_point_t *p)
{
	free(p);
}

int tsnake_point_collide(tsnake_point_t *a, tsnake_point_t *b)
{
	if (a->x == b->x && a->y == b->y)
		return 1;
	return 0;
}

int tsnake_point_get_x(tsnake_point_t *p)
{
	return p->x;
}

int tsnake_point_get_y(tsnake_point_t *p)
{
	return p->y;
}