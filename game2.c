#include <stdio.h>
#include "game2.h"
#include <time.h>
#include <string.h>
int main(void)
{
    Tank tank1 = {
        .Tank_shape = {
            "   __    ",
            " _|__|_//",
            "|_______|"},
        .Px = 0,
        .Py = 19,
        .health = 100};
    Tank tank2 = {
        .Tank_shape = {
            "    __   ",
            "\\\\_|__|_ ",
            "|_______|"},
        .Px = 90,
        .Py = 19,
        .health = 100};
    Tank b1, b2;
    int player = 1;
    int i, j;
    char move;
    int status;
    double angle, power;
    int x0b, y0b;
    int back1 = 1, back2 = 1;
    double xfb = 0, yfb = 0;
    double t, Vx, Vy;
    char grid_backup[GRID_HEIGHT][GRID_WIDTH];
    srand(time(NULL));
    char grid[GRID_HEIGHT][GRID_WIDTH] = {
        "                  ^                                                                                                     ",
        "                 ^^^                                                                            ^                       ",
        "                ^^^^^                                                                          ^^^                      ",
        "                                                                                              ^^^^^                     ",
        "                                                                                                                        ",
        "                                                                                                                        ",
        "                      ^^                                                                                                ",
        "                     ^^^^                                                                                               ",
        "                    ^^^^^^                                                                                    ^         ",
        "                                                                                                             ^^^        ",
        "                                                                                                                        ",
        "                                                                                                                        ",
        "                                                          ^                                                             ",
        "                                                         ^^^         ^^                                                 ",
        "                                                        ^^^^^       ^^^^                                                ",
        "                                               ^       ^^^^^^^^    ^^^^^^                                               ",
        "                                              ^^^     ^^^^^^^^^^  ^^^^^^^^     ^                                        ",
        "                                   ^^        ^^^^^  ^^^^^^^^^^^^^^^^^^^^^^^^  ^^^                                       ",
        "                                  ^^^^     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                      ",
        "                                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                    ",
        "########################################################################################################################",
        "########################################################################################################################",
    };
    PlaceTanksRandomly(&tank1, &tank2);
    while (1)
    {
        system("cls");
        GameDrawing(grid, &tank1, &tank2);
        status = TankMovement(&tank1, &tank2, &player, grid, grid_backup, &back1, &back2);
        if (status == 0)
        {
            continue;
        }
        if (status == -1)
        {
            break;
        }
        if (status == 2)
        {
            if ((player == 1 && back1 == 1) || (player == 2 && back2 == 1))
            {
                tank1 = b1;
                tank2 = b2;
                memcpy(grid, grid_backup, GRID_HEIGHT * GRID_WIDTH);
                if (player == 1)
                    back1 = 0;
                else
                    back2 = 0;

                system("cls");
                GameDrawing(grid, &tank1, &tank2);
            }
        }
        b1 = tank1;
        b2 = tank2;
        memcpy(grid_backup, grid, GRID_HEIGHT * GRID_WIDTH);
        angle = Angle(&player);
        if (angle == -1)
        {
            if (player == 1)
            {
                player = 2;
                Sleep(3000);
                system("cls");
                continue;
            }
            else
            {
                player = 1;
                Sleep(3000);
                system("cls");
                continue;
            }
        }
        power = Power(&player);
        if (power == -1)
        {
            if (player == 1)
            {
                player = 2;
                Sleep(3000);
                system("cls");
                continue;
            }
            else
            {
                player = 1;
                Sleep(3000);
                system("cls");
                continue;
            }
        }
        Sleep(750);
        system("cls");
        if (player == 1)
        {
            y0b = tank1.Py - 2;
            x0b = tank1.Px + 9;
            Vx = VX(angle, power);
        }
        else if (player == 2)
        {
            y0b = tank2.Py - 2;
            x0b = tank2.Px - 1;
            Vx = VX(angle, power);
        }
        char temp = ' ';
        temp = grid[y0b][x0b];
        grid[y0b][x0b] = '*';
        GameDrawing2(grid, &tank1, &tank2);
        Sleep(750);
        system("cls");
        grid[y0b][x0b] = temp;
        xfb = x0b;
        yfb = y0b;
        t = 0;
        Vy = VY(angle, power);
        double last_x = x0b;
        double last_y = y0b;
        double dist_since_last = 0;
        while (1)
        {
            xfb = x0b + deltax(Vx, t, x0b);
            yfb = y0b - deltay(Vy, t, y0b);
            dist_since_last += fabs(xfb - last_x) + fabs(yfb - last_y);
            if (EndOfBulletMovement(&tank1, &tank2, grid, &xfb, &yfb, &player, t, x0b, y0b, Vx, Vy, &temp) == 0)
            {
                break;
            }
            if (dist_since_last >= 6)
            {
                if ((int)yfb >= 0 && (int)yfb < GRID_HEIGHT &&
                    (int)xfb >= 0 && (int)xfb < GRID_WIDTH)
                {
                    temp = grid[(int)yfb][(int)xfb];
                    grid[(int)yfb][(int)xfb] = '*';
                    GameDrawing2(grid, &tank1, &tank2);
                    Sleep(750);
                    system("cls");
                    grid[(int)yfb][(int)xfb] = temp;
                }
                last_x = xfb;
                last_y = yfb;
                dist_since_last = 0;
            }
            t += DELTA_T;
        }
        int winner = (EndOfTheGame(&tank1, &tank2));
        if (winner == 0)
        {
            continue;
        }
        else if (winner == 1)
        {
            printf("--------------------------------------------------------PLAYER 1 WINS-----------------------------------------------------\n");
            break;
        }
        else
        {
            printf("--------------------------------------------------------PLAYER 2 WINS-----------------------------------------------------\n");
            break;
        }
    }
    return 0;
}