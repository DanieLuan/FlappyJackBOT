FLAGS= -g -std=c99 -Wall -Wextra -Werror -pedantic

all: bot_A bot_B bot_C bot_D clean
bot_A: AIfishing
	gcc bot_A.c AIfishing.o -o bot_A -lm $(PARAMS)
bot_B: AIfishing
	gcc bot_B.c AIfishing.o -o bot_B -lm $(PARAMS)
bot_C: AIfishing
	gcc bot_C.c AIfishing.o -o bot_C -lm $(PARAMS)
bot_D: AIfishing
	gcc bot_D.c AIfishing.o -o bot_D -lm $(PARAMS)
AIfishing: AIfishing.c
	gcc AIfishing.c -c -lm
clean:
	rm -rf *.o

exec:
	node ocma -q -mr 500 bot_A bot_B bot_C bot_D