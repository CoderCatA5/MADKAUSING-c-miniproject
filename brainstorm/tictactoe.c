#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char pos[9];

//prints the actual board
void print_board(){
    printf("\n");
    printf("%c|%c|%c\n", pos[0], pos[1],pos[2]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n", pos[3], pos[4],pos[5]);
    printf("-+-+-\n");
    printf("%c|%c|%c \n", pos[6], pos[7],pos[8]);
}

//declares the winner
void win(int player, int winner, int pos[]){
    
    print_board();
    if(winner){
        printf("Player %d is the winner. \n",player);
    }else{
        printf("Match draw\n");
    }
}

int main(){

    int mode;    
    int winner = 0, count = 0;
    int index, sign, player, flag;
    //initialize the positions to blank
    for(int i = 0; i < 9;i++){
        pos[i] = ' ';
    }

start:
    printf("\n--Welcome to tictactoe!--\n");
    printf("Select mode:\n1.PvP\n2.PvE\n");
    scanf("%d",&mode);
    while(count < 9 && winner != 1){
        srand(time(NULL));
        flag = 0;
        //print board
        print_board();
        //if condition that checks the player turn
        if(count % 2 == 0){
            sign = 'X';
            player = 1;
        }else{
            sign = '0';
            player = 2;
        }
        if(player == 1 || (player == 2 && mode == 1)){
            printf("Move for player%d (1-9): ",player);
            scanf("%d",&index);
            if(index < 1 || index > 9){
                printf("Allowed index is 1 to 9\n");
                continue;
            }
            if(pos[index-1] == 'X' || pos[index-1] == 'O'){
                printf("Position is occupied\n");
                continue;
            }
        }
        else if(player == 2 && mode == 2){
            do{
                index = (rand() % 10) + 1;
            }while(pos[index - 1] != ' ');
        }
        pos[index-1] = sign;
        count++;
        //horizontal row check
        for(int i = 0; i < 9; i++){
            if(i % 3 == 0)
                flag = 0;
            if(pos[i] == sign)
                flag++;
            if(flag == 3){
                winner = 1;
                win(player , winner , pos);
            }
        }

        flag = 0;
        //vertical row check
        for(int i = 0; i < 3; i++){
            for(int k = i; k <= i + 6; k+=3){
                if(pos[k] == sign)
                    flag++;
            }
            if(flag == 3){
                winner = 1;
                win(player , winner , pos);
            }
            flag = 0;
        }

        flag = 0;

        if((pos[0] == sign && pos[4] == sign && pos[8] == sign) || (pos[2] == sign && pos[4] == sign && pos[6] == sign)){
            winner = 1;
            win(player, winner, pos);
        }
    }
    return 0;
}