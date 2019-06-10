#include "StructEnemey.h"
#pragma once
//function insert the first element of head at begin of head2 and moves head to the next index
void insb(enemey *&head, enemey*&head2);
//function insert the first element of head at end of head2 and moves head to the next index
void inse(enemey *&head, enemey *&head2);
//function the element of head in head at its place according to its timestep
void insf(enemey *&head,enemey *&head2);
//function insert a block of pointer enemey and include it at the end in the of the list
bool insertatend(enemey*&active,enemey *p);
//function insert the enemey e sorted according to its timestep
void insert_sorted(enemey*&e ,enemey*&head);
//function counts the number of elements in a list
int count(enemey *head);
//function puts the enemies in an array of enemies 
void array_of_enemies(castle g ,enemey **&elist);
//function takes two lists and delete the enemy of health=0 from its list and add it to the killed list
void delete_add(enemey *&head1,enemey *&head2);
//function delete all the enemies in a list 
void DestoryList(enemey*&head);
//function delete all the enemies of the lists of the castle after the game is ended
void Destroycastle(castle&g);
//function delete a dynamic array of pointers of enemies 
void Destroyenemies(enemey**&enemies);
//function sorts a list of enemies according to the priority 
void Sort(enemey *& pList);
//function sorts a list of enemies according to the fightdelay
void Sortfd(enemey *& pList);//sorting function 