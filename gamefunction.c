#include <stdio.h>
#include "game.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include<windows.h>
void PlaceTanksRandomly(struct Tank *tank1, struct Tank *tank2)
{
    tank1->Px = rand() % (24 - 0 + 1) + 0;
    tank2->Px = rand() % (111 - 85 + 1) + 85;
    tank1->Py = tank2->Py = 19;
}
void StatusDrawing(struct Tank *tank1, struct Tank *tank2)
{
    printf("==========================================================================================================================\n");
    printf("|                         [P1] TANK ALPHA  | HEALTH: %d%%   ||   [P2] TANK BETA  | HEALTH: %d%%                          |\n",
           tank1->health, tank2->health);
    printf("==========================================================================================================================\n");
}
int GridForTank1(int i, int j, struct Tank *tank)
{
    if (i >= tank->Py - 2 && i <= tank->Py &&
        j >= tank->Px && j < tank->Px + 9)
    {
        return 1;
    }
    return 0;
}
int GridForTank2(int i, int j, struct Tank *tank)
{
    if (i >= tank->Py - 2 && i <= tank->Py &&
        j >= tank->Px && j < tank->Px + 9)
    {
        return 1;
    }
    return 0;
}
void GameDrawing(char grid[GRID_HEIGHT][GRID_WIDTH], struct Tank *tank1, struct Tank *tank2)
{
    // system("cls");
    StatusDrawing(tank1, tank2);
    printf("|------------------------------------------------------------------------------------------------------------------------|\n");
    for (int i = 0; i < 22; i++)
    {
        printf("|");
        for (int j = 0; j < 120; j++)
        {
            if (GridForTank1(i, j, tank1))
                putchar(tank1->Tank_shape[i - 17][j - tank1->Px]);
            else if (GridForTank2(i, j, tank2))
                putchar(tank2->Tank_shape[i - 17][j - tank2->Px]);
            else
                putchar(grid[i][j]);
        }
        printf("|");
        putchar('\n');
    }
    printf("|------------------------------------------------------------------------------------------------------------------------|\n");
}
void GameDrawing2(char grid[GRID_HEIGHT][GRID_WIDTH], struct Tank *tank1, struct Tank *tank2)
{
    printf("|------------------------------------------------------------------------------------------------------------------------|\n");
    for (int i = 0; i < 22; i++)
    {
        printf("|");
        for (int j = 0; j < 120; j++)
        {
            if (GridForTank1(i, j, tank1))
                putchar(tank1->Tank_shape[i - 17][j - tank1->Px]);
            else if (GridForTank2(i, j, tank2))
                putchar(tank2->Tank_shape[i - 17][j - tank2->Px]);
            else
                putchar(grid[i][j]);
        }
        printf("|");
        putchar('\n');
    }
    printf("|------------------------------------------------------------------------------------------------------------------------|\n");
}
double Angle(int *player)
{
    double angle;
    printf("(Player [%d]) Enter Firing Angle [0-180]:", *player);
    scanf("%lf", &angle);
    if (angle < 0 || angle > 180)
    {
        printf("Angle Out Of Range - Your Turn Is Lost!\n");
        Sleep(3000);
        return -1;
    }
    else
    {
        if (*player == 1)
        {
            return angle;
        }
        else
        {
            angle = 180 - angle;
            return angle;
        }
    }
}
int Power(int *player)
{
    double power;
    printf("(Player [%d]) Enter Shot Power [1-100]: ", *player);
    scanf("%lf", &power);
    if (power < 0 || power > 100)
    {
        printf("Power Out Of Range - Your Turn Is Lost!\n");
        Sleep(3000);
        return -1;
    }
    else
    {
        power = power / 100;;
        power = pow(power, 1.5);
        power = 2 + 7 * (power);
        return power;
    }
}
int TankMovement(struct Tank *tank1, struct Tank *tank2, struct Tank *b1, struct Tank *b2, int *player, char grid[GRID_HEIGHT][GRID_WIDTH], int *back1, int *back2)
{
    char move;
    int n;
    while (1)
    {
        printf("(Player %d ) Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game, B=Back:", *player);
        scanf(" %c", &move);
        if (move != 'N' && move != 'Q' && move != 'S' && move != 'L' && move != 'R' && move != 'B')
        {
            printf("Invalid Command - Your Turn Is Lost!\n");
            if (*player == 1)
            {
                *player = 2;
                continue;
            }
            else
            {
                *player = 1;
                continue;
            }
        }
        if (move == 'L' || move == 'R')
        {
            scanf("%d", &n);
            if (move == 'R')
            {
                if (*player == 1)
                {
                    tank1->Px = tank1->Px + n;
                    if (tank1->Px < 0 || tank1->Px > 24)
                    {
                        printf("Illegal Move - Your Turn Is Lost!");
                        *player = 2;
                        Sleep(3000);
                        system("cls");
                        tank1->Px = tank1->Px - n;
                        GameDrawing(grid, tank1, tank2);
                        continue;
                    }
                    else
                    {
                        system("cls");
                        GameDrawing(grid, tank1, tank2);
                        return 1; /*doroste*/
                        break;
                    }
                }
                else if (*player == 2)
                {
                    tank2->Px = tank2->Px + n;
                    if (tank2->Px < 85 || tank2->Px > 111)
                    {
                        printf("Illegal Move - Your Turn Is Lost!");
                        *player = 1;
                        Sleep(3000);
                        system("cls");
                        tank2->Px = tank2->Px - n;
                        GameDrawing(grid, tank1, tank2);
                        continue;
                    }
                    else
                    {
                        system("cls");
                        GameDrawing(grid, tank1, tank2);
                        return 1; /*doroste*/
                        break;
                    }
                }
            }
            else if (move == 'L')
            {
                if (*player == 1)
                {
                    tank1->Px = tank1->Px - n;
                    if (tank1->Px < 0 || tank1->Px > 24)
                    {
                        printf("Illegal Move - Your Turn Is Lost!");
                        *player = 2;
                        Sleep(3000);
                        system("cls");
                        tank1->Px = tank1->Px + n;
                        GameDrawing(grid, tank1, tank2);
                        continue;
                    }
                    else
                    {
                        system("cls");
                        GameDrawing(grid, tank1, tank2);
                        return 1; /*doroste*/
                        break;
                    }
                }
                else if (*player == 2)
                {
                    tank2->Px = tank2->Px - n;
                    if (tank2->Px < 85 || tank2->Px > 111)
                    {
                        printf("Illegal Move - Your Turn Is Lost!");
                        *player = 1;
                        Sleep(3000);
                        system("cls");
                        tank2->Px = tank2->Px + n;
                        GameDrawing(grid, tank1, tank2);
                        continue;
                    }
                    else
                    {
                        system("cls");
                        GameDrawing(grid, tank1, tank2);
                        return 1; /*doroste*/
                        break;
                    }
                }
            }
        }
        if (move == 'N')
        {
            PlaceTanksRandomly(tank1, tank2);
            *player = 1;
            system("cls");
            tank1->health = 100;
            tank2->health = 100;
            *back1 = 1;
            *back2 = 1;
            return 0; /*bazi az aval*/
            break;
        }
        if (move == 'Q')
        {
            return -1; /*tamam :)*/
            break;
        }
        if (move == 'S')
        {
            if (*player == 1)
            {
                *player = 2;
            }
            else
            {
                *player = 1;
            }
            continue; /*rad kard :|*/
        }
        if (move == 'B')
        {
            if (*player == 1)
            {
                if (*back1 == 1)
                {
                    tank1 = b1;
                    tank2 = b2;
                    *back1 = 0;
                    system("cls");
                    GameDrawing(grid, tank1, tank2);
                    return 1;
                    break; /*1 marhale back*/
                }
                else if (*back1 == 0)
                {
                    printf("Ability Is Already Used - Your Turn Is Lost!");
                    Sleep(3000);
                    system("cls");
                    *player = 2;
                    GameDrawing(grid, tank1, tank2);
                    continue; /*estefade karde bood :|*/
                }
            }
            if (*player == 2)
            {
                if (*back2 == 1)
                {
                    tank1 = b1;
                    tank2 = b2;
                    *back2 = 0;
                    system("cls");
                    GameDrawing(grid, tank1, tank2);
                    return 1;
                    break; /*1 marhale back*/
                }
                else if (*back1 == 0)
                {
                    printf("Ability Is Already Used - Your Turn Is Lost!");
                    Sleep(3000);
                    system("cls");
                    *player = 2;
                    GameDrawing(grid, tank1, tank2);
                    continue; /*estefade karde bood :|*/
                }
            }
        }
    }
}
double VX(double angle, int power)
{
    angle = (angle)*P / 180;
    double Vx = (power)*cos(angle);
    return Vx;
}
double VY(double angle, int power)
{
    angle = (angle)*P / 180;
    double Vy = (power)*sin(angle);
    return Vy;
}
double deltax(double Vx, double t, int x0b)
{
    double deltax = Vx * t;
    return deltax;
}
double deltay(double Vy, double t, int y0b)
{
    double deltay = ((-1.0 / 2.0) * GRAVITY * t * t) + (Vy * t);
    return deltay;
}
void DELTATBACK(double Vx, double Vy, double t, int x0b, int y0b, char grid[GRID_HEIGHT][GRID_WIDTH], struct Tank *tank1, struct Tank *tank2)
{
    t = t - DELTA_T;
    //Sleep(1);
    //system("cls");
    double xfb = x0b + deltax(Vx, t, x0b);
    double yfb = y0b - deltay(Vy, t, y0b);
    xfb = round(xfb);
    yfb = round(yfb);
    grid[(int)yfb][(int)xfb] = '*';
    GameDrawing2(grid, tank1, tank2);
}
int EndOfBulletMovement(struct Tank *tank1, struct Tank *tank2, char grid[GRID_HEIGHT][GRID_WIDTH], int xfb, int yfb, int *player, int t, int x0b, int y0b, int power, double angle, double Vx, double Vy)
{
    if (*player == 1)
    {
        if (yfb >= tank1->Py - 2 && yfb <= tank1->Py &&
            xfb >= tank1->Px && xfb < tank1->Px + 9)
        {
            tank1->health = tank1->health - 20;
            DELTATBACK(Vx, Vy, t, x0b, y0b, grid, tank1, tank2);
            //Sleep(1);
            //system("cls");
            grid[(int)yfb][(int)xfb] = ' ';
            GameDrawing2(grid, tank1, tank2);
            printf("BOOM!!! Friendly Fire\n");
            *player = 2;
            return 0; /*zad be kodesh :(*/
        }
        if (yfb >= tank2->Py - 2 && yfb <= tank2->Py &&
            xfb >= tank2->Px && xfb < tank2->Px + 9)
        {
            tank2->health = tank2->health - 20;
            DELTATBACK(Vx, Vy, t, x0b, y0b, grid, tank1, tank2);
            //Sleep(1);
            //system("cls");
            grid[(int)yfb][(int)xfb] = ' ';
            GameDrawing2(grid, tank1, tank2);
            printf("BOOM!!! Clean Hit On The Enemy\n");
            *player = 2;
            return 0; /*zad be harif :)*/
        }
    }
    if (*player == 2)
    {
        if (yfb >= tank2->Py - 2 && yfb <= tank2->Py &&
            xfb >= tank2->Px && xfb < tank2->Px + 9)
        {
            tank2->health = tank2->health - 20;
            DELTATBACK(Vx, Vy, t, x0b, y0b, grid, tank1, tank2);
            //Sleep(1);
            //system("cls");
            grid[(int)yfb][(int)xfb] = ' ';
            GameDrawing2(grid, tank1, tank2);
            printf("BOOM!!! Friendly Fire\n");
            *player = 1;
            return 0; /*zad be kodesh :(*/
        }
        if (yfb >= tank1->Py - 2 && yfb <= tank1->Py &&
            xfb >= tank1->Px && xfb < tank1->Px + 9)
        {
            tank1->health = tank1->health - 20;
            DELTATBACK(Vx, Vy, t, x0b, y0b, grid, tank1, tank2);
            Sleep(1);
            system("cls");
            grid[(int)yfb][(int)xfb] = ' ';
            GameDrawing2(grid, tank1, tank2);
            printf("BOOM!!! Clean Hit On The Enemy\n");
            *player = 1;
            return 0; /*zad be harif :)*/
        }
    }
    if (grid[yfb][xfb] == '^' || grid[yfb][xfb] == '#' || grid[yfb][xfb] == '"' || yfb < 0 || yfb> 22 ||  xfb< 0 || x0b > 120)
    {
        DELTATBACK(Vx, Vy, t, x0b, y0b, grid, tank1, tank2); 
        //Sleep(1);
        //system("cls");
        GameDrawing2(grid, tank1, tank2);
        printf("Shot Terminated!\n");
        if (*player == 1)
        {
            *player = 2;
        }
        else
        {
            *player = 1;
        }
        return 0;
    }
    return 1;
}
int EndOfTheGame(struct Tank *tank1, struct Tank *tank2)
{
    if (tank2->health == 0)
    {
        printf("--------------------------------------------------------PLAYER 1 WINS-----------------------------------------------------\n");
        return 1;
    }
    else if (tank1->health == 0)
    {
        printf("--------------------------------------------------------PLAYER 2 WINS-----------------------------------------------------\n");
        return 1;
    }
}