#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define true 1
#define false 0
#define PAGE 4096
#define MAX_PLAYERS 11
// the author of this challenge does not know how to write c code for shit
/*
still has the issue of deleting players, if we do not free last player in arr, it will decrement
ptr whilst still having a chunk. that pointer/chunk will not longer be accessable
*/
typedef unsigned int bool;// works better than define
typedef struct player {
    int attack;
    int defense;
    int speed;
    int precision;
    char name[50];
}p;
int idx,slt=0;
p* players[MAX_PLAYERS];

void add_player() {
    char* str;
    int i=0;
    while (i<MAX_PLAYERS&&players[i]!=0) {//iterate until free or too many
        i++;
    }
    if (idx==MAX_PLAYERS) {
   puts("Maximum number of players reached!");
        fflush(stdout);
    } else {
        printf("found free slot: %d\n",i);
        fflush(stdout);// why they do this? there is no need??
        p* new_p = (p*)malloc(sizeof(p));
        if (new_p==NULL) {
            puts("Could not allocate");
        }else{
            printf("Enter players name: ");\
            read(0,new_p->name,50);
            new_p->name[strcspn(new_p->name,"\n")]=0;//remove trailing \n
            printf("Enter attack point: ");
            scanf("%d",&new_p->attack);
            printf("Enter defense point: ");
            scanf("%d",&new_p->defense);
            printf("Enter speed: ");
            scanf("%d",&new_p->speed);
            printf("Enter precision: ");
            scanf("%d",&new_p->precision);
            players[idx]=new_p;
            idx++;
        }
    }
}
void delete_player() {
    int input;
    printf("Enter index: ");
    scanf("%d",&input);
    if(input<MAX_PLAYERS) {
        free(players[input]);
        puts("She\'s gone!");
    } else {
        puts("Invalid Index!");
    }
    idx--;
}
void select_player() {
    int input;
    printf("Enter index: ");
    scanf("%d",&input);
    if(input<MAX_PLAYERS&&players[input]!=0) {
        puts("Player selected!");
        printf("\nName: %s",players[input]->name);
        printf("\tA/D/S/P: %d/%d/%d/%d\n\n",
        players[input]->attack,
        players[input]->defense,
        players[input]->speed,
        players[input]->precision );
        slt=input;
    } else {
        puts("Invalide Index");
    }
}
void edit_name(){ // shell
    char buffer[50];
    printf("Enter new name: ");
    read(0,buffer,50);
    buffer[strcspn(buffer,"\n")]=0;
    int len = strlen(buffer);// < --
    //we will overwrite this GOT entry, and since we are read()ing it, we can execute anything
    strcpy(players[slt]->name, buffer);
}
void edit_attack(){
    printf("Enter attack points: ");
    scanf("%d", &players[slt]->attack);
}
void edit_defense(){
    printf("Enter defense points: ");
    scanf("%d", &players[slt]->defense);
}
void edit_speed(){
    printf("Enter speed points: ");
    scanf("%d", &players[slt]->speed);
}
void edit_precision(){
    printf("Enter precision points: ");
    scanf("%d", &players[slt]->precision);
}
void edit_player() {
    int input;
    bool check = false; // very bad way to implement a check, but it is what it is
    // fuck you, i love goto statements
    if (!idx>0&&slt>=0) {//if player exists and if selected points to existing index
        puts("No player has been selected!");goto die;
    }
    while (1) {
        puts("1.- Edit name");
        puts("2.- Edit attack");
        puts("3.- Edit defense");
        puts("4.- Edit speed");
        puts("5.- Edit precision");
        puts("6.- Exit");
        printf("Enter: ");
        scanf("%d",&input);
        switch(input) {
        case 1:
            edit_name();
            break;
        case 2:
            edit_attack();
            break;
        case 3:
            edit_defense();
            break;
        case 4:
            edit_speed();
            break;
        case 5:
            edit_precision();
            break;
        case 6:
            goto die;
        default:
            puts("Invalid choice!");
        }
    die: return;
    }
}
void show_player() {
    int input;
    printf("Enter index: ");
    scanf("%d",&input);
    if (input>=idx) {
        puts("player doesnt exist!");
    } else {
        printf("\nName: %s\tA/D/S/P: %d/%d/%d/%d\n\n",
        players[input]->name,
        players[input]->attack,
        players[input]->defense,
        players[input]->speed,
        players[input]->precision);
    }
}
void show_team() {
    for (int i=0;i<idx;i++) {
        printf("\nName: %s\tA/D/S/P %d/%d/%d/%d\n\n",
        players[i]->name,
        players[i]->attack,
        players[i]->defense,
        players[i]->speed,
        players[i]->precision);
    }
}
int main(int argc,char**argv) {
    int input;
    puts("Welcome to your TeamManageer (TM)!");
    fflush(stdout);
    while (1) {
        puts("0.- Exit\n1.- Add player\n2.- Remove player\n3.- Select player");
        puts("4.- Edit player\n5.- Show player\n6.- Show team");
        printf("Your choice: ");
        scanf("%d",&input);

        switch(input) {
        case 0:
            exit(0);
            break;
        case 1:
            add_player();
            break;
        case 2:
            delete_player();
            break;
        case 3:
            select_player();
            break;
        case 4:
            edit_player();
            break;
        case 5:
            show_player();
            break;
        case 6:
            show_team();
            break;
        default:
            puts("Invalid option!!");
        }
    }
    return 0;
}
__attribute__((constructor))
void setup(){
    alarm(120);// reduce load on server if program has not been terminated, feel free to patch local
    setbuf(stdout,NULL);
}
