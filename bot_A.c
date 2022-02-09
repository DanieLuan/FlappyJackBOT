#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	int saldo = 0;    //Saldo total do bot
	int range = 10;		//Área de busca de spots de pescado
	int *weight = 0;	//Peso da carga
  int numBots =0;		//Quantidade de bots em jogo
  int myIdNum;			//ID do bot no qual o programa roda (bot_A, bot_B, bot_C, ...)
  int *profXpos , *profYpos;		//Posições de pesca, X e Y
  int stage = 0;		//Estágio de funcionamento do bot
	bot_info* bots; //Registro para armazenar: X de um bot, Y de um bot, ID de um bot
	int *portX;
	int *portY;
	
	// === INÍCIO DA PARTIDA ===
	//Alocações dinamicamente
  profXpos = (int*) malloc(sizeof(int));
  profYpos = (int*) malloc(sizeof(int));
	mat_map = alocMat(h, w);
	int num = 0;//DEBUG!!! APAGAR DEPOIS

	while (1) {
/*----------------------------------ROUND---------------------------*/
/*----------------------------------ROUND---------------------------*/
		num++; //DEBUG APAGAR DEPOIS
		fprintf(stderr, "------------- ROUND %d BOT A -------------\n", num); //DEBUG APAGAR DEPOIS
/*----------------------------------ROUND---------------------------*/
/*----------------------------------ROUND---------------------------*/

    readMap(h, w, mat_map); //Leitura do mapa
    scanf(" BOTS %i", &numBots); // Entrada da quantidade de bots existem na partida
		
		fprintf(stderr, "Existem %d bots na partida\n", numBots); //DEBUG APAGAR DEPOIS
		//Alocação Dinâmica que ocorre em cada repetição

		bots = (bot_info*) malloc(sizeof(bot_info) * numBots); 
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
      if(stage == 1){
        scanf("%s", line);  
      }
       fprintf(stderr, "estagio %d\n",stage); //DEBUG APAGAR DEPOIS
    }
    if(stage ==2){
      if(fishingAction(profXpos, profYpos, mat_map, weight) == 1 ){
        fprintf(stderr, "A PESCA FOI CONCLUIDA \n"); //DEBUG APAGAR DEPOIS
        stage++;
      }
      if(stage ==2){
        scanf("%s", line);
      }
    }
    if(stage ==3){
			if(findPort())
      fprintf(stderr, "ESTAGIO 3 NAO FOI FEITO O BOT NAO VAI ENVIAR NADA RESULTARAM EM ERRO \n"); //DEBUG APAGAR DEPOIS
      if(stage ==3){
        scanf("%s", line);
      }
    }
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
/*--------------ESTAGIOS DO BOT CLICICO------------------*/
/*--------------ESTAGIOS DO BOT CLICICO------------------*/

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