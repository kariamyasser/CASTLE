#include "InAndOutputFiles.h"

void loadfile(queue &un,tower &l,constant &c,castle &g)  //load function saves the enemies in a queue and the tower and constant are bypassed my reference
{
	ifstream myfile("game.txt");
myfile>>l.health;
myfile>>l.capacity;
l.unpaveddis=30;
l.presentkill=0;
l.lastkill=0;
myfile>>l.firepower;
myfile>>c.c1;
myfile>>c.c2;
myfile>>c.c3;

	
		enemey *ptr=new enemey;
	myfile>>ptr->id;
	while (ptr->id!=-1)
	{
		if (ptr->id==-1)  //exit operation when all enemies are saved in the queue
			break;
		g.full++;
	myfile>>ptr->type;
		myfile>>ptr->arriv_time;
 		myfile>>ptr->health;
		myfile>>ptr->firepower;
		myfile>>ptr->reloadperiod;
		myfile>>ptr->region;
		myfile>>ptr->speed;
		enque(un,ptr);
		ptr=new enemey;
		myfile>>ptr->id;
		
}
}
void output_file(castle g, enemey *killed,tower tower)
{
	fstream out;
	out.open("output.txt",ios::out); 
	if (killed!=NULL)
	out<<"KTS    "<<"S    "<<"FD    "<<"KD    "<<"FT    "<<endl;
	int i=1;
	float tfd=0; 
	float tkd=0;
	while(killed!=NULL)
	{
		out<<killed->kts<<"     "<<i<<"     "<<killed->fd<<"     "<<killed->kd<<"     "<<killed->ft<<endl;
		
		tfd=tfd+killed->fd;
		tkd=tkd+killed->kd;
		i++;
		killed=killed->next;
	}
	out<<"T1_Total_Damage     "<<"T2_Total_Damage     "<<"T3_Total_Damage    "<<"T4_Total_Damage    "<<endl;    
	for(int j=0;j<4;j++)
		{
			out<<tower.health - g.tower[j].health<<"               ";
		}
	out<<endl;
	out<<"R1_Distance      "<<"R1_Distance      "<<"R1_Distance     "<<"R1_Distance     "<<endl;    
	for(int j=0;j<4;j++)
		{
			out<<g.tower[j].unpaveddis<<"               ";
		}
	out<<endl;
	if(check_of_lose(g)==true)
	{
	out<<"Game is LOSS"<<endl;
	out<<"Number of killed Enemies 		= "<<i-1<<endl;
	out<<"Number of alive active        = "<<g.count<<endl;
	out<<"Number of alive inactive        = "<<g.full-g.count-i+1<<endl;

	out<<"Average Fight Delay	= "<<tfd<<endl;
	out<<"Average Kill Delay  	= "<<tkd<<endl;
	
	}
	else
	{
	out<<"Game is WIN"<<endl;
	out<<"Total Enemies 		= "<<i-1<<endl; //add g.totale in struct tower && initialize in initialize func & increment after 
	out<<"Average Fight Delay	= "<<tfd/(i-1)<<endl;
	out<<"Average Kill Delay  	= "<<tkd/(i-1)<<endl;
	}
}
void print(castle g,counter kill,counter alive,int killedno , int breakingpoint)
{
	cout<<"Total current enemies:   A="<<alive.a<<"    B="<<alive.b<<"    C="<<alive.c<<"   D="<<alive.d<<endl;   
	cout<<"Last time step kill:     A="<<g.tower[0].lastkill<<"    B="<<g.tower[1].lastkill<<"    C="<<g.tower[2].lastkill<<"   D="<<g.tower[3].lastkill<<endl;   
	cout<<"Total killed enemies:    A="<<kill.a<<"    B="<<kill.b<<"    C="<<kill.c<<"   D="<<kill.d<<endl;   
	cout<<"Unpaved distance:        A="<<g.tower[0].unpaveddis<<"    B="<<g.tower[1].unpaveddis<<"    c="<<g.tower[2].unpaveddis<<"   D="<<g.tower[3].unpaveddis<<endl; 
	if(g.tower[0].health==0 && g.tower[1].health==0 && g.tower[2].health==0 &&g.tower[3].health==0)
	{
		cout<<"Game is Loss";
	}
	else if(killedno==breakingpoint)
	{
		cout<<"Game is Win";
	}
}
void initialize(castle &game,tower t,counter &alive)
{
	
	alive.a=0;
	alive.b=0;
	alive.c=0;
	alive.d=0;
	game.tower[0]=t;
	game.tower[1]=t;
	game.tower[2]=t;
	game.tower[3]=t;
	game.count=0;
	game.tower[0].active=NULL;
	game.tower[1].active=NULL;
	game.tower[2].active=NULL;
	game.tower[3].active=NULL;

}
