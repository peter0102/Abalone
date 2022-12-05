#include <stdio.h>
#include "main.h"

int main(int argc, char *argv[]) {
	int i=1;
	while(game!=0) {
		if(turn(i)==2) {
		printf("C'est au tour des noirs de jouer\n");
		
		
		}
		else {
		printf("C'est au tour des blancs de jouer \n");
		
		
		}
		i++;
	}
	
}

int turn(int current_turn){
	if (current_turn%2+1==2) return 2;
	else return 1;
}
