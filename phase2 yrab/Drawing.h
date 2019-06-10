#include "FightLogic.h"

//The four regions: A, B, C , and D

//Enemy types: Paver, Fighter, and Shielded Fighter

//constants
#define CmdWidth		150
#define CmdHeight		50
#define CastleWidth		30
#define CastleLength	20
#define CastleXStrt		(CmdWidth/2-(CastleWidth/2))
#define CastleYStrt		(CmdHeight/2-(CastleLength/2))
#define TowerWidth      7
#define TowerLength     3

#define EnemyShape		219  //ASCII code of enemy char shape 
//The four regions: A, B, C , and D

//Enemy types: Paver, Fighter, and Shielded Fighter


//Tower

//Functions Prototype
/*A function to set the position of cursor on the screen*/
void gotoxy(int x, int y);

/*A function to set the command window lenght and height for the game specification*/
void SetWindow();

/*A function to color the cmd text*/
void color(int thecolor);

/*A function to partition the castle into regions (A,B,C,D)*/
void DrawRegions(castle & C);

/*A function to draw the castle and the towers*/
void DrawCastle(castle & C,int SimulationTime);

/*A function to draw a single enemy using its distance from the castle*/
void DrawEnemy(enemey *& E, int Ypos=0);

/*A function to draw a list of enemies exist in all regions and ensure there is no overflow in the drawing*/
void DrawEnemies(enemey* enemies[],int size);

/*Student use this function to print his/her message*/
void PrintMsg(char*msg);
