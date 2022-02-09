FLAGS= -g -std=c99 -Wall -Wextra -Werror -pedantic

all: bot_A bot_B
bot_A: AIfishing
	--gcc bot_A.c AIfishing.o -o bot_A $(PARAMS)
bot_B: AIfishing
	gcc bot_B.c AIfishing.o -o bot_B $(PARAMS)
AIfishing: AIfishing.c
	gcc AIfishing.c -c $(PARAMS)
clean:
	rm -rf *.o