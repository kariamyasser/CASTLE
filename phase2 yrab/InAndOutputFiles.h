#include "Drawing.h"
#include <fstream>
//funcion loads the file and enters all the data 
void loadfile(queue &un,tower &l,constant &c,castle &g);
//function output the required data in a fil
void output_file(castle g, enemey *killed,tower tower);
//function print the statistics of the fight every timestep
void print(castle g,counter kill,counter alive, int killedno, int x);
//function gives all the required initialization for every adstract data type
void initialize(castle &game,tower t,counter &alive);
