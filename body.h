#ifndef TSNAKE_BODY_H
#define TSNAKE_BODY_H

#include "point.h"

struct tsnake_body;

void tsnake_body_create(struct tsnake_body **b, struct tsnake_body *next, const int x, const int y);
void tsnake_body_destroy(struct tsnake_body *b);
void tsnake_body_destroy_last(struct tsnake_body *b);
void tsnake_body_clone(struct tsnake_body *from, struct tsnake_body **to);
struct tsnake_point * tsnake_body_get_coords(struct tsnake_body *b);
struct tsnake_body * tsnake_body_get_next(struct tsnake_body *b);

#endif