#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
/*
 The coding of this version was aborted by the lack of time and
 the large amount of new tools discovered, making all this
 useless and outdated. The next version should make up for it.
*/




int random(int x){
    return rand()%x;
}


int main(){
    srand(time(NULL));



int game(){
    int room[100];
    int room_atual=0;

    while(1){
    room_atual=random(100);
    if(room[room_atual]!=3){ break; }
    }
    room[room_atual]=0;

    int map(){
         srand(time(NULL));

    for(int i=0; i<100; i++){
        room[i]=random(2);
    }
    for(int i=0; i<100; i++){
        if(room[i]==0){
            room[i]=random(3);
        }
    }
    for(int i=0; i<100; i++){
        if(room[i]==0 && random(3)==1){
            room[i]= 3; break;
        }
    }}

    map();
    srand(time(NULL));
    int r;
    printf(" Choose your race:\n");
    printf(" 1. Elf\n");
    printf(" 2. Dwarf\n");
    printf(" 3. Human\n");
    printf(" 4. Hobbit\n");

    scanf("%d", &r);

    char race[6];
    switch(r){
        case 1: race[0] = 'E';race[1] = 'l';race[2] = 'f';
        break;
        case 2: race[0] = 'D';race[1] = 'w';race[2] = 'a';race[3] = 'r';race[4] = 'f';
        break;
        case 4: race[0] = 'H';race[1] = 'o';race[2] = 'b';race[3] = 'b';race[4] = 'i';race[5] = 't';
        break;
        case 3: race[0] = 'H';race[1] = 'u';race[2] = 'm';race[3] = 'a';race[4] = 'n';
        break;
    }

    int floor=1, level=1;

    printf("\n You are a level %d %s .\n", level, race);

    for(int i=0; i<100; i++){
    printf(" You just entered the floor %d\n\n", floor);

    srand(time(NULL));

    char move;
    printf(" There is no Immediate danger around you, what do you want to do ?\n");
    printf(" 1. Try to rest a little. (recover some HP)\n");
    printf(" 2. Move to another place.\n");
    scanf("%s", &move);

    int truth=1, truth2=1;
    while(truth==1){

        switch(move){
        case '1': truth=0;//heal HP / MP. with the event chance.
            break;
        case '2':
                truth=0;

                while(truth2==1){
                        truth2=0;
                    printf(" Choose the direction.\n");
                    printf(" 1. North\n");
                    printf(" 2. West\n");
                    printf(" 3. South\n");
                    printf(" 4. East\n");
                    scanf("%s", &move);


                    switch(move){
                    case '1':
                        if((room_atual%10)==0){
                                printf(" you can't go on that diraction...\n");
                                break;} //north
                        room_atual-=1;
                        break;
                    case '2':
                        if((room_atual-10)<0){
                                printf(" you can't go on that diraction...\n");
                                break;}//west
                        room_atual-=10;
                        break;
                    case '3':
                        if(((room_atual-9)%10)==0){
                                printf(" you can't go on that diraction...\n");
                                break;}//south
                        room_atual+=1;
                        break;
                    case '4':
                        if((room_atual+10)>=0){
                                printf(" you can't go on that diraction...\n");
                                break;}//east
                        room_atual+=10;
                        break;
                    default: printf("try another button...\n"); truth2=1;
                    }
                }
            break;
        default:printf("try another button ...\n");
        }}







    //combat/event.



    }
}

    char menu;

    printf(" Welcome to the Tower.\n");
    while(1){
        printf(" Menu:\n");
        printf(" 1. Start the game \n");
        printf(" 2. Close the game \n");
        scanf("%s", &menu);

        switch(menu){
            case '1':
                game();

                break;
            case '2':
                return 0;
            default: printf("try another button ...\n");
        }
    }
      return 0;
}
