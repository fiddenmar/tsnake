#ifndef TSNAKE_SNAKE_H
#define TSNAKE_SNAKE_H

#include "fruit.h"

struct tsnake_snake;
enum tsnake_move_direction;

void tsnake_snake_create(struct tsnake_snake **s, const int x, const int y);
void tsnake_snake_destroy(struct tsnake_snake *s);
int tsnake_snake_move(struct tsnake_snake *s, struct tsnake_fruit *f, const enum tsnake_move_direction, const int field_height, const int field_width);
int tsnake_snake_to_map(struct tsnake_snake *s, char **map, const int height, const int width);
int tsnake_snake_collide(struct tsnake_snake *s, struct tsnake_point *p);

enum tsnake_move_direction
{
	TSNAKE_MOVE_DIRECTION_UP,
	TSNAKE_MOVE_DIRECTION_DOWN,
	TSNAKE_MOVE_DIRECTION_LEFT,
	TSNAKE_MOVE_DIRECTION_RIGHT
};

enum tsnake_move_result
{
	TSNAKE_MOVE_RESULT_NONE,
	TSNAKE_MOVE_RESULT_LOSE,
	TSNAKE_MOVE_RESULT_FRUIT
};

#endif