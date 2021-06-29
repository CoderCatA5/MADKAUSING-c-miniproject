#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
//#define clear() printf(“\033[H\033[J”)

int main(void)
{
    //clear();
    void gameplay(int mode);
    printf("\t\t\t ROCK PAPER SCISSORS LIZARD SPOCK\n");
    int mode;
    start:
    printf("choose your mode\n1.player\n2.player\n");
    scanf("%d",&mode);
    switch(mode)
    {
        case 1:     gameplay(1);
                    break;
        case 2:     gameplay(2);
                    break;
        default:    printf("invalid option\ntry again");
                    goto start;
    }
}
void gameplay(int mode)
{
    int p1,p2;
    char a[5][10],outcome;
    strcpy(a[0],"rock");
    strcpy(a[1],"paper");
    strcpy(a[2],"scissors");
    strcpy(a[3],"lizard");
    strcpy(a[4],"spock");
    retry:
    printf("\nrock=1\twins against scissors and lizard");
    printf("\npaper=2\twins against rock and spock");
    printf("\nscissors=3\twins against paper and lizard");
    printf("\nlizard=4\twins against paper and spock");
    printf("\nspock=5\twins against rock and scissors");
    if(mode==1)
    {
        printf("\nenter your choice\n");
        p1=getch();
        printf("*\n");
        p1 = (int)((char)p1 - '0');
        time_t t;
        srand(time(NULL));
        p2=(rand()%6)+1;
        if(p1>5 || p1<1)
        {
            printf("\ninvalid options chosen\nplease retry\n");
            goto retry;
        }
    }
    else
    {
        printf("\nPlayer 1,enter your choice\n");
        p1=getch();
        //printf("%d",p1);
        p1 = (int)((char)p1 - '0');
        printf("\nPlayer 2,enter your choice\n");
        p2=getch();
        //printf("%d",p2);
        p2 = (int)((char)p2 - '0');
        if(p1>5 || p1<1 || p2>5 || p2<1)
        {
            printf("\ninvalid options chosen\nplease retry\n");
            goto retry;
        }
    }
    if(p1==p2)     //checking for draw
      outcome='d'; 
   else
   {
      switch(p1)    //checking outcome
      {
        case 1:  if(p2==3 || p2==4)
                      outcome='w';
                  else 
                      outcome='l';
                  break;
        case 2:  if(p2==1 || p2==5)
                     outcome='w';
                  else 
                     outcome='l';
                  break;
        case 3:  if(p2==2 || p2==4)
                     outcome='w';
                  else 
                     outcome='l';
                  break;
        case 4:  if(p2==2 || p2==5)
                     outcome='w';
                  else 
                     outcome='l';
                  break;
        case 5:  if(p2==1 || p2==3)
                     outcome='w';
                  else 
                     outcome='l';
                  break;
      }
   }
   if(mode==1)
   {
        printf("you chose %s, computer chose %s\n",a[p1-1],a[p2-1]);
        switch(outcome)
        {
        case 'w':   printf("you win");
                    break;
        case 'l':   printf("you lose");
                    break;
        case 'd':   printf("it's a draw");
                    break;
        }
   }
   if(mode==2)
   {
        printf("Player 1 chose %s, Player 2 chose %s\n",a[p1-1],a[p2-1]);
        switch(outcome)
        {
        case 'w':   printf("Player 1 wins");
                    break;
        case 'l':   printf("Player 2 wins");
                    break;
        case 'd':   printf("it's a draw");
                    break;
        }
   }
}