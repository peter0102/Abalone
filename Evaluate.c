#include <stdio.h>
#include <stdlib.h>
#define ALPHA 3
#define MAX_I 10
#define MAX_J 10
#define CASE_VIDE '0'
#define CASE_NOIRE 'N'
#define CASE_BLANCHE 'B'

typedef char Plateau[MAX_I][MAX_J];


int victory(Plateau p){
	int i=0,v=0;
	for(i=0;i<=8;i++){
		if(p[0][i]==CASE_BLANCHE || p[i][9]==CASE_BLANCHE || p[9][9-i]==CASE_BLANCHE || p[9-i][0]==CASE_BLANCHE){
			v==1;
			break;
		}
	}
	return v;
}

int loss(Plateau p){
	int i=0,l=0;
	for(i=0;i<=8;i++){
		if(p[0][i]==CASE_NOIRE || p[i][9]==CASE_NOIRE || p[9][9-i]==CASE_NOIRE || p[9-i][0]==CASE_NOIRE){
			l==1;
			break;
		}
	}
	return l;
}

int density(Plateau p,char currentPlayer,int alpha){
	int i=0,j=0;
	int t[]={0,0,0,0,0,0,0,0,0};
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			if(p[i][j]==currentPlayer){
				t[0]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=1;j<=3;j++){
			if(p[i][j]==currentPlayer){
				t[1]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=1;j<=3;j++){
			if(p[i][j]==currentPlayer){
				t[2]++;
			}
		}
	}
	for(i=1;i<=3;i++){
		for(j=4;j<=6;j++){
			if(p[i][j]==currentPlayer){
				t[3]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=4;j<=6;j++){
			if(p[i][j]==currentPlayer){
				t[4]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=4;j<=6;j++){
			if(p[i][j]==currentPlayer){
				t[5]++;
			}
		}
	}
	for(i=1;i<=3;i++){
		for(j=6;j<=8;j++){
			if(p[i][j]==currentPlayer){
				t[6]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=6;j<=8;j++){
			if(p[i][j]==currentPlayer){
				t[7]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=6;j<=8;j++){
			if(p[i][j]==currentPlayer){
				t[8]++;
			}
		}
	}
	int max_count=0,most_frequent=0;
	for(i=0;i<9;i++){
		int count=0;
		for(j=0;j<9;j++){
			if(t[i]==t[j]){
				count++;
			}
		}
		
		if(count > max_count){
			max_count=count;
			most_frequent=t[i];
		}
	}
	return most_frequent*alpha;
}

int evaluate(Plateau p,char currentPlayer){
	int utility=0;
	if(victory(p)==1){
		utility+=100;
	}
	if(loss(p)==1){
		utility+=-100;
	} 
	if(currentPlayer==CASE_NOIRE){
		utility += density(p, currentPlayer, ALPHA);
	}
	if(currentPlayer==CASE_BLANCHE){
		utility -= density(p, currentPlayer, ALPHA);
	}
	return utility;
}

void main(){
	Plateau plateau = {
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_VIDE, CASE_BLANCHE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_VIDE, CASE_BLANCHE, CASE_VIDE, CASE_VIDE},
    {CASE_NOIRE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_BLANCHE, CASE_VIDE, CASE_BLANCHE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_BLANCHE, CASE_VIDE, CASE_VIDE, CASE_BLANCHE},
    {CASE_VIDE, CASE_VIDE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE}
};
	printf("%i",evaluate(plateau,CASE_BLANCHE));


}


