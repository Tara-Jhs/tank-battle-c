#include <stdio.h>
#include "game.h"
#include <time.h>
#include <unistd.h>
#include "windows.h"


int main(void)
{
    struct Tank tank1 = {
        .Tank_shape = {
            "   __    ",
            " _|__|_//",
            "|_______|"},
        .Px = 0,
        .Py = 19,
        .health = 100};
    struct Tank tank2 = {
        .Tank_shape = {
            "    __   ",
            "\\\\_|__|_ ",
            "|_______|"},
        .Px = 90,
        .Py = 19,
        .health = 100};
    struct Tank b1;
    struct Tank b2;
    int player = 1;
    int i, j;
    char move;
    int status;
    double angle;
    int power;
    int x0b;
    int y0b;
    int back1 = 1;
    int back2 = 1;
    double xfb = 0;
    double yfb = 0;
    double t, Vx, Vy;
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
        b1 = tank1;
        b2 = tank2;
        GameDrawing(grid, &tank1, &tank2);
        status = TankMovement(&tank1, &tank2, &b1, &b2, &player, grid, &back1, &back2);
        if (status == 0)
        {
            continue;
        }
        if (status == -1)
        {
            break;
        }
        angle = Angle(&player);
        if (angle == -1)
        {
            if (player == 1)
            {
                player = 2;
                continue;
            }
            else
            {
                player = 1;
                continue;
            }
        }
        power = Power(&player);
        if (power == -1)
        {
            if (player == 1)
            {
                player = 2;
                continue;
            }
            else
            {
                player = 1;
                continue;
            }
        }
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
            Vx = -Vx;
        }
        t = 0;
        Vy = VY(angle, power);
        xfb = x0b;
        yfb = y0b;

        while (EndOfBulletMovement(&tank1, &tank2, grid, xfb, yfb, &player, t, x0b, y0b, power, angle, Vx, Vy))
        {
            
            // man kollan ye seri jaha ro ke nemikhastam test konam comment kardam mesle DELTATBACK, ye seri print e ezafi ham gozashtam, "cout" ham hamum print e age nadide budi 
            // age compile nashod imclude ha ro check kon, cout ha ro bokon printf, 
            // age run beshe bayad bebini ke golule harkat mikone va masiresh moshakhas mishe. 
            
            while ((xfb - x0b) + (yfb - y0b) <= 6)
            {
                xfb = x0b + deltax(Vx, t, x0b);
                yfb = y0b - deltay(Vy, t, y0b);
                t = t + DELTA_T;
            }
            grid[(int)yfb][(int)xfb] = '*';
            GameDrawing2(grid, &tank1, &tank2);
            //Sleep(750);
            //system("cls");
            grid[(int)yfb][(int)xfb] = ' ';   // ina ro pak kardam ke masir e bullet malum beshe
            x0b = xfb;
            y0b = yfb;
            continue;
        }
        if (EndOfTheGame(&tank1, &tank2) == 1)
        {
            break;
        }
        continue;
    }
    return 0;
}