/* Eirik Flogard, s169963*/
#ifndef CLASS_NRADACTION_H
#define CLASS_NRADACTION_H
//#include "nRad_node.h"
#define _POSIX_SOURCE
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "nRad.h"
#include <time.h>
#include <sys/types.h>
#include <windows.h>

class nRadAction
{
std::vector <std::vector<int> > brett;
void printState();//skriver ut state
int rad;//peker på den siste raden som er lagt
int kolonne;//peker på den siste kolonnen som er lagt
int getAction();//henter input fra spiller
void takeAction();//behandler input fra spiller
void computer(bool trep, int st);//spiller ai mot ai
public:
void game();


};

#endif