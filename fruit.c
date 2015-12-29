#include "fruit.h"

#include <stdlib.h>

struct tsnake_fruit
{
	struct tsnake_point *coords;
};
typedef struct tsnake_fruit tsnake_fruit_t;

void tsnake_fruit_create(tsnake_fruit_t **f, const int x, const int y)
{
	(*f) = (tsnake_fruit_t *) malloc(sizeof(tsnake_fruit_t));
	struct tsnake_point *_coords;
	tsnake_point_create(&_coords, x, y);
	(*f)->coords = _coords;
}

void tsnake_fruit_destroy(tsnake_fruit_t *f)
{
	tsnake_point_destroy(f->coords);
	free(f);
}

struct tsnake_point * tsnake_fruit_get_coords(tsnake_fruit_t *f)
{
	return f->coords;
}

int tsnake_fruit_to_map(tsnake_fruit_t *f, char **map, const int height, const int width)
{
	unsigned x = tsnake_point_get_x(f->coords);
	unsigned y = tsnake_point_get_y(f->coords);
	if (x < width && y < height)
		map[x][y] = '0';
}