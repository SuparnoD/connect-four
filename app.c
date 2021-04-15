#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 1000

struct stack {
    char array[MAX][10];
    int top;
};

void init_stack(struct stack *);
void push(struct stack *, char board[][10]);
void pop(struct stack *);

void menu();
void display_board(char board[][10]);
int drop(char board[][10]);
void check(char board[][10],char str, int choice);

struct stack s;
bool winner = false;
bool undo = false;
char board[9][10];
int drop_choice;

int main(){
    init_stack(&s);

    int turn = 1;
    int width = 7;
    int length = 6;

    display_board(board);
    int x = 10;

    while(!winner){
        if(!winner){
            if(!undo){
                if(turn==1){
                    turn++;
                printf("X's Turn\n");
                drop_choice = drop(board);
                push(&s, board);
                check(board, 'X', drop_choice);
                display_board(board);
                turn++;
                menu();
            } else {
                undo = false;
                turn--;
                pop(&s);
            }
            }
        }
        if(!winner){
            if(!undo){
                if(turn==2){
                    turn--;
                printf("O's Turn\n");
                drop_choice = drop(board);
                push(&s, board);
                check(board, 'O', drop_choice);
                display_board(board);
                menu();
            } else {
                undo = false;
                turn++;
                pop(&s);
            }
            }
        }
    }

    return 0;
}

void init_stack(struct stack *s){
    s->top = -1;
}

void push(struct stack *s, char board[][10]){
    if(s->top == MAX -1){
        printf("error");
        return;
    }
    s->top++;
    memcpy(s->array[s->top], board, 1000);
}

void pop(struct stack *s){
    if(s->top == -1){
        printf("--- BEGINNING OF GAME REACHED ---");
    }
    memcpy(board, &s->array[s->top], 1000);
    s->top--;
}

void menu(){
    int choice;

    printf("\nWould you like to:\n");
    printf("1. Proceed\n");
    printf("2. Undo\n");
    printf("3. Exit\n");
    scanf("%d", &choice);

    if(choice==1){
    } else if(choice==2){
        winner = false;
        pop(&s);
        display_board(board);
        menu();
    } else if(choice==3){
        printf("Program Terminated...\n");
        exit(0);
    } else {
        printf("Invalid Input!\n");
        menu();
    }
}

void display_board(char board[][10]){
    int row = 6;
    int column = 7;
    printf("  1 2 3 4 5 6 7\n");
    for(int i=1;i<=row;i++){
        printf("|");
        for(int ix=1;ix<=column;ix++){
            if(board[i][ix] != 'X' && board[i][ix] != 'O')
                board[i][ix] = '*';
                printf(" ");

            printf("%c",board[i][ix]);
        }

        printf(" |\n");
    }
}

int drop(char board[][10]){
    int choice;

    printf("Select 1-7\n");
    scanf("%d", &choice);

    while(choice < 1 || choice > 7){
        printf("Invalid Input! Select 1-7\n");
        scanf("%d", &choice);
    }

    return choice;
}

