#include "body.h"

#include <stdlib.h>

struct tsnake_body
{
	struct tsnake_point *coords;
	struct tsnake_body *next;
};
typedef struct tsnake_body tsnake_body_t;

void tsnake_body_create(tsnake_body_t **b, tsnake_body_t *next, const int x, const int y)
{
	(*b) = (tsnake_body_t *) malloc(sizeof(tsnake_body_t));
	struct tsnake_point *_coords;
	tsnake_point_create(&_coords, x, y);
	(*b)->coords = _coords;
	(*b)->next = next;
}

void tsnake_body_destroy(tsnake_body_t *b)
{
	tsnake_point_destroy(b->coords);
	if (b->next != NULL)
		tsnake_body_destroy(b->next);
	free(b);
}

void tsnake_body_destroy_last(tsnake_body_t *b)
{
	tsnake_body_t *t = b;
	while (t->next->next != NULL)
		t = t->next;
	tsnake_body_t *last = t->next;
	t->next = NULL;
	tsnake_body_destroy(last);
}

void tsnake_body_clone(tsnake_body_t *from, tsnake_body_t **to)
{
	tsnake_body_create(to, from->next, tsnake_point_get_x(from->coords), tsnake_point_get_y(from->coords));
}

struct tsnake_point * tsnake_body_get_coords(tsnake_body_t *b)
{
	return b->coords;
}

tsnake_body_t * tsnake_body_get_next(tsnake_body_t *b)
{
	return b->next;
}