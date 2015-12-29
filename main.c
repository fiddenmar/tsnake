#define _BSD_SOURCE

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "snake.h"
#include "fruit.h"


//Создание фрукта с учетом положения змеи (исключение возможности коллизии при создании)
void spawn_fruit(struct tsnake_fruit **f, struct tsnake_snake *s, int heigth, int width)
{
    int collide = 1;
    int x;
    int y;
    while (collide)
    {
        x = rand()%(width*9 / 10) + 3;
        y = rand()%(heigth*9 / 10) + 3;
        struct tsnake_point *coords;
        tsnake_point_create(&coords, x, y);
        collide = tsnake_snake_collide(s, coords);
    }
    tsnake_fruit_create(f, x, y);
}

//Очистка поля
void clear_map(char **map, const int height, const int width)
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            map[i][j] = '.';
        }
}

//Вывод поля на экран
void print_map(char **map, const int height, const int width)
{
    for (int i=0; i<height; i++)
    {
        char *string = (char *) malloc(sizeof(char)*(width+1));
        for (int j=0; j<width; j++)
        {
            string[j] = map[j][i];
        }
        string[width] = '\0';
        mvprintw(i+2, 0, "%s", string);
        free(string);
    }
}

//Проверка нажатия клавиши
int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main(void)
{
    initscr();

    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, FALSE);


    srand(time(NULL));

    int width = 40;
    int height = 20;
    char **map = (char **) malloc(sizeof(char*)*width);
    for (int i = 0; i < width; i++)
    {
        map[i] = (char *) malloc(sizeof(char)*height);
    }
    clear_map(map, height, width);

    char control;
    enum tsnake_move_direction current_move = TSNAKE_MOVE_DIRECTION_RIGHT;
    enum tsnake_move_direction last_move = TSNAKE_MOVE_DIRECTION_RIGHT;
    struct tsnake_snake *snake;
    tsnake_snake_create(&snake, width/2, height/2);
    struct tsnake_fruit *fruit;
    spawn_fruit(&fruit, snake, height, width);

    int score = 0;
    int lose = 0;

//Игровой цикл
    while (1)
    {
        if (!lose)
        {
            //Рисование
            clear_map(map, height, width);
            tsnake_fruit_to_map(fruit, map, height, width);
            tsnake_snake_to_map(snake, map, height, width);
            print_map(map, height, width);
            refresh();

            usleep(200000);

            //Обработка ввода
            if (kbhit())
            {
                control = getch();
                last_move = current_move;
                switch (control)
                {
                    case 'w':
                    case 'W':
                        if (last_move != TSNAKE_MOVE_DIRECTION_DOWN)
                            current_move = TSNAKE_MOVE_DIRECTION_UP;
                        break;
                    case 'a':
                    case 'A':
                        if (last_move != TSNAKE_MOVE_DIRECTION_RIGHT)
                            current_move = TSNAKE_MOVE_DIRECTION_LEFT;
                        break;
                    case 's':
                    case 'S':
                        if (last_move != TSNAKE_MOVE_DIRECTION_UP)
                            current_move = TSNAKE_MOVE_DIRECTION_DOWN;
                        break;
                    case 'd':
                    case 'D':
                        if (last_move != TSNAKE_MOVE_DIRECTION_LEFT)
                            current_move = TSNAKE_MOVE_DIRECTION_RIGHT;
                        break;
                }
            }
            else
            {
                last_move = current_move;
            }

            //Движение змеи
            int result = tsnake_snake_move(snake, fruit, current_move, height, width);

            //Обновление состояния игры на основе результатов движения
            if (result & TSNAKE_MOVE_RESULT_FRUIT)
            {
                score+10;
                tsnake_fruit_destroy(fruit);
                spawn_fruit(&fruit, snake, height, width);
            }
            if (result & TSNAKE_MOVE_RESULT_LOSE)
                lose = 1;
        }
        else
        {
            //Экран проигрыша
            mvprintw(1, 0, "Game over! Press ^C to exit");
            refresh();
        }
        mvprintw(0, 0, "Score: %d", score);
    }

    //Очистка
    tsnake_snake_destroy(snake);
    tsnake_fruit_destroy(fruit);
    for (int i = 0; i < width; i++)
    {
        free(map[i]);
    }
    free(map);
}