#include"FightLogic.h"
void assignpir(enemey *&e,constant c)
{
	if (e==NULL) return;
	if (e->type==2)
	{
		e->remtime=(e->reloadperiod-e->ammo)%e->reloadperiod;
		e->priority = (e->firepower / (e->distance) ) * c.c1 + c.c2 / (e->remtime + 1) + e->health * c.c3;
	}
	else
	{
		e->priority=0;
	}
}
void activate(queue &unactive,castle &game,constant c,int timestep,int &breakingpoint) //activation function is called at every time step
{
	enemey*added=NULL;
	if (isempty(unactive)==false)
	{
	while (unactive.front->arriv_time==timestep)
			{
				deque(unactive,added);
			added->distance=60;
			game.count++;
			added->shot=false;
			added->ammo=0;
			assignpir(added,c);

				if (added->region=='a')
		{
			insertatend(game.tower[0].active,added);
			
		}
				else if (added->region=='b')
				{
					insertatend(game.tower[1].active,added);
				}
				else if (added->region=='c')
				{
					insertatend(game.tower[2].active,added);
				}
				else 
				{
					insertatend(game.tower[3].active,added);
				}
		if (isempty(unactive)==true)
		{
			breakingpoint=added->id;
			break;
		}
	}
}
}
void pave(tower &t) // paves the distance to the castle when a paver has reloaded his weapon and moves the paver
{     
     enemey *ptr=t.active;//takes an enemey of type 0 and its tower 
	while (ptr!=NULL)
	{
		
			if(ptr->type!=0)
			{
				ptr=ptr->next;
				continue;
			}
			if (ptr->ammo==0)
			{

				ptr->distance = ptr->distance - ptr->firepower;
				ptr->ammo=(ptr->ammo+1)%(ptr->reloadperiod);

				if (ptr->distance < t.unpaveddis)
				{
					t.unpaveddis = ptr->distance;
				}

				if (ptr->distance < 2)
				{ 
					ptr->distance = 2;
					t.unpaveddis = 2;
				}
			
				}
			ptr=ptr->next;
}
}
void motion(tower&tower,constant c)
{
	enemey*ptr=tower.active;
	while (ptr!=NULL)
	{
		if (ptr->type==2 || ptr->type==1 || ptr->type==3|| ptr->type==4)  // motion of enemies except type 0
		{
			//motion of both typ 1,2
		if (ptr->distance > (tower.unpaveddis+ptr->speed))
			{
				ptr->distance=ptr->distance-ptr->speed;
						
			}
		else
		{
			ptr->distance=tower.unpaveddis;

		}
			assignpir(ptr,c);
		}
		if(ptr->type==0 && ptr->ammo!=0) //motion of type 0
		{
			if (ptr->distance > (tower.unpaveddis+ptr->speed))
			{
				ptr->distance=ptr->distance-ptr->speed;

			}
			else
		{
			ptr->distance=tower.unpaveddis;

		}
			ptr->ammo=(ptr->ammo+1)%(ptr->reloadperiod);//circulation of ammo 
		}
		ptr=ptr->next;
	}
}
void attack(tower &tower,int timestep,castle &g) //attack of enemies to the tower
{

	enemey*ptr=tower.active;
	int cap=tower.capacity;
	if (ptr==NULL) return;	
	while (ptr!=NULL)
	{
		if (ptr->type==2 || ptr->type==1 || ptr->type==3)  // attacking of enemies except type 0,4
		{
		if (ptr->ammo==0)
		{
			if (ptr->type==2)
			{
		    	tower.health=tower.health-2*(ptr->firepower)/(ptr->distance); // attack of enemey of type 2 on tower
			}
			else //ptr is type 1,3 
			{
					tower.health=tower.health-1*ptr->firepower/ptr->distance; //attack of type 1 on tower
			}
			ptr->ammo=(ptr->ammo+1)%(ptr->reloadperiod);//circulation of ammo for both (at ammo=0)
		}
		else //their ammo not=0 (not time to shoot)
		{
			ptr->ammo=(ptr->ammo+1)%(ptr->reloadperiod);

		}
		//at the end of (type1,2) we move both of them and attack both of them by the tower
		if (cap!=0)
		{
			if (ptr->type==2)
			{
				if (ptr->shot==false) // to get tfirst shot and fight delay
				{
				ptr->shot=true;
				ptr->fshot=timestep;
				ptr->fd=ptr->fshot-ptr->arriv_time;
				}
				ptr->health=ptr->health-(1/ptr->distance)*(tower.firepower/2); //attack of tower on type 2
     			cap--;
			}
			if(ptr->type==1)
			{
				if (ptr->shot==false) // getting the tfirst and the fight delay 
					{
		            ptr->shot=true;
		            ptr->fshot=timestep;
		         	ptr->fd=ptr->fshot-ptr->arriv_time;
					}
		ptr->health=ptr->health-(1/ptr->distance)*(tower.firepower/1); //attack of tower to type 1
		cap--;
			}
		}
		}
	
		
	 if (ptr->type==0 || ptr->type==4 )   //not type 1,2,3  ptr is type 0,4
		{
			if (cap!=0)
			{
				if (ptr->shot==false) // getting the tfirst and the fight delay 
					{
		            ptr->shot=true;
		            ptr->fshot=timestep;
		         	ptr->fd=ptr->fshot-ptr->arriv_time;
					}
					ptr->health=ptr->health-(1/ptr->distance)*(tower.firepower/1); //attack of tower to type 0
					cap--;
			}
		}
		
	 if (tower.health<=0)
		{
			tower.health=0;
		
		}
	 
	 if(ptr->type==3)
	{
		ptr->shot=false;
		ptr->fshot=0;
		ptr->fd=0;
	
		if (tower.health<=0)
		{
			tower.health=0;
			ptr->health=0;
		}
	 }
	if(ptr->type==4 && ptr->distance==2)
		{
			tower.health=0;
		}
	 if (ptr->health<=0)
		{	
			g.count--;
			ptr->health=0;
	
	
			if(ptr->type ==3)
		{
			ptr->kd=0;
		}
		else
		{
		ptr->kd=timestep-ptr->fshot;
		}
		ptr->ft=timestep-ptr->arriv_time;
		ptr->kts=timestep;
		
		tower.presentkill++;
		
		}
		ptr=ptr->next;

		
		}
	
}
void movereg(castle &game,char region,queue &inactive)
{

     int reg=region-97; 
     int newreg=reg;
     int i=0;
	 if (game.tower[reg].health!=0)
		return;
//region-65 for capital letters;
while(game.tower[newreg].health==0 && i<4) //finding the next alive tower to move enemies to
{
     newreg=(reg+i+1)%4;
     i++;
     }
     if (i==4)
     return; // game is loss
	 enemey *ptr=inactive.front;
                while(ptr!=NULL)   //move inactive from killed tower to new region
                {
                if(ptr->region==(reg+97))
                ptr->region=(newreg+97);
                ptr=ptr->next;
                }
				if(game.tower[newreg].active==NULL || game.tower[newreg].active->next==NULL) //moving to an empty tower enemies or just one enemy
				{
				if(game.tower[newreg].active!=NULL)
				{
					if (game.tower[newreg].active->arriv_time<=game.tower[reg].active->arriv_time)
					{insb(game.tower[newreg].active,game.tower[reg].active);}
				
				else if (game.tower[newreg].active->arriv_time>game.tower[reg].active->arriv_time && game.tower[reg].active->next!=NULL)
				{	inse(game.tower[newreg].active,game.tower[reg].active);}
				else 
				{insf(game.tower[newreg].active,game.tower[reg].active);}
				
				}
					game.tower[newreg].active=game.tower[reg].active;
					while(game.tower[reg].active!=NULL)                      //changing region for active enemies
					{
						game.tower[reg].active->region=(newreg+97);
                                            if(game.tower[reg].active->distance < game.tower[newreg].unpaveddis) // handling unpaved distance
                                          { 
											 game.tower[reg].active->distance=game.tower[newreg].unpaveddis;
											}
											game.tower[reg].active=game.tower[reg].active->next;

					}
					game.tower[reg].active=NULL;
					return;

				}				

	 
     while(game.tower[reg].active!=NULL)  // moving to non-empty tower enemies
     {
		  game.tower[reg].active->region=(newreg+97);
                                            if(game.tower[reg].active->distance < game.tower[newreg].unpaveddis)
                                          { 
											 game.tower[reg].active->distance=game.tower[newreg].unpaveddis;
											}
		 insert_sorted(game.tower[newreg].active,game.tower[reg].active);  // insert enemies sorted according to their arrival time
					
	 }
	 
}
bool check_of_lose(castle g)
{
	if(g.tower[3].health==0 && g.tower[2].health==0 && g.tower[1].health==0 && g.tower[0].health==0)
	{return true;}
	else 
	{
		return false;
	}
}
void countreg(enemey*head,counter &kill)
{
	enemey*ptr=head;
	kill.a=0;
	kill.b=0;
	kill.c=0;
	kill.d=0;
	while(ptr!=NULL)
	{
		if('a'==ptr->region)
	{
		kill.a++;
	}
	 else if('b'==ptr->region)
	{
		kill.b++;
	}
	else if('c'==ptr->region)
	{
		kill.c++;
	}
	else if('d'==ptr->region)
	{
		kill.d++;
	}
	ptr=ptr->next;
	}
	
}
void statistics(castle &game,int timestep,constant c,enemey *&killed,queue &unactive)
{
	for(int i=0;i<4;i++)
	{
			Sort(game.tower[i].active);
	game.tower[i].lastkill=game.tower[i].presentkill;
	game.tower[i].presentkill=0;
	motion(game.tower[i],c);
	pave(game.tower[i]);

	attack(game.tower[i],timestep,game);
	delete_add(game.tower[i].active,killed);
	if (game.tower[i].health==0 && game.tower[i].active!=NULL)
		movereg(game,97+i,unactive);
	
	
	}

}