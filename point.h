#ifndef TSNAKE_POINT_H
#define TSNAKE_POINT_H

struct tsnake_point;

//Создание точки
void tsnake_point_create(struct tsnake_point **p, const int x, const int y);
//Удаление точки
void tsnake_point_destroy(struct tsnake_point *p);
//Проверка на коллизию двух точек
int tsnake_point_collide(struct tsnake_point *a, struct tsnake_point *b);
//Получение координаты x точки
int tsnake_point_get_x(struct tsnake_point *p);
//Получение координаты y точки
int tsnake_point_get_y(struct tsnake_point *p);

#endif