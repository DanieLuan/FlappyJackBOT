#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "AIfishing.h"




/*--------------FUNÇÃO PARA LER O MAPA------------------*/
void readMap(int h, int w, int** mat_map){
  char id[10][MAX_STR];
  //int map_mat[h][w], n, x[50], y[50];
  
  // Read SeaMap
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      scanf("%i", &mat_map[i][j]);
    }
  }
}





/*--------------FUNÇÃO PARA LER OS DADOS DOS BOTS------------------*/
void readBots(int numBots, bot_info* bots){
	for (int i = 0; i < numBots; i++){
      scanf("%s %i %i", bots[i].botID, &bots[i].Y, &bots[i].X);
      fprintf(stderr, "%s Está nesta posição = %dx %dy \n",bots[i].botID, bots[i].X, bots[i].Y);
    }
}





/*--------------FUNÇÃO PARA IDENTIFICAR O NUMERO DO BOT-----------------*/
int IdentifyMe(char thisBotID[MAX_STR],int numbots, bot_info* bots){
  //Identify ID relative to another IDs
  for (int i = 0; i < numbots; i++){
    if(0 == strcmp(bots[i].botID, thisBotID)){
			fprintf(stderr, "IdentifyID : %d\n", i);
      return i;
		}
  }
}





/*--------------FUNÇÃO PARA ACHAR O LOCAL DE PESCA MAIS LUCRATIVO --------------*/
void findSpot(int h, int w, int** map_mat, int range, int myIdNumerical, bot_info* bots, int* profitX, int* profitY){
  int profit = 0;
  //Algorithm to define Fihsing Spot
  	for (int i = 0; i < h; i++) {   
      for (int j = 0; j < w; j++) {
        if((bots[myIdNumerical].X - range <= j && bots[myIdNumerical].X + range >= j) && (bots[myIdNumerical].Y - range <= i && bots[myIdNumerical].Y + range >= i)){
            if (map_mat[i][j] >= 10){ //Posição que tem peixe
            int thisProfit =0;
            int d =0;
            d = map_mat[i][j]/10;
						//Descobrir qual peixe tem na posição
            if (d==1)
            	d = 100;
            else if(d==2)
            	d = 150;
            else if(d==3)
            	d = 200;

						//Cálculo de valor da posição
            thisProfit = (map_mat[i][j]%10)*d;
            if (thisProfit > profit){
            	profit = thisProfit;
            	*profitX = j;
            	*profitY = i;
            }
          }
          else if (map_mat[i][j] == 1){
          //one is a PORT
          }
      }
    }
  }
  fprintf(stderr, "o local de pesca mais lucrativo é em %d %d com o total de %d no range de %d para o %dº bot \n", *profitX, *profitY, profit, range, (myIdNumerical + 1));
}




/*--------------FUNÇÃO PARA DECIDIR O CAMINHO------------------*/
int pathMaker(int* profXpos, int* profYpos, int myIdNumerical, bot_info* bots){

  srand(*profXpos + *profYpos + bots[myIdNumerical].X + bots[myIdNumerical].Y);

  int r = rand() % 2;
	
  if(r == 0){//ACHAR UMA FORMA MAIS INTELIGENTE DE USAR O RANDOOM PRA NAO TER QUE COPIAR E COLAR OS MESMO IF PRAS DUAS OCASIÕES
    if(*profXpos > bots[myIdNumerical].X){
	    printf("RIGHT\n");
      fprintf(stderr, "o %dº bot andou para RIGHT com o destino de %dx e %dy \n", myIdNumerical + 1, *profXpos, *profYpos);
      return 0;
    }
    else if(*profXpos < bots[myIdNumerical].X){
      printf("LEFT\n");
      fprintf(stderr, "o %dº bot andou para LEFT com o destino de %dx e %dy \n", myIdNumerical + 1, *profXpos, *profYpos);
      return 0;
    }
    if(*profYpos > bots[myIdNumerical].Y){
	    printf("DOWN\n");
      fprintf(stderr, "o %dº bot andou para DOWN com o destino de %dx e %dy \n", myIdNumerical + 1, *profXpos, *profYpos);
      return 0;
    }
    else if(*profYpos < bots[myIdNumerical].Y){
      printf("UP\n");
      fprintf(stderr, "o %dº bot andou para UP com o destino de %dx e %dy \n", myIdNumerical + 1, *profXpos, *profYpos);
      return 0;
    }
  }
  else{
    if(*profYpos > bots[myIdNumerical].Y){
	    printf("DOWN\n");
      fprintf(stderr, "o %dº bot andou para DOWN com o destino de %dx e %dy \n", myIdNumerical + 1, *profXpos, *profYpos);
      return 0;
    }
    else if(*profYpos < bots[myIdNumerical].Y){
      printf("UP\n");
      fprintf(stderr, "o %dº bot andou para UP com o destino de %dx e %dy \n", myIdNumerical + 1, *profXpos, *profYpos);
      return 0;
    }
    if(*profXpos > bots[myIdNumerical].X){
	    printf("RIGHT\n");
      fprintf(stderr, "o %dº bot andou para RIGHT com o destino de %dx e %dy \n", myIdNumerical + 1, *profXpos, *profYpos);
      return 0;
    }
    else if(*profXpos < bots[myIdNumerical].X){
      printf("LEFT\n");
      fprintf(stderr, "o %dº bot andou para LEFT com o destino de %dx e %dy \n", myIdNumerical + 1, *profXpos, *profYpos);
      return 0;
    }
  }
  fprintf(stderr, "o bot chegou no destino \n");
  return 1;
}


/*----------------------------FUNÇÃO PARA PESCAR---------------------------*/
int fishingAction(int* profXpos, int* profYpos, int** mat_map, int* weight){
  fprintf(stderr, "DEVERIA PESCARRRRRRRRRRRRRRRR \n");
  fprintf(stderr, "%dx %dy \n", *profXpos, *profYpos);
  fprintf(stderr, "%d\n",mat_map[*profYpos][*profXpos]);

  if((mat_map[*profYpos][*profXpos] > 11) && (mat_map[*profYpos][*profXpos]  <= 19)){
    //fprintf(stderr, "Pescou Robalo, carga de %dKg \n",*weight);
    printf("FISH\n");
    *weight ++;
    return 0;
  }
  else if((mat_map[*profYpos][*profXpos] > 21) && (mat_map[*profYpos][*profXpos]  <= 29)){
    //fprintf(stderr, "Pescou Cioba, carga de %dKg \n",*weight);
    printf("FISH\n");
    *weight ++;
    return 0;
  }
  else if((mat_map[*profYpos][*profXpos] > 31) && (mat_map[*profYpos][*profXpos]  <= 39)){
    //fprintf(stderr, "Pescou Robalo, carga de %dKg \n",*weight);
    printf("FISH\n");
    *weight ++;
    return 0;
  }

  return 1;
}

void findPort(int h, int w, int** map_mat, int myIdNumerical, bot_info* bots, int* portX, int* portY){
  //Algorithm to define Fihsing Spot
  int thisPortX =0;
  int thisPortY =0;
  for (int i = 0; i < h; i++){   
    for (int j = 0; j < w; j++){
      if (map_mat[i][j] == 1){//one is a PORT
        thisPortX = j;
        thisPortY = i;

        bots[myIdNumerical].X + thisPortX


        *portX = j;
        *portY = i;



      }
    }
  }
  fprintf(stderr, "o Porto mais proximo é em %dx %dy para o %dº bot\n", *portX, *portY, (myIdNumerical + 1));
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