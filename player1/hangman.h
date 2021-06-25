/****************************************************************************************************************************
 *                                              !!! Hangman !!!                                                             *
 * Players - Two                                                                                                            *
 * Protocol Used - UDP                                                                                                      *
 * GCC Version - 4.1.1 20061011 (Red Hat 4.1.1-30)                                                                          *
 * Created By :- Anuj Aggarwal (PRN No - 043)                                                                               *
 ***************************************************************************************************************************/
#include <stdio.h>              
#include <stdlib.h>             
#include <sys/socket.h>         
#include <netinet/in.h>         
#include <arpa/inet.h>          
#include <unistd.h>             
#include <string.h>
#include <signal.h>

char play1_game(int sockfd,struct sockaddr_in *player2,socklen_t *player2_len);
char play2_game(int sockfd,struct sockaddr_in *player2,socklen_t *player2_len);
int check_char(char ch,char string[],int pos[]);

struct info{
    int count;
    int lives;
    int invalid;
    int win_flag;
    int pos[20];
};

