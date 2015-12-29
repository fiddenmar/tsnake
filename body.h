#ifndef TSNAKE_BODY_H
#define TSNAKE_BODY_H

#include "point.h"

struct tsnake_body;

//Создание тела
void tsnake_body_create(struct tsnake_body **b, struct tsnake_body *next, const int x, const int y);
//Удаление тела от текущего элемента до конца
void tsnake_body_destroy(struct tsnake_body *b);
//Удаление хвоста
void tsnake_body_destroy_last(struct tsnake_body *b);
//Клонирование тела
void tsnake_body_clone(struct tsnake_body *from, struct tsnake_body **to);
//Получение координат тела
struct tsnake_point * tsnake_body_get_coords(struct tsnake_body *b);
//Следующее тело
struct tsnake_body * tsnake_body_get_next(struct tsnake_body *b);

#endif