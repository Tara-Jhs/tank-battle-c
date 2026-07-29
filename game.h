#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#define DELTA_T 0.1 // ina ro avaz kardam 
#define GRAVITY 0.4 // 
#define P 3.14159265358
#define GRID_HEIGHT 22
#define GRID_WIDTH 121
#define TANK_HEIGHT 4
#define TANK_WIDTH 9
struct Tank
{
    char Tank_shape[TANK_HEIGHT][TANK_WIDTH];
    int Px;
    int Py;
    int health;
};
void GameDrawing(char grid[GRID_HEIGHT][GRID_WIDTH], struct Tank *tank1, struct Tank *tank2);
void PlaceTanksRandomly(struct Tank *tank1, struct Tank *tank2);
void StatusDrawing(struct Tank *tank1, struct Tank *tank2);
void GameDrawing2(char grid[GRID_HEIGHT][GRID_WIDTH], struct Tank *tank1, struct Tank *tank2);
int GridForTank1(int i, int j, struct Tank *tank);
int GridForTank2(int i, int j, struct Tank *tank);
double Angle(int *player);
int Power(int *player);
int TankMovement(struct Tank *tank1, struct Tank *tank2, struct Tank *b1, struct Tank *b2, int *player, char grid[GRID_HEIGHT][GRID_WIDTH], int *back1, int *back2);
double VX(double angle, int power);
double VY(double angle, int power);
double deltax(double Vx, double t, int x0b);
double deltay(double Vy, double t, int y0b);
int EndOfBulletMovement(struct Tank *tank1, struct Tank *tank2, char grid[GRID_HEIGHT][GRID_WIDTH], int xfb, int yfb, int *player, int t, int x0b, int y0b, int power, double angle,double Vx,double Vy);
int EndOfTheGame(struct Tank *tank1, struct Tank *tank2);
void DELTATBACK(double Vx ,double Vy,double t,int x0b,int y0b,char grid[GRID_HEIGHT][GRID_WIDTH],struct Tank *tank1, struct Tank *tank2);