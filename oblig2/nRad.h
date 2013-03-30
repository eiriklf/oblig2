/* Eirik Flogard, s169963*/
#ifndef CLASS_BLACKJACKGAME_H
#define CLASS_NRAD_H
#include <cstdlib>
#include "nRad_node.h"

class nRad
{
std::vector<std::vector <int> > brett;//inneholder nåværende gamestate
bool trerad;//sørger for å begrense prosesstiden til en brøkdel, dersom spillet er større enn 3 ( innvirkningen er som følger: worst case: 0 ops spart eller 0 forandring, best case: summen av alle bladnoder - dybden for søketreet)
//mest signifikant opperasjon: memory-write
node* hode;//peker på den siste brikken som faktisk er blitt lagt i spillet
node* peker;//peker på den siste noden som er besøkt
public:

nRad(std::vector<std::vector <int> > brettet,int kolonne, int rad, bool opp, bool tre);
void calculate();//kalkulerer et trekk for ai, velger det mest fordelaktige trekket i en gitt gamestate
bool tie(int lengde,std::vector<std::vector <int> > pseudo);//avgjør om det er uavgjort
bool win(int farge, int lengde, std::vector<std::vector <int> > pseudo);//avgjør om en spiller har vunnet (basert på farge)
void calculateaction(std::vector<std::vector<int> >& pseudo,bool opponent,int depth); //avgjør hvilket trekk (av alle lovelige) som er mest fordelaktig
bool end(int lengde, std::vector<std::vector <int> > pseudo);//avgjør om spillet er over
std::vector<std::vector <int> >getBrett();//henter ut trekket til ai
bool motstander;//avgjør hvilken tur/farge ai skal spille
~nRad(){delete(hode);}//mingw godtok ikke at jeg deklarerer i header og implementerer i cpp for destruktor

};


#endif