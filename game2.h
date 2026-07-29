#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#define DELTA_T 0.1 // 1
#define GRAVITY 0.4 // 0.06
#define P 3.14159265358
#define GRID_HEIGHT 22
#define GRID_WIDTH 121
#define TANK_HEIGHT 4
#define TANK_WIDTH 9
typedef struct Tank
{
    char Tank_shape[TANK_HEIGHT][TANK_WIDTH];
    int Px;
    int Py;
    int health;
} Tank;
void GameDrawing(char grid[GRID_HEIGHT][GRID_WIDTH], Tank *tank1, Tank *tank2);
void PlaceTanksRandomly(Tank *tank1, Tank *tank2);
void StatusDrawing(Tank *tank1, Tank *tank2);
void GameDrawing2(char grid[GRID_HEIGHT][GRID_WIDTH], Tank *tank1, Tank *tank2);
int GridForTank1(int i, int j, Tank *tank);
int GridForTank2(int i, int j, Tank *tank);
double Angle(int *player);
double Power(int *player);
int TankMovement(Tank *tank1, Tank *tank2, int *player, char grid[GRID_HEIGHT][GRID_WIDTH], char grid_backup[GRID_HEIGHT][GRID_WIDTH], int *back1, int *back2);
double VX(double angle, double power);
double VY(double angle, double power);
double deltax(double Vx, double t, int x0b);
double deltay(double Vy, double t, int y0b);
int EndOfBulletMovement(Tank *tank1, Tank *tank2, char grid[GRID_HEIGHT][GRID_WIDTH], double *xfb, double *yfb, int *player, double t, int x0b, int y0b, double Vx, double Vy, char *temp);
int EndOfTheGame(Tank *tank1, Tank *tank2);
void DELTATBACK(double Vx, double Vy, double *t, int x0b, int y0b, double *xfb, double *yfb, char grid[GRID_HEIGHT][GRID_WIDTH], Tank *tank1, Tank *tank2, char *temp);