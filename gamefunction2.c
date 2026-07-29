#include <stdio.h>
#include "game2.h"
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
void PlaceTanksRandomly(Tank *tank1, Tank *tank2)
{
    tank1->Px = rand() % (24 - 0 + 1) + 0;
    tank2->Px = rand() % (111 - 85 + 1) + 85;
    tank1->Py = tank2->Py = 19;
}
void StatusDrawing(Tank *tank1, Tank *tank2)
{
    printf("==========================================================================================================================\n");
    printf("|                         [P1] TANK ALPHA  | HEALTH: %3d%%   ||   [P2] TANK BETA  | HEALTH: %3d%%                          |\n",
           tank1->health, tank2->health);
    printf("==========================================================================================================================\n");
}
int GridForTank1(int i, int j, Tank *tank)
{
    if (i >= tank->Py - 2 && i <= tank->Py &&
        j >= tank->Px && j < tank->Px + 9)
    {
        return 1;
    }
    return 0;
}
int GridForTank2(int i, int j, Tank *tank)
{
    if (i >= tank->Py - 2 && i <= tank->Py &&
        j >= tank->Px && j < tank->Px + 9)
    {
        return 1;
    }
    return 0;
}
void GameDrawing(char grid[GRID_HEIGHT][GRID_WIDTH], Tank *tank1, Tank *tank2)
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
                putchar(tank1->Tank_shape[i - (tank1->Py - 2)][j - tank1->Px]);
            else if (GridForTank2(i, j, tank2))
                putchar(tank2->Tank_shape[i - (tank2->Py - 2)][j - tank2->Px]);
            else
                putchar(grid[i][j]);
        }
        printf("|");
        putchar('\n');
    }
    printf("|------------------------------------------------------------------------------------------------------------------------|\n");
}
void GameDrawing2(char grid[GRID_HEIGHT][GRID_WIDTH], Tank *tank1, Tank *tank2)
{
    printf("|------------------------------------------------------------------------------------------------------------------------|\n");
    for (int i = 0; i < 22; i++)
    {
        printf("|");
        for (int j = 0; j < 120; j++)
        {
            if (GridForTank1(i, j, tank1))
                putchar(tank1->Tank_shape[i - (tank1->Py - 2)][j - tank1->Px]);
            else if (GridForTank2(i, j, tank2))
                putchar(tank2->Tank_shape[i - (tank2->Py - 2)][j - tank2->Px]);
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
double Power(int *player)
{
    double power;
    printf("(Player [%d]) Enter Shot Power [1-100]: ", *player);
    scanf("%lf", &power);
    if (power < 1 || power > 100)
    {
        printf("Power Out Of Range - Your Turn Is Lost!\n");
        Sleep(3000);
        return -1;
    }
    else
    {
        power = power / 100;
        power = pow(power, 1.5);
        power = 2 + 7 * (power);
        return power;
    }
}
int TankMovement(Tank *tank1, Tank *tank2, int *player, char grid[GRID_HEIGHT][GRID_WIDTH], char grid_backup[GRID_HEIGHT][GRID_WIDTH], int *back1, int *back2)
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
                Sleep(3000);
                system("cls");
                GameDrawing(grid, tank1, tank2);
                continue;
            }
            else
            {
                *player = 1;
                Sleep(3000);
                system("cls");
                GameDrawing(grid, tank1, tank2);
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
            system("cls");
            GameDrawing(grid, tank1, tank2);
            continue; /*rad kard :|*/
        }
        if (move == 'B')
        {
            if (*player == 1)
            {
                if (*back1 == 1)
                {
                    return 2;
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
                    return 2;
                    break; /*1 marhale back*/
                }
                else if (*back2 == 0)
                {
                    printf("Ability Is Already Used - Your Turn Is Lost!");
                    Sleep(3000);
                    system("cls");
                    *player = 1;
                    GameDrawing(grid, tank1, tank2);
                    continue; /*estefade karde bood :|*/
                }
            }
        }
    }
}
double VX(double angle, double power)
{
    angle = (angle)*P / 180;
    double Vx = (power)*cos(angle);
    return Vx;
}
double VY(double angle, double power)
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
void DELTATBACK(double Vx, double Vy, double *t, int x0b, int y0b, double *xfb, double *yfb, char grid[GRID_HEIGHT][GRID_WIDTH], Tank *tank1, Tank *tank2, char *temp)
{
    *t = *t - DELTA_T;
    // Sleep(750);
    // system("cls");
    *xfb = x0b + deltax(Vx, *t, x0b);
    *yfb = y0b - deltay(Vy, *t, y0b);
    *temp = grid[(int)*yfb][(int)*xfb];
    grid[(int)*yfb][(int)*xfb] = '*';
    GameDrawing2(grid, tank1, tank2);
    Sleep(750);
    // system("cls");
    // GameDrawing2(grid, tank1, tank2);
}
int EndOfBulletMovement(Tank *tank1, Tank *tank2, char grid[GRID_HEIGHT][GRID_WIDTH], double *xfb, double *yfb, int *player, double t, int x0b, int y0b, double Vx, double Vy, char *temp)
{
    if ((int)*yfb < 0 || (int)*yfb >= GRID_HEIGHT ||
        (int)*xfb < 0 || (int)*xfb >= GRID_WIDTH)
    {
        DELTATBACK(Vx, Vy, &t, x0b, y0b, xfb, yfb, grid, tank1, tank2, temp);
        printf("Shot Terminated!\n");
        if (EndOfTheGame(tank1, tank2) == 0)
        {
            Sleep(3000);
            system("cls");
            grid[(int)*yfb][(int)*xfb] = *temp;
        }
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
    if (*player == 1)
    {
        if (*yfb >= tank1->Py - 2 && *yfb <= tank1->Py &&
            *xfb >= tank1->Px && *xfb < tank1->Px + 9)
        {
            tank1->health = tank1->health - 20;
            DELTATBACK(Vx, Vy, &t, x0b, y0b, xfb, yfb, grid, tank1, tank2, temp);
            printf("BOOM!!! Friendly Fire\n");
            if (EndOfTheGame(tank1, tank2) == 0)
            {
                Sleep(3000);
                system("cls");
                grid[(int)*yfb][(int)*xfb] = *temp;
            }
            *player = 2;
            return 0; /*zad be kodesh :(*/
        }
        if (*yfb >= tank2->Py - 2 && *yfb <= tank2->Py &&
            *xfb >= tank2->Px && *xfb < tank2->Px + 9)
        {
            tank2->health = tank2->health - 20;
            DELTATBACK(Vx, Vy, &t, x0b, y0b, xfb, yfb, grid, tank1, tank2, temp);
            printf("BOOM!!! Clean Hit On The Enemy\n");
            if (EndOfTheGame(tank1, tank2) == 0)
            {
                Sleep(3000);
                system("cls");
            }
            grid[(int)*yfb][(int)*xfb] = *temp;
            *player = 2;
            return 0; /*zad be harif :)*/
        }
    }
    if (*player == 2)
    {
        if (*yfb >= tank2->Py - 2 && *yfb <= tank2->Py &&
            *xfb >= tank2->Px && *xfb < tank2->Px + 9)
        {
            tank2->health = tank2->health - 20;
            DELTATBACK(Vx, Vy, &t, x0b, y0b, xfb, yfb, grid, tank1, tank2, temp);
            printf("BOOM!!! Friendly Fire\n");
            if (EndOfTheGame(tank1, tank2) == 0)
            {
                Sleep(3000);
                system("cls");
                grid[(int)*yfb][(int)*xfb] = *temp;
            }
            *player = 1;
            return 0; /*zad be kodesh :(*/
        }
        if (*yfb >= tank1->Py - 2 && *yfb <= tank1->Py &&
            *xfb >= tank1->Px && *xfb < tank1->Px + 9)
        {
            tank1->health = tank1->health - 20;
            DELTATBACK(Vx, Vy, &t, x0b, y0b, xfb, yfb, grid, tank1, tank2, temp);
            printf("BOOM!!! Clean Hit On The Enemy\n");
            if (EndOfTheGame(tank1, tank2) == 0)
            {
                Sleep(3000);
                system("cls");
            }
            grid[(int)*yfb][(int)*xfb] = *temp;
            *player = 1;
            return 0; /*zad be harif :)*/
        }
    }
    if (grid[(int)*yfb][(int)*xfb] == '^' || grid[(int)*yfb][(int)*xfb] == '#' || grid[(int)*yfb][(int)*xfb] == '"')
    {
        DELTATBACK(Vx, Vy, &t, x0b, y0b, xfb, yfb, grid, tank1, tank2, temp);
        printf("Shot Terminated!\n");
        if (EndOfTheGame(tank1, tank2) == 0)
        {
            Sleep(3000);
            system("cls");
            grid[(int)*yfb][(int)*xfb] = *temp;
        }
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
int EndOfTheGame(Tank *tank1, Tank *tank2)
{
    if (tank2->health <= 0)
    {
        return 1;
    }
    else if (tank1->health <= 0)
    {
        return 2;
    }
    return 0;
}