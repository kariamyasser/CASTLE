#include "Simulate.h"


void introsound()
{
	           Beep(659, 125);
           Beep(659, 125);
            Sleep(125);
           Beep(659, 125);
            Sleep(167);
           Beep(523, 125);
           Beep(659, 125);
            Sleep(125);
           Beep(784, 125);
            Sleep(375);
           Beep(392, 125);
            Sleep(375);

}
void finalsound()
{
	Beep(369,800);
	Beep(392,150);
	Beep(349,150);
	Beep(329,150);
	Beep(261,150);
	Beep(246,150);
	Beep(261,150);
	Beep(261,900);


}

void interactivemode()
{
	queue unactive;
	unactive.front=NULL;
	unactive.rear=NULL;
	enemey*killedkts;
	killedkts=NULL;
	castle game;
	enemey*killed;
	killed=NULL;
	constant c;
	tower t;
	game.full=0;
	counter alive;//counts for active elements
		counter kill; // counts for killed enemies
	loadfile(unactive,t,c,game);
	initialize(game,t,alive);
	
	
	int timestep=1;
	int breakingpoint=-1;
	bool x=true;
	enemey *added=NULL;
	
	cin.get();
	Beep (400,100);Sleep(125);
	while (x=true)
	{
		
		activate(unactive,game,c,timestep,breakingpoint);
		/*DrawCastle(game,timestep);
		array_of_enemies(game ,elist);
		DrawEnemies(elist,game.count);*/
		enemey**enemies=new enemey*[150];
		statistics(game,timestep,c,killedkts,unactive);
		Sortfd(killedkts);
		delete_add(killedkts,killed);
		countreg(killed,kill);
		countactive(game,alive);
		SetWindow();	//adjust game window settings

	 


	game.Xstrt = CastleXStrt;
	game.Ystrt = CastleYStrt;
	game.W = CastleWidth;
	game.L = CastleLength;
		//[1],[2],[3] Clear the screen, Draw the castle, Draw the regions
	DrawCastle(game,timestep);
	array_of_enemies(game,enemies);
	//[4] Draw enemies
	int p,l,m,n;// counters of active elements each region ,p counts of region a,l counts the region b,m counts the region c,n counts the region d
	p=count(game.tower[0].active);
	l=count(game.tower[1].active);
	m=count(game.tower[2].active);
	n=count(game.tower[3].active);
	int totalactive=m+l+n+p;
	DrawEnemies(enemies,totalactive);
		int killedno=count(killed);
		if (killedno==breakingpoint || check_of_lose(game)==true)
			{
				print(game,kill,alive,killedno,breakingpoint);
		output_file(game,killed,t);
	
		DestoryList(killed);
		Destroycastle(game);
			return;
			}
		print(game,kill,alive,killedno,breakingpoint);
		Destroyenemies(enemies);
		cin.get();
		
	timestep++;
	Beep (400,100);Sleep(125);
	}
}

void stepbystep()
{
	queue unactive;
	unactive.front=NULL;
	unactive.rear=NULL;
	
	castle game;
	enemey*killed;
	killed=NULL;
	enemey*killedkts;
	killedkts=NULL;
	constant c;
	tower t;
	game.full=0;
	counter alive; //counts for active elements
		counter kill; // counts for killed enemies
	loadfile(unactive,t,c,game);
	initialize(game,t,alive);
	
	int timestep=1;
	int breakingpoint=-1;
	bool x=true;
	enemey *added=NULL;
	
	Beep (400,100);Sleep(125);
	while (x=true)
	{
		
		activate(unactive,game,c,timestep,breakingpoint);

		enemey**enemies=new enemey*[150];
		statistics(game,timestep,c,killedkts,unactive);
		 Sortfd(killedkts);
		delete_add(killedkts,killed);
		countreg(killed,kill);
		countactive(game,alive);
		SetWindow();	//adjust game window settings

	


	game.Xstrt = CastleXStrt;
	game.Ystrt = CastleYStrt;
	game.W = CastleWidth;
	game.L = CastleLength;
		//[1],[2],[3] Clear the screen, Draw the castle, Draw the regions
	DrawCastle(game,timestep);
	array_of_enemies(game,enemies);
	//[4] Draw enemies
	
	int p,l,m,n;// counters of active elements each region ,p counts of region a,l counts the region b,m counts the region c,n counts the region d
	p=count(game.tower[0].active);
	l=count(game.tower[1].active);
	m=count(game.tower[2].active);
	n=count(game.tower[3].active);
	int totalactive=m+l+n+p;//total no. of active in this timestep;
	DrawEnemies(enemies,totalactive);
		int killedno=count(killed);
		if (killedno==breakingpoint || check_of_lose(game)==true)
			{
				print(game,kill,alive,killedno,breakingpoint);
		output_file(game,killed,t);

		DestoryList(killed);
		Destroycastle(game);
			return;
			}
		print(game,kill,alive,killedno,breakingpoint);
		Destroyenemies(enemies);
		Sleep(100);
		
	timestep++;
	Beep (400,100);Sleep(125);
	}
}
void silentmode()
{
	queue unactive;
	unactive.front=NULL;
	unactive.rear=NULL;
	
	castle game;
	enemey*killed;
	killed=NULL;
	enemey*killedkts;
	killedkts=NULL;
	constant c;
	tower t;
	game.full=0;
	counter alive;//counts for active elements
		
	loadfile(unactive,t,c,game);
	initialize(game,t,alive);
	int timestep=1;
	int breakingpoint=-1;
	bool x=true;
	enemey *added=NULL;
	

	while (x=true)
	{
		
		activate(unactive,game,c,timestep,breakingpoint);
		statistics(game,timestep,c,killedkts,unactive);
		Sortfd(killedkts);
		delete_add(killedkts,killed);
		int killedno=count(killed);
		if (killedno==breakingpoint || check_of_lose(game)==true)
			{
	
		output_file(game,killed,t);

		DestoryList(killed);
		Destroycastle(game);
			return;
			}
		
		
		
	timestep++;

	}
}
