
#include "LinkedList.h"
#pragma once
//implemntations of queue 
struct constant
{
	float c1;
	float c2;
	float c3;
};
struct counter
{
	int a;
	int b;
	int c;
	int d;
};
struct queue
	{
		enemey*front;
enemey*rear;
enemey*next;
};
bool isempty(queue k);
bool enque(queue &k,enemey*p);

bool deque(queue &k,enemey *&p);
void countactive(castle game,counter &k);