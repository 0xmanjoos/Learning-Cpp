#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#define MAX_GANGS   5
#define MAX_MEMBERS 20
using namespace std; // only stl, no 3rd p libs so ok
/* A vulnerable gang game

some vulns include:
incorrect indexing:

you can allocate 2 users, free index 0, and still have a pointer to 0
with the global idx for gangsters decremented. 

security implications:
use after free - dangling pointer ; we can read write into free chunk within cache bin.
double free    - if we are able to get into a fastbin, that may allow us to cause problems :)

buffer overflow:
virtual admin function has a buffer overflow
each inherited object/class will contain this virtual function/vtable entry

and probably much much more unintended bugs :)
*/
class gangster {
protected:
    bool capo_boost;
    int attack,defense,speed;
    string name;
private:
    virtual void admin() {
        char buffer[15];
        fprintf(stdout,"Welcome to the admin panel: ");
        scanf("%s",buffer);
        fprintf(stdout,"Saved!");
    }
public:
    virtual int stats() {
        return this->attack + this->defense + this->speed;
    }
    virtual void introduce() {
        cout<<
        "\nMy name is "<<name<<"\n"<<
        "Attack: "<<attack<<"\n"<<
        "Defense: "<<defense<<"\n"<<
        "Speed: "<<speed<<endl;
    }
};
typedef struct gang {
    char name[50];
    int idx,power;
    gangster* gang_members[MAX_MEMBERS];
}g;
typedef struct warzone {
    int idx;
    g* gangs[MAX_GANGS];
}war;

war* all_gangs = (war*)malloc(sizeof(war));

