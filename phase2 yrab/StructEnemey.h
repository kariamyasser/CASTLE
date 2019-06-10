#include <iostream>
using namespace std;

#include <windows.h>


struct enemey
{
	int id;
	float health;
		char region;
		int type;
		float firepower;
		int arriv_time;
		int reloadperiod;
		int ammo;
		int remtime;
		bool shot;
		int fshot;
		int fd;
		int ft;
		int kd;
		float distance;
		enemey*next;
		float priority;
		int loc;
		int kts;
		int speed;
};

struct tower
{
	int capacity;
	int firepower;
	float unpaveddis;
	int tw;
	int tl;
	int count;
float health;
tower*next;
enemey*active;
int lastkill;
		int presentkill;

};
struct castle
{
	//starting x,y
	int Xstrt;
	int Ystrt;
	int W;	//width
	int L;  //Height
	tower tower[4];
	int count;
	int full;
};



