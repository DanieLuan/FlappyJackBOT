#ifndef AIfishing
#define AIfishing

void readMap(int h, int w, int** mat);

void readBots(int numBots, bot_info* bots);

int IdentifyMe(char thisBotID[MAX_STR], int numbots, bot_info* bots);

void findSpot(int h, int w, int** map_mat, int range, int myIdNumerical, bot_info* bots, int* profitX, int* profitY);

void findPort(int h, int w, int** map_mat, int myIdNumerical, bot_info* bots, int* portX, int* portY);

int pathMaker(int* profXpos, int* profYpos, int myIdNumerical, bot_info* bots);

int fishingAction(int* profXpos, int* profYpos, int** mat_map, int* weight, int* stage);

//Funcs to alloc memory when necessary
int **alocMat(int rows, int cols);
int *alocArr(int rows);

#endif