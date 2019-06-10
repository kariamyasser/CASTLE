
#include <fstream>
#include <string>
#include<cstdlib>
#include <ctime>
#include<iostream>
#include <chrono>
#include <thread>
using namespace std;
#include "Simulate.h"
#include <windows.h>




void main()
{
	cout<<"CHOOSE MODE : "<<endl<< endl;
	cout<<"1 - INTERACTIVE MODE "<<endl<<"2 - STEP BY STEP "<<endl<<"3 - SILENT MODE"<<endl;
	introsound();
	int x;
	cin>>x;
	if(x==1)
	{interactivemode();}
	if(x==2)
	{stepbystep();}
	if(x==3)
	{silentmode();}
	finalsound();
	Sleep(100);
int team20;cin>>team20;
}


