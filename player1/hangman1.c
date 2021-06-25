/****************************************************************************************************************************
 *                                              !!! Hangman !!!                                                             *
 * Players - Two                                                                                                            *
 * Protocol Used - UDP                                                                                                      *
 * GCC Version - 4.1.1 20061011 (Red Hat 4.1.1-30)                                                                          *
 * Created By :- Anuj Aggarwal (PRN No - 043)                                                                               *
 ***************************************************************************************************************************/


#include "hangman.h"           

#define P1_PORT 11703 


/* Signal Handler for SIGINT (ctrl+c)  & SIGTSTP (ctrl+z)  signals */
void sighandler(int signum)
{
    write(STDOUT_FILENO,"\n\t Thanks for playing Hangman !!!\n\n\t Have a nice day !!!\n",57);
    write(STDOUT_FILENO,"\n\t Game Over !!!\n\n",18);
    exit(3);
}


int main(int argc,char *argv[])
{
    int sockfd;
    char more;
    struct sockaddr_in player1,player2 ;
    struct sigaction act; 
    socklen_t player2_len;

    /* Create Socket */
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd < 0) { perror(" SOCKFD() failed"); exit(1);}


    /* Construct player 1 address structure */
    bzero(&player1,sizeof(player1));
    player1.sin_family = AF_INET;
    player1.sin_addr.s_addr = htonl(INADDR_ANY);
    player1.sin_port = htons(P1_PORT);

    player2_len = sizeof(player2);

    /* Bind to the player 1 address */
    if(bind(sockfd,(struct sockaddr *) &player1, sizeof(player1))<0) { perror("BIND() failed"); exit(2);}

    /* Installing Signal Handler for proper termination of the game */
    act.sa_handler=sighandler;
    sigfillset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGTSTP,&act,NULL);

    do{
        system("clear");
        printf("\n\t\t\t\t\t WELCOME TO HANGMAN !!!\n");
        more = play1_game(sockfd,&player2,&player2_len);
        //printf("\n\n\n The socket no of Player 2 : %d ", ntohs(player2.sin_port));
        //printf("\n The Ip  of Player 2 : %s ", inet_ntoa(player2.sin_addr));
        if('y' == more)
        {
            system("clear");
            printf("\n\t\t\t\t\t WELCOME TO HANGMAN !!!\n");
            more = play2_game(sockfd,&player2,&player2_len);
        }
        else
            break;

    }while('y'== more);

    close(sockfd);

    printf("\n\t Thanks for Playing Hangman !!!\n\n\t Have a nice Day !!!\n");
    printf("\n\t GAME OVER !!!\n");
    exit(0);

}










