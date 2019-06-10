#include"queue.h"
//function to assign the priority for the enemies
void assignpir(enemey *&e,constant c);
//function takes the activated enemies and put it in its place
void activate(queue &unactive,castle &game,constant c,int timestep,int &breakingpoint);
//function takes the type 0 and make them pave
void pave(tower &t);
//function moves all enemies 
void motion(tower&tower,constant c);
//function makes the tower attacks  the required enemies ALSO makes the enemies attacks the tower
void attack(tower &tower,int timestep,castle &g);
//function move the list of dead tower to the forward alive tower
void movereg(castle &game,char region,queue &inactive);
//checking fucntion if all towers are dead
bool check_of_lose(castle g);
//fucntion count the enemies at each region
void countreg(enemey*head,counter &kill);
//function takes the castle and call Sort ,MOTION ,PAVE,ATTACK,REMOVEKILLED,MOVEREG for all towers
void statistics(castle &game,int timestep,constant c,enemey *&killed,queue &unactive);