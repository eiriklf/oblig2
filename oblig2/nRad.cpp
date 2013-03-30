#include "nRad.h"
#include <iostream>
using namespace std;

nRad::nRad(vector<vector<int> > brettet, int kolonne,int rad, bool opp,bool tre):brett(brettet),motstander(opp),trerad(tre)
{
hode=new node(kolonne,rad);
}
bool nRad::end(int lengde, vector<vector<int> > pseudo)
{
if(win(1,lengde,pseudo)||win(2,lengde,pseudo)||tie(lengde,pseudo))
return true;
else return false;


}
std::vector<std::vector <int> > nRad::getBrett()
{

return brett;

}

void nRad::calculate()
{

vector<vector<int> > pseudo=brett;
peker=hode;
int brikke=2;
cout<<endl;
//traverserer gjennom nodene for å finne det beste trekket
if(motstander==false)//jeg kunne funnet på noe annet her enn å nærmest kopiere 2 rutiner, men dette er den mest effektive måten jeg kommer på.
{	brikke=1;
	node* nextmove=NULL;
	calculateaction(pseudo, false,0);

	for(int i=0; i<(*hode).noder.size(); i++)
	{
		if((*hode).noder[i].stat==3)
		{		
			if(nextmove!=NULL)
				brett[(*nextmove).kolonne][(*nextmove).rad]=0;

			brett[(*hode).noder[i].kolonne][(*hode).noder[i].rad]=brikke;
			nextmove=&(*hode).noder[i];
			break;
		}
		else if((*hode).noder[i].stat==2)
		{
			brett[(*hode).noder[i].kolonne][(*hode).noder[i].rad]=brikke;
			if(nextmove!=NULL)
				brett[(*nextmove).kolonne][(*nextmove).rad]=0;

			nextmove=&(*hode).noder[i];


		}
		else if(nextmove==NULL)
		{
			
				brett[(*hode).noder[i].kolonne][(*hode).noder[i].rad]=brikke;
				nextmove=&(*hode).noder[i];
			


		}

	}
}
else 
{

node* nextmove=NULL;
calculateaction(pseudo, true,0);

	for(int i=0; i<(*hode).noder.size(); i++)
	{
		if((*hode).noder[i].stat==1)
		{
			if(nextmove!=NULL)
				brett[(*nextmove).kolonne][(*nextmove).rad]=0;
		
			brett[(*hode).noder[i].kolonne][(*hode).noder[i].rad]=brikke;
			nextmove=&(*hode).noder[i];
			break;
		}
		else if((*hode).noder[i].stat==2)
		{
			brett[(*hode).noder[i].kolonne][(*hode).noder[i].rad]=brikke;
			if(nextmove!=NULL)
				brett[(*nextmove).kolonne][(*nextmove).rad]=0;
			nextmove=&(*hode).noder[i];

		}
		else if(nextmove==NULL)
		{

		brett[(*hode).noder[i].kolonne][(*hode).noder[i].rad]=brikke;
		nextmove=&(*hode).noder[i];

		}

	}


}



}


//let igjennom treet etter det trekket som har flest antall muligheter for å vinne
//spill ut alle trekk i "moves" turer
//å vinne eller uavgjort er motivet for at ethvert trekk en spiller gjør
//win har førsteplass
//uavgjort har andreplass (fork for en motstander gir automatisk win)
//forutse flere trekk framover ved å anta at motstanderen spiller ut trekkene sine for å vinne
//man kan også anta at for å vinne, så er hver av spillerne nødt til å spille sitt trekk slik at motstanderen ikke får en uomtvistelig vei til seier


