#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "AIfishing.h"

int main() {	
	int h, w;                 //Al
	char line[MAX_STR];       // dados temporários
	char myId[MAX_STR];       // identificador do bot em questão
	setbuf(stdin, NULL);      // stdin, stdout e stderr não terão buffers
	setbuf(stdout, NULL);     // assim, nada é "guardado temporariamente"
	setbuf(stderr, NULL);

	scanf("AREA %i %i", &h, &w);  //altura (h) x largura (w)
	scanf(" ID %s", myId);  // ...e o id do bot

  int **mat_map;
	int saldo = 0;            //valor 
	int range = 2;                //Área de busca de spots de pescado
	int *weight = 0;	
  int numBots =0;
  int myIdNum;
  int *profXpos , *profYpos;
  int stage = 0;

	bot_info* bots; //Registro para armazenar: X de um bot, Y de um bot, ID de um bot
	
	// === INÍCIO DA PARTIDA ===

  profXpos = (int*) malloc(sizeof(int));
  profYpos = (int*) malloc(sizeof(int));

	mat_map = alocMat(h, w);
  
	int num = 0;
	while (1) {
/*----------------------------------ROUND---------------------------*/
/*----------------------------------ROUND---------------------------*/
		num++;
		fprintf(stderr, "------------- ROUND %d BOT A -------------\n", num);
/*----------------------------------ROUND---------------------------*/
/*----------------------------------ROUND---------------------------*/

    readMap(h, w, mat_map); //Leitura do mapa

    scanf(" BOTS %i", &numBots); // Read Number of bots in game

		fprintf(stderr, "Existem %d bots na partida\n", numBots);

		/*char bots[i].botID[numBots][MAX_STR]; //
    int BotsParamsX[numBots];
    int bots[i].Y[numBots];*/

		bots = (bot_info*) malloc(sizeof(bot_info) * numBots); //Alocação Dinâmica
		readBots(numBots, bots);

		myIdNum = IdentifyMe(myId, numBots, bots);
   
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
    if(stage==0){
      findSpot(h, w, mat_map, range, myIdNum, bots, profXpos, profYpos);
      stage++;

    }
    if(stage ==1){
      if(pathMaker(profXpos, profYpos, myIdNum, bots) == 1){
        stage++;
      }
      if(stage ==1){
        scanf("%s", line);  
      }
       fprintf(stderr, "estagio %d\n",stage);
    }
    if (stage ==2){
      if(fishingAction(profXpos, profYpos, mat_map, weight) == 1 ){     
        fprintf(stderr, "A PESCA FOI CONCLUIDA \n");
        stage++;
      }

      if(stage ==2){
        scanf("%s", line);
      }

    }
     if (stage ==3){
       fprintf(stderr, "ESTAGIO 3 NAO FOI FEITO O BOT NAO VAI ENVIAR NADA RESULTARAM EM ERRO \n");

      if(stage ==3){
        scanf("%s", line);
      }

    }
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
/*--------------ESTAGIOS DO BOT CLICICO------------------*/

// o erro agr ta na no segundo estagio qunado é pra pescar, acho que o bot ta tentando fazer 2 ações no mesmo round ou sla oq, mas o estagio 1 ta funcionando bem. outro coisa que vi é que o nome do bot vira invalid quando ele é elimiinado, tem que implementar isso no bot para ele perceber que outro bot é eleminado.


/*--------------RETORNO DO OCMA.JS------------------*/
/*--------------RETORNO DO OCMA.JS------------------*/
/*--------------RETORNO DO OCMA.JS------------------*/
    if(0 == strcmp(line,"SEABASS"))
      fprintf(stderr, "Pescou Robalo\n");
    else if(0 == strcmp(line,"SNAPPER"))
      fprintf(stderr, "Pescou Cioba\n");
    else if (0 == strcmp(line,"MULLET"))
      fprintf(stderr, "Pescou Tainha\n");
    else if(0 == strcmp(line,"DONE"))
      fprintf(stderr, "Conseguiu Andar\n");
    else if(0 == strcmp(line,"BUSY"))
      fprintf(stderr, "Não Conseguiu Andar local ocupado por outro bot\n");
    else if (0 == strcmp(line,"OUT"))
      fprintf(stderr, "Não Conseguiu Andar local fora do limite do mapa\n");
/*--------------RETORNO DO OCMA.JS------------------*/
/*--------------RETORNO DO OCMA.JS------------------*/
/*--------------RETORNO DO OCMA.JS------------------*/

	free(bots); //Liberar memória pós uso devido ao loop while
	}

	free(*mat_map);
	free(mat_map);
	return 0;
}