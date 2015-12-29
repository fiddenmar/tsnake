#ifndef TSNAKE_POINT_H
#define TSNAKE_POINT_H

struct tsnake_point;

void tsnake_point_create(struct tsnake_point **p, const int x, const int y);
void tsnake_point_destroy(struct tsnake_point *p);
int tsnake_point_collide(struct tsnake_point *a, struct tsnake_point *b);
int tsnake_point_get_x(struct tsnake_point *p);
int tsnake_point_get_y(struct tsnake_point *p);

#endif