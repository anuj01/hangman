/* Player 2 */
#include "hangman.h"           

#define P1_PORT  11703  //atoi(argv[2])
#define P2_PORT  11800  //atoi(argv[3])

void sighandler(int signum)
{
    write(STDOUT_FILENO,"\n\t Thanks for playing Hangman !!!\n\n\t Have a nice day !!!\n",57);
    write(STDOUT_FILENO,"\n\t Game Over !!!\n\n",18);
    exit(1);
}

int main(int argc,char *argv[])
{
    int sockfd;
    char more;
    struct sockaddr_in player1;
    struct sigaction act;
    socklen_t player1_len;

    if(argc != 2) { fprintf(stderr," SYNTAX : %s <player1-IP> \n ", argv[0]); exit(1);} 

    /* Create Socket */
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd < 0) { perror(" SOCKFD() failed"); exit(1);}


    /* Construct player 1 address structure */
    bzero(&player1,sizeof(player1));
    player1.sin_family = AF_INET;
    player1.sin_port = htons(P1_PORT);
    if(inet_pton(AF_INET,argv[1],&player1.sin_addr)<0) { perror(" INET_PTON() failed "); exit(2);}


    /* Install the signal handler */
    act.sa_handler=sighandler;
    sigfillset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGTSTP,&act,NULL);

    player1_len = sizeof(player1);


    do{
        system("clear");
        printf("\n\t\t\t\t\t WELCOME TO HANGMAN !!!\n");
        more = play2_game(sockfd,&player1,&player1_len);
        if('y'==more)
        {
            system("clear");
            printf("\n\t\t\t\t\t WELCOME TO HANGMAN !!!\n");
            //printf("\n player2 port no = %d", ntohs(player2.sin_port));
            //printf("\n player2 IP = %s", inet_ntoa(player2.sin_addr));
            more = play1_game(sockfd,&player1,&player1_len);
        }
        else
        {
            break;
        }
    }while('y'==more);

    close(sockfd);
    printf("\n\t Thanks for playing Hangman !!!\n\n\t Have a nice day !!!\n");
    printf("\n\t GAME OVER !!!\n");
}
