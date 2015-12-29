#ifndef TSNAKE_FRUIT_H
#define TSNAKE_FRUIT_H

#include "point.h"

struct tsnake_fruit;

//Создание фрукта
void tsnake_fruit_create(struct tsnake_fruit **f, const int x, const int y);
//Удаление фрукта
void tsnake_fruit_destroy(struct tsnake_fruit *f);
//Получение координат фрукта
struct tsnake_point * tsnake_fruit_get_coords(struct tsnake_fruit *f);
//Рисование фрукта
int tsnake_fruit_to_map(struct tsnake_fruit *f, char **map, const int height, const int width);

#endif