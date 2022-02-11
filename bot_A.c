#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "definitions.h"
#include "AIfishing.h"

int main() {	
	srand(time(NULL));
	int h, w;               //Al
	char line[MAX_STR];     // dados temporários
	char myId[MAX_STR];     // identificador do bot em questão
	setbuf(stdin, NULL);    // stdin, stdout e stderr não terão buffers
	setbuf(stdout, NULL);   // assim, nada é "guardado temporariamente"
	setbuf(stderr, NULL);


  /*------------------------ENTRADA DE DADOS DA PARTIDA---------------------*/
	scanf("AREA %i %i", &h, &w);  //altura (h) x largura (w)
	scanf(" ID %s", myId);  // ...e o id do bot
  /*------------------------ENTRADA DE DADOS DA PARTIDA---------------------*/




  /*------------------------PONTEIROS---------------------*/
  int **mat_map;		//Mapa do jogo
	int *weight;	//Peso da carga
	int *profXpos;
	int *profYpos;
  int *stage;		//Estágio de funcionamento do bot
	int *portX;
	int *portY;
  bot_info* bots; //Registro para armazenar: X de um bot, Y de um bot, ID de um bot
  /*---------------------------PONTEIROS-------------------*/




  /*----------------------------Variáveis-------------------------*/
  int action = 0; //1 - LEFT | 2 - RIGHT | 3 - UP | 4 - DOWN | 5 - FISH | 6 - SELL
	int saldo = 0;    //Saldo total do bot
	int range = (rand() % (5 - 4 + 1)) + 4;
	int rangeStart = range;		//Área de busca de spots de pescado
  int numBots =0;		//Quantidade de bots em jogo
  int myIdNum;			//ID do bot no qual o programa roda (bot_A, bot_B, bot_C, ...)
  int num = 0;//DEBUG!!! APAGAR DEPOIS
  int UnStuck = 0;
  /*-----------------------------Variáveis-----------------------*/





	/*----------------------------Alocações-------------------------*/
  stage  = (int*) malloc(sizeof(int));
	weight = (int*) malloc(sizeof(int));
	portX = (int*) malloc(sizeof(int));
  portY = (int*) malloc(sizeof(int));
  profXpos = (int*) malloc(sizeof(int));
  profYpos = (int*) malloc(sizeof(int));
	mat_map = alocMat(h, w);
	bots = (bot_info*) malloc(sizeof(bot_info) * numBots); 
  /*----------------------------Alocações-------------------------*/

  *weight = 0;
  *stage = 0;
	*portX = 0;
	*portY = 0;
	*profXpos = 0;
  *profYpos = 0;

	//================================INÍCIO DA PARTIDA===============================//
	while (1) {
		num++; //DEBUG APAGAR DEPOIS
		fprintf(stderr, "------------- ROUND %d -------------\n", num); //DEBUG APAGAR DEPOIS

    /*--------------ENTRADA DE DADOS----------------*/
    readMap(h, w, mat_map); //Leitura do mapa
    scanf(" BOTS %i", &numBots); // Entrada da quantidade de bots existem na partida
		readBots(numBots, bots); //Coordenadas dos BOTS
    /*--------------ENTRADA DE DADOS----------------*/

    /*--------------IDESCOBRIR NUMERO DO BOT----------------*/
    myIdNum = IdentifyMe(myId, numBots, bots);
    /*--------------IDESCOBRIR NUMERO DO BOT----------------*/

    /*---------------- PROCESSAMENTO -> ESTÁGIOS ---------------------*/
    /*---------------- PROCESSAMENTO -> ESTÁGIOS ---------------------*/
    /*---------------- PROCESSAMENTO -> ESTÁGIOS ---------------------*/
    if(UnStuck == 1){//PARA O UNSTUCK FUNCIOANR COLOCAR VALOR IGUAL A 1 E NO BUSY ATRIBUIR 1
      fprintf(stderr, "Função para destravar\n");
      UnStuck = 0;

			findSpot(h, w, mat_map, range, myIdNum, bots, profXpos, profYpos);
      action = pathMaker(profXpos, profYpos, myIdNum, bots);
    }
    else{
      if(*stage == 0){
				while(findSpot(h, w, mat_map, range, myIdNum, bots, profXpos, profYpos) == 404){
          range++;
        }
				*stage = 1;

      }
      if(*stage == 1){
        if(bots[myIdNum].X == *profXpos && bots[myIdNum].Y == *profYpos){ //WARNING HERE
          *stage = 2;
        }
        else{
          action = pathMaker(profXpos, profYpos, myIdNum, bots);
        }
      }
      if(*stage == 2){
        action = fishingAction(profXpos, profYpos, mat_map, weight, stage);
        if(action == 10){
          *stage = 3;
        }
        else if (action == 20){
          while(findSpot(h, w, mat_map, range, myIdNum, bots, profXpos, profYpos) == 404){
          range++;
        	}
          action = pathMaker(profXpos, profYpos, myIdNum, bots);
          *stage = 1;
        }
      }
      if(*stage == 3){
        findPort(h, w, mat_map,myIdNum,bots,portX,portY);
        *stage = 4;	
      }
      if(*stage == 4){
        if(bots[myIdNum].X == *portX && bots[myIdNum].Y == *portY){ //WARNING HERE
          action = 6;
					range = rangeStart;
          *stage = 0;
          *weight = 0;
        }
        else{
          action = pathMaker(portX, portY, myIdNum, bots);
        }
      }
    }
/*------------------------- FIM PROCESSAMENTO ---------------------------*/
/*------------------------- FIM PROCESSAMENTO ---------------------------*/
/*------------------------- FIM PROCESSAMENTO ---------------------------*/

  /*---------------- DEBUG ---------------------
  fprintf(stderr, "bot %d: PESO A   %d\n", myIdNum, *weight);
	fprintf(stderr, "bot %d: RANGE    %d\n", myIdNum, range);
	fprintf(stderr, "bot %d: RANGEi   %d\n", myIdNum, rangeStart);
  fprintf(stderr, "bot %d: MYCORD   (%d, %d)\n", myIdNum, bots[myIdNum].X, bots[myIdNum].Y);
  fprintf(stderr, "bot %d: SPOT     (%d, %d)\n", myIdNum, *profXpos, *profYpos);
  fprintf(stderr, "bot %d: PORTnear (%d, %d)\n", myIdNum, *portX, *portY);
  ---------------- DEBUG ---------------------*/


  /*-----------------------ACTIONS--------------------*/
  //fprintf(stderr, "Action %d\n", action);
  

  doAction(action); // Função para imprimir a ação à ser executada
  scanf("%s", line); // RECEBE A RESPOSTA DA AÇÃO
  action = 0;
  /*-----------------------ACTIONS--------------------*/


  /*--------------RETORNO DO OCMA.JS------------------
  if(0 == strcmp(line,"SEABASS"))
    fprintf(stderr, "Pescou Robalo\n");//DEBUG APAGAR DEPOIS
  else if(0 == strcmp(line,"SNAPPER"))
    fprintf(stderr, "Pescou Cioba\n");//DEBUG APAGAR DEPOIS
  else if (0 == strcmp(line,"MULLET"))
    fprintf(stderr, "Pescou Tainha\n");//DEBUG APAGAR DEPOIS
  else if(0 == strcmp(line,"DONE"))
    fprintf(stderr, "Conseguiu Andar\n");//DEBUG APAGAR DEPOIS
  else if(0 == strcmp(line,"BUSY")){
    fprintf(stderr, "Não Conseguiu Andar Bot no destino\n");
    UnStuck++;
	}
  else if (0 == strcmp(line,"OUT"))
    fprintf(stderr, "Não Conseguiu Andar local fora do limite do mapa\n");//DEBUG APAGAR DEPOIS
--------------RETORNO DO OCMA.JS------------------*/

	}
  //================================FIM DA PARTIDA===============================//
  
	free(*mat_map);
	free(mat_map);
  free(stage);
  free(weight);
  free(portX);
  free(portY);
  free(profXpos);
  free(profYpos);
  free(bots);

	return 0;
}