class capo:public gangster {
public:
    capo(string n,int a,int d,int s) {
        this->name=n;
        this->attack=a;
        this->defense=d;
        this->speed=s;
        this->capo_boost=true;
    }
    virtual void introduce() {
        gangster::introduce();
        cout<<"I am the capo of ";
    }
};
class footman:public gangster {
public:
    footman(string n,int a,int d,int s) {
        this->name=n;
        this->attack=a;
        this->defense=d;
        this->speed=s;
        this->capo_boost=false;
    }
    virtual void introduce() {
        gangster::introduce();
        cout<<"I am a footman for: ";
    }
};
void __attribute__((constructor)) setup() {
    alarm(240);//patch local, reduce server load
    setbuf(stdin,NULL);
    setbuf(stdout,NULL);
}
void banner() {
    fprintf(stdout," \
   ┬ ┬┌─┐┬┌─┬ ┬┌─┐┌─┐  ╦═╗╔═╗╔═╗ \n\
    └┬┘├─┤├┴┐│ │┌─┘├─┤  ╠╦╝╠═╝║ ╦ \n\
     ┴ ┴ ┴┴ ┴└─┘└─┘┴ ┴  ╩╚═╩  ╚═╝ \n\
            ____ \n\
           /___/\\_ \n\
          _\\   \\/_/\\__ \n\
        __\\       \\/_/\\ \n\
        \\   __    __ \\ \\ \n\
       __\\  \\_\\   \\_\\ \\ \\   __ \n\
      /_/\\\\   __   __  \\ \\_/_/\\ \n\
      \\_\\/_\\__\\/\\__\\/\\__\\/_\\_\\/ \n\
         \\_\\/_/\\       /_\\_\\/ \n\
            \\_\\/       \\_\\/ \n\n");

}
void scream_into_the_void() {
    int s=0;
    puts("Dame da ne dame yo dame na no yo");
    sleep(1);
    puts("Anta ga suki de suki sugite");
    sleep(1);
    puts("Dore dake tsuyoi osake demo");
    sleep(1);
    puts("Yugamanai omoide ga baka mitai");
    sleep(1);
    puts("How much do you want to scream?: ");
    cin>>s;
    if(s>256) {
        puts("you cannot scream that much!");
    }else{
        char* ptr = (char*)malloc(s);
        puts("Well.. go ahead....\n\n");
        printf("Scream: ");
        read(0,ptr,s);
    }
}
void show_users() {
    int n=all_gangs->idx;
    for(int i=0;i<n;i++) { // for all gangs
        int member_n = all_gangs->gangs[i]->idx;//so script doesnt deref repeat, just alloc as local var
        for (int j=0;j<member_n;j++) { // for all members in gang
            all_gangs->gangs[i]->gang_members[j]->introduce();
            fprintf(stdout,"%s\n\n", all_gangs->gangs[i]->name);
        }
    }
}
void show_all_gangs() {
    int n=all_gangs->idx;
    for (int i=0;i<n;i++) {
        fprintf(stdout,"\nGang #%d: %s\n\n",i,all_gangs->gangs[i]->name);
    }
}
void new_user() {
    string name;
    int g,attack,defense,speed;
    gangster*new_recruit;
    if (all_gangs->idx==0) {
        puts("\nCreate a gang first!\n");
    } else {
        puts("\nokay, lets go over their background before recruiting them");
        printf("Enter index to gang they want to join: ");cin>>g;
        if(all_gangs->idx<=g|| g>MAX_GANGS) {
            puts("\nthat gang does not exist!\n");
        } else {
            printf("Enter name of gangster: ");cin>>name;
            printf("Enter Attack Points: ");cin>>attack;
            printf("Enter Defense Points: ");cin>>defense;
            printf("Enter Speed Points: ");cin>>speed;
            if (all_gangs->gangs[g]->idx==0) {//alloc capo
                new_recruit=new capo(name,attack,defense,speed);
            }else {//alloc footman
                new_recruit=new footman(name,attack,defense,speed);
            }
            all_gangs->gangs[g]->gang_members[all_gangs->gangs[g]->idx]=new_recruit;
            all_gangs->gangs[g]->idx++;//increase index of gangsters in gang
        }
    }
}
void new_gang() {
    if (all_gangs->idx>MAX_GANGS) {
        puts("cannot create more gangs!");
    } else {
        char buffer[50];
        fprintf(stdout,"Enter new gang name: ");
        read(0,buffer,50);
        buffer[strcspn(buffer,"\n")]=0;//remove trailing \n
        gang* new_gang = (gang*)malloc(sizeof(gang));
        strncpy(new_gang->name,buffer,50);
        all_gangs->gangs[all_gangs->idx] = new_gang;
        all_gangs->idx++;
    }
}
void free_gang() {
    int gidx=0;
    printf("Enter gang index: ");cin>>gidx;
    if(all_gangs->idx<=gidx) {
        puts("Gang does not exist!");
    }else{
        for(int i=0;i< all_gangs->gangs[gidx] ->idx;i++) {
            delete all_gangs->gangs[gidx]->gang_members[i];
        }
        delete all_gangs->gangs[gidx];// dangle dangle
        all_gangs->idx--;
        all_gangs->gangs[gidx] = NULL;
        puts("\nDeleted Gang!\n");
    }
}
void gang_war() {
    int all_n=all_gangs->idx,i,j,g_memb,strongest,temp=0;// n of gangs in all_gangs
    for(i=0;i<all_n;i++) {
        g_memb=all_gangs->gangs[i]->idx; // n of gang members per gang
        for(j=0;j<g_memb;j++) {
            all_gangs->gangs[i]->power = all_gangs->gangs[i]->gang_members[j]->stats(); // update power
        }
    }
    for (int gang_cx=0;gang_cx<all_n;gang_cx++) { // sort to find largest ; for each gang in all_gangs
        if(temp< all_gangs->gangs[gang_cx]->power) {
            temp=all_gangs->gangs[gang_cx]->power; //store value to check
            strongest=gang_cx; //store index
        }
    }
    cout<< all_gangs->gangs[strongest]->name<<" is victorious!"<<endl;
}
int main(int argc,char**argv) {
    banner();
    int input;
    do {
        puts("[1] Show Gangsters\n[2] Show all Gangs\n[3] Recruit New Gangster\n[4] Start a new gang\n[5] Abolish a gang\n[6] WAR!!");
        fprintf(stdout,"Enter: ");
        cin>>input;
        switch(input){
        case 1:
            show_users();
            break;
        case 2:
            show_all_gangs();
            break;
        case 3:
            new_user();
            break;
        case 4:
            new_gang();
            break;
        case 5:
            free_gang();
            break;
        case 6:
            gang_war();
            break;
        case 7:
            scream_into_the_void();
            break;
        default:
            putchar('\n');
            break;
        }
    }while(1);
}