void nRad::calculateaction(vector<vector<int> >& pseudo, bool opponent, int depth)
{

node* present=peker;
			
				if(win(!(opponent)+1,pseudo.size(),pseudo))//sjekker om det siste "pseudotrekket" har ført til "win"
				{
			
				if(opponent)
				{(*peker).stat=3;//spiller 1 vinner
				return ;}
				else{
				(*peker).stat=1;//spiller 2 vinner
				return;
				}
				}
				
				
				if(trerad)
				{
				if(tie(pseudo.size(),pseudo))
				{
				(*peker).stat=2;
				return;
				}
				
				}
				else if(tie(pseudo.size(),pseudo)||depth>=4)//dersom dybden er større eller lik 4, kan man si det er uavgjort. for npå rad er det tilstrekkelig å kunne beregne 4 trekk framover for å ikke tape
				{
				(*peker).stat=2;
				return;
				}

				
				

				
for(int i=0; i<pseudo.size(); i++)
	{
		for(int j=0; j<pseudo.size(); j++)
		{//motstander velger det trekket som er mest fordelaktig
		//kopier pseudovektoren inn i en ny vektor for fork. Fordi pseudovektoren ligger i 
		if(pseudo[i][j]==0)
			{
			
			
				pseudo[i][j]=((int)opponent)+1;
				node* noden=new node(i,j);
				(*present).noder.push_back(*noden);
			
				peker=&(*present).noder.back();//flytter pekeren til (denen)siste noden
				
				//fork() , virker ikke i windows
				
				calculateaction(pseudo,!(opponent),depth+1);
				peker=&(*present).noder.back();//flytter pekeren tilbake til den siste noden
								pseudo[i][j]=0;
				if(opponent==true)//brukes til å avgjøre hvilket trekk som er mest fordellaktig på en bestemt tur
				{
				
				if((*peker).stat==1)
				{
				(*present).stat=1;
			
				return;
				
				}
				if((*peker).stat==2)
				{
				(*present).stat=2;
			
					if(!(trerad))/*for 1 av spillerne er det tilstrekkelig å få uavgjort så lenge den andre spilleren prøver å vinne. Dersom en av spillerne spiller perfekt for å vinne,
					kan ikke den andre spilleren vinne men bare få uavgjort. Det samme gjelder for sjakk (jeg har tenkt ut dette helt på egenhånd)*/
						return;
				}
				else if((*present).stat!=2)//sjekker om det ikke ligger noe "lavere" enn 3 der
				{
				(*present).stat=3;

				}
				}
			else
				{
				
				if((*peker).stat==3)
				{
				(*present).stat=3;
				
				return;
				
				}
				if((*peker).stat==2)//for spillerens valg er det ikke 
				{
				(*present).stat=2;
					
				}
				else if((*present).stat!=2)
				{
				(*present).stat=1;
				}
				
				}
		
				
			}
		
		
		}

	
	}
/* //under her er en del historikk som er kommentert ut
				(*present).stat=5;
				for(int k=0; k<((*present).noder).size();k++)
				{
				if(opponent==true)
				{
				
				if((*present).noder[k].stat==1)
				{
				(*present).stat=1;
				return 0;
				
				}
				if((*present).noder[k].stat==2)
				(*present).stat=2;
				if((*present).noder[k].stat==3&&(*present).stat!=2)
				(*present).stat=3;
				}
				if(opponent==false)
				{
				
				if((*present).noder[k].stat==3)
				{
				(*present).stat=3;
				return 0;
				
				}
				if((*present).noder[k].stat==2)
				(*present).stat=2;
				if((*present).noder[k].stat==1&&(*present).stat!=2)
				(*present).stat=1;
				}
				}*/
	/*			if(present!=hode)
				{
	for(int k=0; k<((*present).noder).size();k++)
				{
				if(((*present).noder[k]).stat==1)
				{
				if(opponent==false)
				{
				if((tempstat==3||(same>=((*present).noder).size()-1)&&tempstat==1)||((*present).noder).size()==1)
				{
				cout<<"happen"<<endl;
				(*present).stat=1;
				break;
				}
				else if(same>0&&tempstat!=1)
				{
				
				same=1;
				tempstat=1;
				//cout<<"ii"<<endl;
				}
				else{same++; tempstat=1;}
				}else
				{
				 if(((same>=((*present).noder).size()-1)&&tempstat==1)||((*present).noder).size()==1)
				 {
				cout<<"omhn"<<depth<<(*present).noder.size()<<endl;
				(*present).stat=1;
				break;
				 
				 }
				 else if(tempstat==3)
				 {
				( *present).stat=1;
				 
				 }
				 
				if(same>0&&tempstat!=1)
				{
				
				same=1;
				tempstat=1;
				//cout<<"ii"<<endl;
				}
				else{same++; tempstat=1;}
				
				
				}
				
				}
				
				else if(((*present).noder[k]).stat==3)
				{
			if(opponent==true)
			{
						if(((same>=((*present).noder).size()-1)&&tempstat==3)||(tempstat==1)||(*present).noder.size()==1)
				{
				cout<<"adsasd"<<endl;
				(*present).stat=3;
				break;
				}
				
					if(same>0&&tempstat!=3)
				{
				same=1;
				tempstat=3;
				}
				else
				{
				same++;
			tempstat=3;
				
				}
				}else
				{
				if(((same>=((*present).noder).size()-1)&&tempstat==3)||(*present).noder.size()==1)
				 {
				cout<<"omsdfsdfn"<<endl;
				(*present).stat=1;
				break;
				 
				 }
				 else if(tempstat==1)
				 {
				 (*present).stat=3	;
				break;
				 }
				 
				 
				 
				if(same>0&&tempstat!=3)
				{
				
				same=1;
				tempstat=3;
				//cout<<"ii"<<endl;
				}
				else{same++; tempstat=3;}
				
				}
				}
				
				}
				
				
				if((*present).stat==5)
				{cout<<"omg"<<endl;
				(*present).stat=2;
			/*	for(int k=0; k<((*present).noder).size();k++)
				{
				if(tempstat==1&&opponent==false)
				{
				(*present).stat=3;
				}
				else if(tempstat==3&&opponent==true)
				(*present).stat=1;
				}//
				
				}
				}*/

	return;

}
bool nRad::tie( int lengde, vector<vector<int> > pseudo)
{
for(int i=0; i<lengde; i++)
{
for(int j=0; j<lengde; j++)
{
if(pseudo[i][j]==0)
return false;
}
}

if(!(win(1,lengde,pseudo))||!(win(2,lengde,pseudo)))
return true;
else return false;

}
bool nRad::win(int farge, int lengde, vector<vector <int> > pseudo)
{

for(int i=0; i<lengde; i++)
{
for(int j=0; j<lengde; j++)
{
	if(pseudo[j][i]!=farge)
		break;
	
	if(pseudo[j][i]==farge&&(j+1)==lengde)
		return true;
}
}
for(int i=0; i<lengde; i++)
{
for(int j=0; j<lengde; j++)
{
	if(pseudo[i][j]!=farge)
		break;
	if(pseudo[i][j]==farge&&(j+1)==lengde)
		return true;
		
	}
	

}

for(int i=0; i<lengde; i++)
{
	
		
			if(pseudo[i][i]!=farge)
			break;
			if(pseudo[i][i]==farge&&(i+1)==lengde)
			return true;
		
	
	

}
int j=lengde-1;
for(int i=0; i<lengde; i++)
{

if(pseudo[i][j]!=farge)
			break;
if((pseudo[i][j]==farge)&&((i+1)==lengde))
			return true;		

j--;
}

return false;
}

