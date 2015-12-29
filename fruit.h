#ifndef TSNAKE_FRUIT_H
#define TSNAKE_FRUIT_H

#include "point.h"

struct tsnake_fruit;

void tsnake_fruit_create(struct tsnake_fruit **f, const int x, const int y);
void tsnake_fruit_destroy(struct tsnake_fruit *f);
struct tsnake_point * tsnake_fruit_get_coords(struct tsnake_fruit *f);
int tsnake_fruit_to_map(struct tsnake_fruit *f, char **map, const int height, const int width);

#endif