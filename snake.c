#include "snake.h"

#include <stdlib.h>

#include "body.h"

struct tsnake_snake
{
	struct tsnake_body *head;
};
typedef struct tsnake_snake tsnake_snake_t;

typedef enum tsnake_move_direction tsnake_move_direction_t;

typedef enum tsnake_move_result tsnake_move_result_t;

void tsnake_snake_create(tsnake_snake_t **s, const int x, const int y)
{
	(*s) = (tsnake_snake_t *) malloc(sizeof(tsnake_snake_t));
	struct tsnake_body *_tail;
	tsnake_body_create(&_tail, NULL, x-2, y);
	struct tsnake_body *_body;
	tsnake_body_create(&_body, _tail, x-1, y);
	struct tsnake_body *_head;
	tsnake_body_create(&_head, _body, x, y);
	(*s)->head = _head;
}

void tsnake_snake_destroy(tsnake_snake_t *s)
{
	tsnake_body_destroy(s->head);
	free(s);
}

static void tsnake_snake_delta_from_direction(int *delta_x, int *delta_y, tsnake_move_direction_t d)
{
	switch (d)
	{
		case TSNAKE_MOVE_DIRECTION_UP:
			*delta_y = -1;
			break;
		case TSNAKE_MOVE_DIRECTION_DOWN:
			*delta_y = 1;
			break;
		case TSNAKE_MOVE_DIRECTION_LEFT:
			*delta_x = -1;
			break;
		case TSNAKE_MOVE_DIRECTION_RIGHT:
			*delta_x = 1;
			break;
	}
}

static tsnake_move_result_t tsnake_snake_check_snake(tsnake_snake_t *s, tsnake_move_direction_t d)
{
	struct tsnake_body *i;

	int delta_x = 0;
	int delta_y = 0;
	tsnake_snake_delta_from_direction(&delta_x, &delta_y, d);
	
	struct tsnake_body *h = s->head;
	struct tsnake_point *h_coords = tsnake_body_get_coords(h);
	int x = tsnake_point_get_x(h_coords);
	int y = tsnake_point_get_y(h_coords);
	tsnake_body_create(&i, NULL, x + delta_x, y + delta_y);
	
	for (struct tsnake_body *t = h; tsnake_body_get_next(t) != NULL; t = tsnake_body_get_next(t))
	{
		if (tsnake_point_collide(tsnake_body_get_coords(i), tsnake_body_get_coords(t)))
		{
			return TSNAKE_MOVE_RESULT_LOSE;
		}
	}
	tsnake_body_destroy(i);
	return TSNAKE_MOVE_RESULT_NONE;
}

static tsnake_move_result_t tsnake_snake_check_fruit(tsnake_snake_t *s, struct tsnake_fruit *f, tsnake_move_direction_t d)
{
	struct tsnake_body *i;

	int delta_x = 0;
	int delta_y = 0;
	tsnake_snake_delta_from_direction(&delta_x, &delta_y, d);

	struct tsnake_body *h = s->head;
	struct tsnake_point *h_coords = tsnake_body_get_coords(h);
	tsnake_body_create(&i, NULL, tsnake_point_get_x(h_coords) + delta_x, tsnake_point_get_y(h_coords) + delta_y);

	struct tsnake_point *a = tsnake_body_get_coords(i);
	struct tsnake_point *b = tsnake_fruit_get_coords(f);
	int res = tsnake_point_collide(a, b);
	tsnake_body_destroy(i);
	if (res)
		return TSNAKE_MOVE_RESULT_FRUIT;
	return TSNAKE_MOVE_RESULT_NONE;
}

static tsnake_move_result_t tsnake_snake_check_coords(tsnake_snake_t *s, tsnake_move_direction_t d, const int field_height, const int field_width)
{
	int delta_x = 0;
	int delta_y = 0;
	tsnake_snake_delta_from_direction(&delta_x, &delta_y, d);

	struct tsnake_body *h = s->head;
	struct tsnake_point *h_coords = tsnake_body_get_coords(h);
	unsigned x = tsnake_point_get_x(h_coords) + delta_x;
	unsigned y = tsnake_point_get_y(h_coords) + delta_y;
	if (x < field_width && y < field_height)
		return TSNAKE_MOVE_RESULT_NONE;
	return TSNAKE_MOVE_RESULT_LOSE;
}

static void tsnake_snake_do_move(tsnake_snake_t *s, tsnake_move_direction_t d, const int result)
{
	struct tsnake_body *t;

	int delta_x = 0;
	int delta_y = 0;
	tsnake_snake_delta_from_direction(&delta_x, &delta_y, d);

	struct tsnake_body *h = s->head;
	struct tsnake_point *h_coords = tsnake_body_get_coords(h);
	tsnake_body_create(&t, s->head, tsnake_point_get_x(h_coords) + delta_x, tsnake_point_get_y(h_coords) + delta_y);
	s->head = t;
	if (!(result & TSNAKE_MOVE_RESULT_FRUIT))
		tsnake_body_destroy_last(t);
}

int tsnake_snake_move(tsnake_snake_t *s, struct tsnake_fruit *f, tsnake_move_direction_t d, const int field_height, const int field_width)
{
	int result = 0;
	result |= tsnake_snake_check_snake(s, d);
	result |= tsnake_snake_check_fruit(s, f, d);
	result |= tsnake_snake_check_coords(s, d, field_height, field_width);
	tsnake_snake_do_move(s, d, result);
	return result;
}

int tsnake_snake_to_map(tsnake_snake_t *s, char **map, const int height, const int width)
{
	struct tsnake_body *h = s->head;
	for (struct tsnake_body *t = h; t != NULL; t = tsnake_body_get_next(t))
	{
		struct tsnake_point *coords = tsnake_body_get_coords(t);
		map[tsnake_point_get_x(coords)][tsnake_point_get_y(coords)] = '#';
	}
}

int tsnake_snake_collide(tsnake_snake_t *s, struct tsnake_point *p)
{
	for (struct tsnake_body *t = s->head; t != NULL; t = tsnake_body_get_next(t))
	{
		if (tsnake_point_collide(p, tsnake_body_get_coords(t)))
		{
			return 1;
		}
	}
	return 0;
}