void check(char board[][10],char str, int choice){
    int length, turn;
    length = 6;
    turn = 0;

    do{
        if(board[length][choice] != 'X' && board[length][choice] != 'O'){
            board[length][choice] = str;
            turn = 1;
        }
        else
        --length;
    }while (turn !=1);

    if(str == '*'){
        if(board[length][choice] == 'X' || board[length][choice] == 'O'){
            board[length][choice] == str;
            turn = 1;
        }
    }

    // up-down
    if(board[length][choice] == 'X'   && 
		board[length+1][choice] == 'X' &&
		board[length+2][choice] == 'X' &&
		board[length+3][choice] == 'X'){
            winner = true;
            printf("\n---------- X Won! ----------\n");
			}
    
    if(board[length][choice] == 'X'   && 
        board[length-1][choice] == 'X' &&
        board[length-2][choice] == 'X' &&
        board[length-3][choice] == 'X'){
            winner = true;
            printf("\n---------- X Won! ----------\n");
            }  
    
    if(board[length][choice] == 'O'   && 
        board[length+1][choice] == 'O' &&
        board[length+2][choice] == 'O' &&
        board[length+3][choice] == 'O'){
            winner = true;
            printf("\n---------- O Won! ----------\n");
            }

    if(board[length][choice] == 'O'   && 
        board[length-1][choice] == 'O' &&
        board[length-2][choice] == 'O' &&
        board[length-3][choice] == 'O'){
            winner = true;
            printf("\n---------- O Won! ----------\n");
            }    


    //across
    if(board[length][choice] == 'X'   && 
		board[length][choice-1] == 'X' &&
		board[length][choice-2] == 'X' &&
		board[length][choice-3] == 'X'){
			winner = true;
            printf("\n---------- X Won! ----------\n");
			}  

    if(board[length][choice] == 'X'   && 
		board[length][choice+1] == 'X' &&
		board[length][choice+2] == 'X' &&
		board[length][choice+3] == 'X'){
			winner = true;
            printf("\n---------- X Won! ----------\n");
			} 
    
    if(board[length][choice] == 'O'   && 
		board[length][choice-1] == 'O' &&
		board[length][choice-2] == 'O' &&
		board[length][choice-3] == 'O'){
			winner = true;
            printf("\n---------- O Won! ----------\n");
			} 

    if(board[length][choice] == 'O'   && 
		board[length][choice+1] == 'O' &&
		board[length][choice+2] == 'O' &&
		board[length][choice+3] == 'O'){
			winner = true;
            printf("\n---------- O Won! ----------\n");
			} 

    //up-diagnol
    if(board[length][choice] == 'X'   && 
        board[length+1][choice-1] == 'X' &&
		board[length+2][choice-2] == 'X' &&
		board[length+3][choice-3] == 'X'){
			winner = true;
            printf("\n---------- X Won! ----------\n");
			}

    if(board[length][choice] == 'X'   && 
        board[length-1][choice+1] == 'X' &&
		board[length-2][choice+2] == 'X' &&
		board[length-3][choice+3] == 'X'){
			winner = true;
            printf("\n---------- X Won! ----------\n");
			}

    if(board[length][choice] == 'O'   && 
        board[length+1][choice-1] == 'O' &&
		board[length+2][choice-2] == 'O' &&
		board[length+3][choice-3] == 'O'){
			winner = true;
            printf("\n---------- O Won! ----------\n");
			}
    
    if(board[length][choice] == 'O'   && 
        board[length-1][choice+1] == 'O' &&
		board[length-2][choice+2] == 'O' &&
		board[length-3][choice+3] == 'O'){
			winner = true;
            printf("\n---------- O Won! ----------\n");
			}


    //down-diagonal
    if(board[length][choice] == 'X'   && 
		board[length+1][choice+1] == 'X' &&
		board[length+2][choice+2] == 'X' &&
		board[length+3][choice+3] == 'X'){
			winner = true;
            printf("\n---------- X Won! ----------\n");
            }

    if(board[length][choice] == 'X'   && 
		board[length-1][choice-1] == 'X' &&
		board[length-2][choice-2] == 'X' &&
		board[length-3][choice-3] == 'X'){
			winner = true;
            printf("\n---------- X Won! ----------\n");
            }

    if(board[length][choice] == 'O'   && 
		board[length+1][choice+1] == 'O' &&
		board[length+2][choice+2] == 'O' &&
		board[length+3][choice+3] == 'O'){
			winner = true;
            printf("\n---------- O Won! ----------\n");
            }

    if(board[length][choice] == 'O'   && 
		board[length-1][choice-1] == 'O' &&
		board[length-2][choice-2] == 'O' &&
		board[length-3][choice-3] == 'O'){
			winner = true;
            printf("\n---------- O Won! ----------\n");
            }		
}