/* Eirik Flogard, s169963*/
#include "nRadAction.h"
using namespace std;

void nRadAction::printState()
{

for(int i=0; i<brett.size(); i++)
{
for(int j=0; j<brett.size();j++)
{

cout<<brett[i][j];

}
cout<<endl;
}


}

int nRadAction::getAction()
{
  char buffer[256];
  fgets (buffer, 256, stdin);

return atoi(buffer);

}


void nRadAction::takeAction()
{

printState();
while(true)
{
	cout<<"Skriv inn kolonne "<<endl;
	kolonne=getAction();
	cout<<"skriv inn rad"<<endl;
	rad=getAction();
	if(brett[kolonne][rad]==0)
	{
		brett[kolonne][rad]=1;
		break;
	}
	else
		cout<<"ugyldig plassering"<<endl;
}

}
bool player1starts()
{srand ( time(NULL) );
return (rand()%2);


}
void nRadAction::computer(bool trep, int st2)
{ bool mostander=true;

	nRad* n=new nRad(brett,kolonne,rad,true,trep);

	while(!(*n).end(brett.size(),brett))
	{	
		
			
			delete(n);
			n=new nRad(brett,kolonne,rad,mostander,trep);
			(*n).calculate();
			brett=(*n).getBrett();
		printState();
		mostander=!(mostander);
		//sleep(1);// (anse denne funksjonen for å være med i obligen, jeg får ikke kompilert unistdfunksjoner med denne kompilatoren. Både fork og sleep finnes ikke i windows)
	}


}
void nRadAction::game()
{
	bool trep=false;
	vector <int> v;	
	char buffer[256];
	cout<<"skriv inn storrelse paa brett"<<endl;
	cout<<"storrelsen skal vaere et tall som er storre enn 2"<<endl;

	fgets (buffer, 256, stdin);
	int st=atoi(buffer);
	if(st<3)
		return;
	if(st==3)
		trep=true;
	v.assign(st,0);
	for(int i=0; i<st; i++)
	{
		brett.assign(st,v);
	}
	
	cout<<"spill ai mot ai?, 0=nei, 1=ja"<<endl;
	char input[256];//må opprette en ny array, for å slippe å cleare det andre. Jeg ønsker her å beholde datastrukturen som et aggregat og slippe å bruke en kompositt type
	fgets (input, 256, stdin);
	int st2=atoi(input);//ligger i stdlib
	bool p1start=player1starts();//avgjør om spiller er spiller 1
	if(st2==1)//spill ai mot ai
		computer(trep,st2);/*ingen return etter kallet, fordi brettet er fullt vil whileløkken bli false. Og programmet vil gå rett til utskriften som viser hvem som vinner.
		resultatet av ai mot ai vil alltid bli "tie", fordi aien ikke kan tape*/
	else//spill menneske mot maskin
	{
	if(p1start)
	cout<<"you are player 1"<<endl;
	else
	cout<<"you are player 2"<<endl;
	}
	nRad* n=new nRad(brett,kolonne,rad,true,trep);//gjør ingenting, men new må kalles før delete.
	while(!(*n).end(st,brett))
	{	
		if(p1start)//spiller begynner
		{
			
			delete(n);
			takeAction();
			n=new nRad(brett,kolonne,rad,true,trep);
			(*n).calculate();
			brett=(*n).getBrett();
		}
		else//computer begynner
		{
		
			delete(n);
			n=new nRad(brett,kolonne,rad,true,trep);
			(*n).calculate();
			brett=(*n).getBrett();
			if(!(*n).end(st,brett))
				takeAction();
		}

	
	}
		
		if(st2!=1)
			printState();
	if((*n).win(1,brett.size(),brett))
	cout<<"player 1 wins"<<endl;
	else if ((*n).win(2,brett.size(),brett))
	cout<<"player 2 wins"<<endl;
	else cout<<"tie"<<endl;
}
int main()
{
nRadAction n;
n.game();

}
