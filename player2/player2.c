
#include"hangman.h"


char play2_game(int sockfd,struct sockaddr_in *sendAddr,socklen_t *sendAddr_len)
{
    int i,j;
    int string_len;
    char name[20],ch,*show,more,*string;
    struct sockaddr_in fromAddr;
    socklen_t addrLen;
    struct info update;

    update.count=0;
    update.lives=6;
    update.invalid=0;
    update.win_flag=0;

    addrLen=sizeof(fromAddr);

    printf("\n Enter your name : ");
    scanf("%s",name);

    if((sendto(sockfd,name,sizeof(name),0,(struct sockaddr* )sendAddr, *sendAddr_len ))<0)
    { perror(" SENDTO() failed "); exit(4);}

    printf("\n\t Waiting for the string...\n");
    if((recvfrom(sockfd,&string_len,4,0,(struct sockaddr *)&fromAddr, &addrLen ))<0)
    { perror(" RECVFROM() failed "); exit(3);}
    printf("\n\t The string to be guessed is of %d characters\n",string_len);


    show=(char *)malloc(string_len);
    for(i=0;i<string_len;i++)
        show[i]='-';
    printf("\n\t\t\t\t %s",show);
    printf("\t Lives Remaining - %d",update.lives);
    printf("\n");

    printf("\n\n\t\t Guess the characters one by one:\n");

    for(i=0;(update.win_flag!=1)&& update.lives>0;i++)
    {
        do{
            ch=getc(stdin);
        }while(ch=='\n');

        if((sendto(sockfd,&ch,1,0,(struct sockaddr *)sendAddr, *sendAddr_len ))<0)
        { perror(" SENDTO() failed "); exit(4);}

        if((recvfrom(sockfd,&update,sizeof(struct info),0,(struct sockaddr *)&fromAddr, &addrLen ))<0)
        { perror(" RECVFROM() failed "); exit(3);}

        if(1==update.invalid)
        {
            printf("\n\t\t\t\t The character is already used\n");
            printf("\n\t\t\t\t %s",show);
            printf("\t Lives Remaining - %d",update.lives);
            printf("\n");
            continue;
        }

        for(j=0;j<update.count;j++)
            show[update.pos[j]]=ch;
        printf("\n\t\t\t\t %s",show);
        printf("\t Lives Remaining - %d",update.lives);
        printf("\n");
    }

    if(update.win_flag==1)
        printf("\n CONGRATULATIONS : YOU WIN !!! \n");
    else
    {
        string=(char *)malloc(string_len);
        if((recvfrom(sockfd,string,string_len,0,(struct sockaddr *)&fromAddr, &addrLen ))<0)
        { perror(" RECVFROM() failed "); exit(3);}
        printf("\n\t\t\t\t\a %s",string);
        printf("\n Better Luck Next Time... !!! \n");
    }

    printf("\n Do you want to play more??? (y\\n) \n");
    do{
        more=getc(stdin);
    }while(more=='\n');
    //scanf("\n%c",&more);


    if((sendto(sockfd,&more,1,0,(struct sockaddr *)sendAddr, *sendAddr_len ))<0)
    { perror(" SENDTO() failed "); exit(4);}

    return more;

}

