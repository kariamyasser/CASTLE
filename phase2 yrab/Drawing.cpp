#include "Drawing.h"
void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}

void SetWindow()
{
	system("mode 150,50");   //Set mode to ensure window does not exceed buffer size
	SMALL_RECT WinRect = {0, 0, CmdWidth, CmdHeight};   //New dimensions for window in 8x12 pixel chars
	SMALL_RECT* WinSize = &WinRect;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   //Set new size for window
}

void color(int thecolor)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdout, 
		thecolor|FOREGROUND_INTENSITY);
}
///////////////////////////////////////////////////////////////////////////////////////

void DrawRegions(castle & C)
{
	color(FOREGROUND_RED|FOREGROUND_BLUE);
	gotoxy(0, C.Ystrt + C.L/2);
	for(int i=0;i<C.W+2*C.Xstrt;i++)
		cout<<"-";
	for(int j=0;j<C.L+2*C.Ystrt;j++)
	{
		gotoxy(C.Xstrt + C.W/2, j);
		cout<<"|";		
	}
	color(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}
void DrawCastle(castle & C,int SimulationTime)
{
	system("CLS");
	
	//Draw the castle
	cout<<endl;
	gotoxy(C.Xstrt,C.Ystrt);
	for(int i=0;i<C.W;i++)
		cout<<"=";
	for(int j=1;j<C.L; j++)
	{
		gotoxy(C.Xstrt, C.Ystrt +j);
		cout<<"|";
		gotoxy(C.Xstrt+C.W-1, C.Ystrt +j);
		cout<<"|";
	}
	gotoxy(C.Xstrt,C.Ystrt+C.L-1);
	for(int i=0;i<C.W;i++)
		cout<<"=";

	//Draw towers
	int T1X,T2X,T3X,T4X,T1Y,T2Y,T3Y,T4Y;
	for (int i=0;i<4;i++)
	{

		if(i==0)
		{
			T1X=C.Xstrt+1;
			T1Y=C.Ystrt + TowerLength;
			gotoxy(T1X, T1Y);
			for(int i=0;i<TowerWidth;i++)
				cout<<"=";
			gotoxy(T1X +1, T1Y-1);
			cout<<"T1"<<"("<<C.tower[0].health<<")";

			gotoxy(C.Xstrt+C.W/4, C.Ystrt+C.L/4);
			cout<<"(A)";
		}
		else if(i==1)
		{
			T2X=C.Xstrt+C.W-2-TowerWidth;
			T2Y=T1Y;
			gotoxy(T2X,T2Y );
			for(int i=0;i<TowerWidth+1;i++)
				cout<<"=";
			gotoxy(T2X +1, T2Y-1);
			cout<<"T2"<<"("<<C.tower[1].health<<")";
			gotoxy(C.Xstrt+(3*C.W/4), C.Ystrt+C.L/4);
			cout<<"(B)";
		}
		else if(i==2)
		{
			T3X=T2X;
			T3Y=C.Ystrt + C.L - TowerLength-1;;
			gotoxy(T3X,T3Y );
			for(int i=0;i<TowerWidth+1;i++)
				cout<<"=";
			gotoxy(T3X +1, T3Y+1);
			cout<<"T3"<<"("<<C.tower[2].health<<")";
			gotoxy(C.Xstrt+(3*C.W/4), C.Ystrt+(3*C.L/4)-1);
			cout<<"(C)";

		}
		else 
		{
			T4X=T1X;
			T4Y=C.Ystrt + C.L - TowerLength-1;
			gotoxy(T4X, T4Y);
			for(int i=0;i<TowerWidth;i++)
				cout<<"=";
			gotoxy(T4X +1, T4Y+1);
			cout<<"T4"<<"("<<C.tower[3].health<<")";
			gotoxy(C.Xstrt+(C.W/4), C.Ystrt+(3*C.L/4)-1);
			cout<<"(D)";

		}
	}


	DrawRegions(C);

	//****************************
	gotoxy(CmdWidth/2 -10, CmdHeight-1);
	cout<<"Simulation Time : " << SimulationTime<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////

/*A function to draw a single enemy using its distance from the castle*/
void DrawEnemy(enemey*& E, int Ypos)
{
	int x,y;
	//First calcuale x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	char Enemyregion = E->region;
	switch (Enemyregion)
	{
	case 'a':
		x = (int)(CastleXStrt-E->distance+1);
		y = (CmdHeight/2)-(CastleLength/4)-Ypos;
		break;
	case 'b':
		x = (int)(CastleXStrt+CastleWidth+E->distance-1);
		y = (CmdHeight/2)-(CastleLength/4)-Ypos;
		break;
	case 'c':
		x = (int)(CastleXStrt+CastleWidth+E->distance-1);
		y = (CmdHeight/2)+(CastleLength/4)+Ypos;
		break;
	default:
		x= (int)(CastleXStrt-E->distance+1);
		y= (CmdHeight/2)+(CastleLength/4)+Ypos;

	}

	gotoxy(x, y);

	//set enemy color according to it type
	int Enemytype = E->type;
	switch(Enemytype)
	{
	case 0:
		color(FOREGROUND_GREEN);
		break;
	case 1:
		color(FOREGROUND_RED|FOREGROUND_GREEN);//Yellow
		break;
		case 3:
		color(FOREGROUND_BLUE);//Blue
		break;
		case 4:
		color(FOREGROUND_RED|FOREGROUND_BLUE);
		break;
	default:
		color(FOREGROUND_RED);
	}

	
	cout<<(char)EnemyShape; //Draw the enemy

	color(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to draw a list of enemies and ensure there is no overflow in the drawing*/
//To use this function, you must prepare its input parameters as specified
//Input Parameters:
// enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
// size : the size of the array (total no. of enemies)
void DrawEnemies(enemey* enemies[],int size)
{
	//draw enemies at each region 
	for(char region='a';region<='d';region++)
	{
		int CountEnemies =0;	//count Enemies at the same distance to draw them vertically if they are <= 15 enemy else print number of enemy in the region
		bool draw=true;
		for(int distance=((CmdWidth/2)-(CastleWidth/2));distance>1;distance--)
		{
			CountEnemies=0;

			for(int i=0;i<size;i++)
			{	
				if(enemies[i]->distance==distance && enemies[i]->region == region)
				{
					CountEnemies++;
				}
			}
			if(CountEnemies>15)
			{
				draw=false;
				break;
			}

		}
		if(draw)
		{
			for(int distance=((CmdWidth/2)-(CastleWidth/2));distance>1;distance--)
			{
				CountEnemies=0;

				for(int i=0;i<size;i++)
				{	
					if(enemies[i]->distance==distance && enemies[i]->region == region)
					{
						DrawEnemy((enemies[i]),CountEnemies);
						CountEnemies++;
					}
				}
			}


		}
		else // print message maximum reached in this region
		{
			int x;int y;
			if(region=='a')
			{
				x= CastleXStrt-30;
				y= (CmdHeight/2)-(CastleLength/4);
			}
			else if(region=='b')
			{
				x= CastleXStrt+CastleWidth+30;
				y= (CmdHeight/2)-(CastleLength/4);


			}
			else if(region=='c')
			{
				x= CastleXStrt+CastleWidth+30;
				y= (CmdHeight/2)+(CastleLength/4);

			}
			else
			{
				x= CastleXStrt-30;
				y= (CmdHeight/2)+(CastleLength/4);

			}
			gotoxy(x, y);
			cout<<"Maximum limit";
		}

	}
	gotoxy(0, CmdHeight-1);
}
void PrintMsg(char*msg)
{
	cout << msg;
}