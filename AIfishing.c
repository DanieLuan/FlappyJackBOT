#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "definitions.h"
#include "AIfishing.h"


/*--------------FUNÇÃO PARA LER O MAPA------------------*/
void readMap(int h, int w, int** mat_map){
  char id[10][MAX_STR];

  for (int i = 0; i < h; i++){
	for (int j = 0; j < w; j++){
		scanf("%i", &mat_map[i][j]);
	}
  }
}

/*------------LER OS DADOS DE TODOS BOTS-----------*/
void readBots(int numBots, bot_info* bots){
	for (int i = 0; i < numBots; i++){
		scanf("%s %i %i", bots[i].botID, &bots[i].Y, &bots[i].X);
	}
}

/*----------IDENTIFICA O NUMERO DE CADA BOT-----------*/
int IdentifyMe(char thisBotID[MAX_STR],int numbots, bot_info* bots){
  for (int i = 0; i < numbots; i++){
	if(0 == strcmp(bots[i].botID, thisBotID))
		return i; //RETORNA O VALOR DO BOT EM RELAÇÃO À ORDEM "A, B, C, ..."
  }
}

/*--------------FUNÇÃO PARA ACHAR O LOCAL DE PESCA MAIS LUCRATIVO --------------*/
int findSpot(int h, int w, int** map_mat, int range, int IDnum, bot_info* bots, int* profitX, int* profitY){

	int profit1 = 0, profit2 = 0, profit3 = 0, profit4 = 0;

	int profitX1 = 0, profitX2 = 0, profitX3 = 0, profitX4 = 0;
	int profitY1 = 0, profitY2 = 0, profitY3 = 0, profitY4 = 0;

  	int count;
  	//Algorithm to define Fihsing Spot
  	for (int i = 0; i < h; i++) {   
	  	for (int j = 0; j < w; j++) {
			if((bots[IDnum].X - range <= j && bots[IDnum].X + range >= j) && (bots[IDnum].Y - range <= i && bots[IDnum].Y + range >= i)){

				if(map_mat[i][j] >= 10 && map_mat[i][j]%10 > 1){ //Posição que tem peixe
							
				int thisProfit =0;
				int d =0;
				d = map_mat[i][j]/10;
				//Descobrir qual peixe tem na posição

				if(d==1)
					d = 100;
				else if(d==2)
					d = 150;
				else if(d==3)
					d = 200;

				//Cálculo de valor da posição
				thisProfit = (map_mat[i][j]%10)*d;
				if(thisProfit > profit1){

					profit4 = profit3;
					profit3 = profit2;
					profit2 = profit1;
					profit1 = thisProfit;

					profitY4 = profitY3;
					profitX4 = profitX3;

					profitY3 = profitY2;
					profitX3 = profitX2;

					profitY2 = profitY1;
					profitX2 = profitX1;

					profitY1 = i;
					profitX1 = j;
				}
			}
	 		}	
		}
	}
  srand(time(NULL));

  int r = rand() % 100;
	
	if (r >= 0 && r <= 40 && profit1 > 0){
		*profitX = profitX1;
		*profitY = profitY1;
		return 0;
	}
		srand(time(NULL));
	r = rand() % 100;
		if(r >= 41 && r <= 70 && profit2 > 0){
		*profitX = profitX2;
		*profitY = profitY2;
		return 0;
	}
		srand(time(NULL));
	r = rand() % 100;
	if(r >= 71 && r <= 90 && profit3 > 0){
		*profitX = profitX3;
		*profitY = profitY3;
		return 0;
	}
		srand(time(NULL));
		r = rand() % 100;
	if(profit4 > 0){
		*profitX = profitX4;
		*profitY = profitY4;
		return 0;
	}
	
		return 404;
	}


/*--------------FUNÇÃO PARA DECIDIR O CAMINHO------------------*/
int pathMaker(int* spotX, int* spotY, int myIdNumerical, bot_info* bots){
	srand(*spotX + *spotY + bots[myIdNumerical].X + bots[myIdNumerical].Y);
	int r = rand() % 2;

	if(r == 0){
		if(*spotX > bots[myIdNumerical].X){
		return 2; //RIGHT
		}
		else if(*spotX < bots[myIdNumerical].X){
		return 1; //LEFT
		}
		if(*spotY > bots[myIdNumerical].Y){
		return 4; //DOWN
		}
		else if(*spotY < bots[myIdNumerical].Y){
		return 3; //UP
		}
	}
	else{
		if(*spotY > bots[myIdNumerical].Y){
		return 4; //DOWN
		}
		else if(*spotY < bots[myIdNumerical].Y){
		return 3; //UP
		}
		if(*spotX > bots[myIdNumerical].X){
		return 2; //RIGHT
		}
		else if(*spotX < bots[myIdNumerical].X){
		return 1; //LEFT
		}
	}
	}

/*----------------------------FUNÇÃO PARA PESCAR---------------------------*/
int fishingAction(int* spotX, int* spotY, int** mat_map, int* weight, int* stage){
	if((mat_map[*spotY][*spotX] > 11) && (mat_map[*spotY][*spotX]  <= 19) && (*weight <=9)  ){
		*weight = *weight +1;
		return 5; //FISH
	}

	else if((mat_map[*spotY][*spotX] > 21) && (mat_map[*spotY][*spotX]  <= 29) &&  (*weight <=9) ){
		*weight = *weight +1;
		return 5; //FISH
	}

	else if((mat_map[*spotY][*spotX] > 31) && (mat_map[*spotY][*spotX]  <= 39) &&  (*weight  <=9) ){
		*weight = *weight +1;
		return 5; //FISH
	}
	else if(*weight  ==10){
		return 10; //NAO DEVE PESCAR. VOLTAR PORTO
	}
	else{
		return 20; //NAO DEVE PESCAR. SPOT COM 1 PEIXE | CASO EXTREMO
	}
	}


void findPort(int h, int w, int** map_mat, int myIdNumerical, bot_info* bots, int* portX, int* portY){
	//Algorithm to define Fihsing Spot
	int thisPortDist = 10000;
	int portDist = 10000;
		
	for (int i = 0; i < h; i++){   
		for (int j = 0; j < w; j++){
		if (map_mat[i][j] == 1){ //one is a PORT
				int x1;
				int y1;

				x1 = abs(bots[myIdNumerical].X - j);
				y1 = abs(bots[myIdNumerical].Y - i);

				thisPortDist = sqrt((x1*x1) + (y1*y1));

		if(thisPortDist <= portDist){
			*portX = j;
			*portY = i;
			portDist = thisPortDist;
			}     
		} 
		}
	}
}

void doAction(int action){
	if(action == 1){
	printf("LEFT\n");
	}
	else if(action == 2){
		printf("RIGHT\n");
	}
	else if(action == 3){
		printf("UP\n");
	}
	else if(action == 4){
		printf("DOWN\n");
	}
	else if(action == 5){
		printf("FISH\n");
	}
	else if(action == 6){
		printf("SELL\n");
	}
	else{
		printf("SELL\n");
	}
}

/*-----------------------------------------
-----------------FUNCS ALOC----------------
------------------------------------------*/

int **alocMat(int rows, int cols){
	int **mat = (int**) malloc(sizeof(int *) * rows);
	for(int i = 0; i < rows; i++){
		mat[i] = (int *) malloc(sizeof(int) * cols);
	}
	return mat;
}

int *alocArr(int rows){
	int *arr = (int *) malloc(sizeof(int*) * rows);
	return arr;
}