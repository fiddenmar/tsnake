#ifndef TSNAKE_SNAKE_H
#define TSNAKE_SNAKE_H

#include "fruit.h"

struct tsnake_snake;
enum tsnake_move_direction;

//Создание змеи
void tsnake_snake_create(struct tsnake_snake **s, const int x, const int y);
//Удаление змеи
void tsnake_snake_destroy(struct tsnake_snake *s);
//движение змеи
int tsnake_snake_move(struct tsnake_snake *s, struct tsnake_fruit *f, const enum tsnake_move_direction, const int field_height, const int field_width);
//Рисование змеи
int tsnake_snake_to_map(struct tsnake_snake *s, char **map, const int height, const int width);
//Проверка змеи на столкновение с точкой
int tsnake_snake_collide(struct tsnake_snake *s, struct tsnake_point *p);

//Возможные значения направления движения
enum tsnake_move_direction
{
	TSNAKE_MOVE_DIRECTION_UP, //Вверх
	TSNAKE_MOVE_DIRECTION_DOWN, //Вниз
	TSNAKE_MOVE_DIRECTION_LEFT, //Влево
	TSNAKE_MOVE_DIRECTION_RIGHT //Вправо
};

//Возможные результаты движения
enum tsnake_move_result
{
	TSNAKE_MOVE_RESULT_NONE, //Ничего
	TSNAKE_MOVE_RESULT_LOSE, //Проигрыш
	TSNAKE_MOVE_RESULT_FRUIT //Столкновение с фруктом
};

#endif