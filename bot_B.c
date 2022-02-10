#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h"
#include "AIfishing.h"

int main() {	
	int h, w;               //Al
	char line[MAX_STR];     // dados temporários
	char myId[MAX_STR];     // identificador do bot em questão
	setbuf(stdin, NULL);    // stdin, stdout e stderr não terão buffers
	setbuf(stdout, NULL);   // assim, nada é "guardado temporariamente"
	setbuf(stderr, NULL);

	scanf("AREA %i %i", &h, &w);  //altura (h) x largura (w)
	scanf(" ID %s", myId);  // ...e o id do bot

  int **mat_map;		//Mapa do jogo
	int *weight;	//Peso da carga
	int *profXpos;
	int *profYpos;
	int saldo = 0;    //Saldo total do bot
	int range = 10;		//Área de busca de spots de pescado
	bot_info* bots; //Registro para armazenar: X de um bot, Y de um bot, ID de um bot

  int numBots =0;		//Quantidade de bots em jogo
  int myIdNum;			//ID do bot no qual o programa roda (bot_A, bot_B, bot_C, ...)
 		//Posições de pesca, X e Y
  int *stage = 0;		//Estágio de funcionamento do bot
	int *portX;
	int *portY;
	
	//Alocações dinamicamente
  stage  = (int*) malloc(sizeof(int));
	weight = (int*) malloc(sizeof(int));
	portX = (int*) malloc(sizeof(int));
  portY = (int*) malloc(sizeof(int));
  profXpos = (int*) malloc(sizeof(int));
  profYpos = (int*) malloc(sizeof(int));
	mat_map = alocMat(h, w);
	
	// === INÍCIO DA PARTIDA ===
	
	int num = 0;//DEBUG!!! APAGAR DEPOIS

	//*weight = 0;
	*portX = 0;
	*portY = 0;
	*profXpos = 0;
  *profYpos = 0;

	while (1) {
/*----------------------------------ROUND---------------------------*/
/*----------------------------------ROUND---------------------------*/
		num++; //DEBUG APAGAR DEPOIS
		fprintf(stderr, "------------- ROUND %d BOT B -------------\n", num); //DEBUG APAGAR DEPOIS
/*----------------------------------ROUND---------------------------*/
/*----------------------------------ROUND---------------------------*/

    readMap(h, w, mat_map); //Leitura do mapa
    scanf(" BOTS %i", &numBots); // Entrada da quantidade de bots existem na partida
		
		fprintf(stderr, "Qnt Bots: %d\n", numBots); //DEBUG APAGAR DEPOIS
		//Alocação Dinâmica que ocorre em cada repetição

		bots = (bot_info*) malloc(sizeof(bot_info) * numBots); 
		readBots(numBots, bots);
		myIdNum = IdentifyMe(myId, numBots, bots);
   
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
    if(*stage==0){
      findSpot(h, w, mat_map, range, myIdNum, bots, profXpos, profYpos);
      *stage = *stage +1;
    }
    if(*stage ==1){
      if(pathMaker(profXpos, profYpos, myIdNum, bots) == 1){
        *stage = *stage +1;
      }
      if(*stage == 1){
        scanf("%s", line);  
      }
    }
    if(*stage ==2){
      if(fishingAction(profXpos, profYpos, mat_map, weight,stage) == 1 ){
        fprintf(stderr, "A PESCA FOI CONCLUIDA %d Kg \n",*weight); //DEBUG APAGAR DEPOIS
        if(*weight < 10){
          *stage = 0;
          scanf("%s", line);
        }
        else{
          scanf("%s", line);
          *stage = *stage +1;
        }
      }
      if(*stage == 2){
        scanf("%s", line);
      }
    }
    else if(*stage == 3){
			findPort(h, w, mat_map,myIdNum,bots,portX,portY);
			if(pathMaker(portX, portY, myIdNum, bots) == 1){
        *stage = 0;
        fprintf(stderr, "TENTOU VENDER\n");
        printf("SELL\n");
        scanf("%s", line);  
      }
			else{
				scanf("%s", line); 
			} 
    }
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
fprintf(stderr, "bot %d: PESO A   %d\n", myIdNum, *weight);
fprintf(stderr, "bot %d: MYCORD   (%d, %d)\n", myIdNum, bots[myIdNum].X, bots[myIdNum].Y);
fprintf(stderr, "bot %d: SPOT     (%d, %d)\n", myIdNum, *profXpos, *profYpos);
fprintf(stderr, "bot %d: PORTnear (%d, %d)\n", myIdNum, *portX, *portY);
// o erro agr ta na no segundo estagio qunado é pra pescar, acho que o bot ta tentando fazer 2 ações no mesmo round ou sla oq, mas o estagio 1 ta funcionando bem. outro coisa que vi é que o nome do bot vira invalid quando ele é elimiinado, tem que implementar isso no bot para ele perceber que outro bot é eleminado.

/*--------------RETORNO DO OCMA.JS------------------*/
    if(0 == strcmp(line,"SEABASS"))
      fprintf(stderr, "Pescou Robalo\n");//DEBUG APAGAR DEPOIS
    else if(0 == strcmp(line,"SNAPPER"))
      fprintf(stderr, "Pescou Cioba\n");//DEBUG APAGAR DEPOIS
    else if (0 == strcmp(line,"MULLET"))
      fprintf(stderr, "Pescou Tainha\n");//DEBUG APAGAR DEPOIS
    else if(0 == strcmp(line,"DONE"))
      fprintf(stderr, "Conseguiu Andar\n");//DEBUG APAGAR DEPOIS
    else if(0 == strcmp(line,"BUSY"))
      fprintf(stderr, "Não Conseguiu Andar local ocupado por outro bot\n");//DEBUG APAGAR DEPOIS
    else if (0 == strcmp(line,"OUT"))
      fprintf(stderr, "Não Conseguiu Andar local fora do limite do mapa\n");//DEBUG APAGAR DEPOIS
/*--------------RETORNO DO OCMA.JS------------------*/

	free(bots); //Liberar memória pós uso devido ao loop while
	}
	//Liberar memória de variáveis alocadas dinamicamente
	free(*mat_map);
	free(mat_map);
	return 0;
}