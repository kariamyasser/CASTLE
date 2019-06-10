#include "queue.h"
bool isempty(queue k)
{
	if (k.front==NULL)
	{	return true;
}
	else 
	{return false;}
}
bool enque(queue &k,enemey*p)
{

if (isempty(k)==true)
{
k.front=p;
k.rear=p;
p->next=NULL;
	return true;
}
k.rear->next=p;
k.rear=p;
p->next=NULL;
	return true;

}
bool deque(queue &k,enemey *&p)
{
	if(isempty(k)==true)
		return false;
	p=k.front;
	enemey*d=k.front;
	k.front=d->next;
	if(k.front==NULL)
{		k.rear=NULL;

}
		return true;	
}
void countactive(castle game,counter &k)
{
	for(int i=0;i<4;i++)
	{
		if(i==0)
		{
k.a=count(game.tower[0].active);
		}
		else if(i==1)
		{
			k.b=count(game.tower[1].active);
		}
		else if(i==2)
		{
			k.c=count(game.tower[2].active);
		}
		else
		{
k.d=count(game.tower[3].active);
		}

	}
}

