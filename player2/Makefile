
hang : hangman2.o player1.o player2.o 
	gcc -o hang hangman2.o player1.o player2.o

hangman2.o : hangman2.c
	gcc -c hangman2.c

player1.o : player1.c
	gcc -c player1.c

player2.o : player2.c
	gcc -c player2.c

clean : 
	rm -f hang hangman2.o player1.o player2.o

