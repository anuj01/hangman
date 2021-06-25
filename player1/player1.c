/****************************************************************************************************************************
 *                                              !!! Hangman !!!                                                             *
 * Players - Two                                                                                                            *
 * Protocol Used - UDP                                                                                                      *
 * GCC Version - 4.1.1 20061011 (Red Hat 4.1.1-30)                                                                          *
 * Created By :- Anuj Aggarwal (PRN No - 043)                                                                               *
 ***************************************************************************************************************************/

#include"hangman.h"

char play1_game(int sockfd,struct sockaddr_in *sendAddr,socklen_t *sendAddr_len)
{
    int i,j,string_len,win=0;
    char name[20],string[20],ch,*show,more;
    char used[20];                    // array contains already used characters
    struct info update;
    struct sockaddr_in fromAddr;
    socklen_t addrLen;

    update.count=0;
    update.lives=6;
    update.invalid=0;
    update.win_flag=0;
    used[0]='\0';

    addrLen = sizeof(fromAddr);

    printf("\n Waiting for a player...\n");
    /* Get the name of player 2*/
    if((recvfrom(sockfd,name,sizeof(name),0,(struct sockaddr *)&fromAddr, &addrLen ))<0)
    { perror(" RECVFROM() failed "); exit(1);}
    printf("%s : wants to play the game\n",name);

    //printf("\n The socket no of Player 2 : %d ", ntohs(fromAddr.sin_port));
    //printf("\n The Ip  of Player 2 : %s ", inet_ntoa(fromAddr.sin_addr));

    /* Assigning the sendAddr's Address and length to the corresponding variables*/
    *sendAddr =  fromAddr;
    *sendAddr_len = addrLen;

    /* input the string to be guessed and send its length to Player 2*/
    printf("\n Enter the string for %s :\n",name);
    scanf("%s",string);
    string_len = strlen(string);
    if((sendto(sockfd,&string_len,4,0,(struct sockaddr *)sendAddr, *sendAddr_len ))<0)
    { perror(" SENDTO() failed "); exit(2);}

    /* initialize the show[] string*/
    show=(char *)malloc(string_len);
    for(i=0;i<string_len;i++)
        show[i]='-';

    printf("\n\n\t Now Wait and Watch... \n\n");

    printf("\n\t\t\t %s ",show);


    for(i=0;(update.win_flag!=1) && update.lives>0;i++)
    {
        update.invalid=0;
        if((recvfrom(sockfd,&ch,1,0,(struct sockaddr *)&fromAddr, &addrLen ))<0)
        { perror(" RECVFROM() failed "); exit(3);}

        // check for validity      
        for(j=0;used[j]!='\0';j++)
        {
            if(ch==used[j])
            {
                update.invalid=1;
                break;
            }
        }


        if(update.invalid==0)
        {
            for(j=0;used[j]!='\0';j++);
            used[j]=ch;
            used[j+1]='\0';

            win+=update.count = check_char(ch,string,update.pos); 
            if(update.count==0 && update.lives!=0)    //  if character is not matched 
                update.lives--;
            if(win==string_len)                       // if all characters matched means player2 win
                update.win_flag=1;        
        }

        /* update the show with matched characters */
        for(j=0;j<update.count;j++)
            show[update.pos[j]]=ch;

        printf("\n\t\t\t %s ",show);
        printf("\t Lives Remaining - %d",update.lives);

        if((sendto(sockfd,&update,sizeof(struct info),0,(struct sockaddr *) sendAddr, *sendAddr_len ))<0)
        { perror(" SENDTO() failed "); exit(4);}

    }

    if(update.win_flag==0)
    {
        if((sendto(sockfd,string,sizeof(string),0,(struct sockaddr *) sendAddr, *sendAddr_len ))<0)
        { perror(" SENDTO() failed "); exit(4);}
        printf("\n\n CONGRATULATIONS : YOU WIN\n");
    }

    else
        printf("\n Better Luck Next Time...\n");

    printf("\n\n Waiting for %s's response...\n\n",name);

    if((recvfrom(sockfd,&more,1,0,(struct sockaddr *)&fromAddr , &addrLen ))<0)
    { perror(" RECVFROM() failed "); exit(3);}


    return more;

}

int check_char(char ch,char string[],int pos[])
{
    int i,j,count=0;
    for(i=0,j=0;i<strlen(string);i++)
    {
        if(ch==string[i])
        {
            pos[j++]=i;  // pos[] contains the positions of matched characters
            count++;     // no. of characters matched
        }
    }

    return count;
}
