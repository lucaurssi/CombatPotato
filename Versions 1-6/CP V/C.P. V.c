#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include"BaseFunctions.h"

/*
        Combat Potato MK.V --> The Tower with save game, highscore and should be finished.
*/

typedef struct savegame{
    char name[20];
    char *race; int race1;
    int level;
    int life;           // save files.
    int damage;
    int floor;
}Save;

typedef struct highscore{
    int score[10];
    char *nome;
}Hs;

int menu(){
    int op;
    printf(" Select an option:\n");
    printf(" 1. New Game\n");
    printf(" 2. Load Game\n");     // initial menu.
    printf(" 3. Highscore\n");
    printf(" 4. Leave\n");          // add highscore option;
    scanf("%d", &op); system("cls");                      ///    <-----    clear tool
    return op;
}

void new_game(Save *slot){
    printf(" Welcome to the tower.\n");
    printf(" Here only the Strong will survive.\n");


    printf(" By which name shall i call you ?\n");
    scanf("%s", slot->name);         //pega o nome.
    system("cls");

    new_race:
    printf(" Choose a race:\n");        //pega a raca do personagem.
    int race;
    printf(" 1. Elf\n");
    printf(" 2. Dwarf\n");
    printf(" 3. Hobbit\n");
    printf(" 4. Human\n");
    printf(" 5. Argonian\n");
    printf(" 6. Khajiit\n");
    scanf("%d", &race);  system("cls");
    switch(race){
        case 1: slot->race = "Elf";
            break;
        case 2: slot->race = "Dwarf";
            break;
        case 3: slot->race = "Hobbit";
            break;
        case 4: slot->race = "Human";
            break;
        case 5: slot->race = "Argonian";
            break;
        case 6: slot->race = "Khajiit";
            break;
        default: printf(" Not a valid option.\n"); goto new_race;
    }
    slot->level = 1;
    slot->floor = 1;
    slot->life = 100;
    slot->damage = 10;

    printf(" You are %s, the %s.\n", slot->name, slot->race);
}

void slots(Save *slot){

    slots:
    printf(" Choose your save slot(only numbers):\n");
    printf(" 1. Slot #1\n");
    printf(" 2. Slot #2\n");
    printf(" 3. Slot #3\n");
    printf(" 4. Back\n");

    int race;

    int choice;
    scanf("%d", &choice); system("cls");
    FILE *p = NULL;
    switch(choice){
        case 1:
            p = fopen("Slot 1.txt", "r");            // should check if exist;

            fscanf(p, "%d", &slot->level); //printf(" %d", slot->level);
            fscanf(p, "%d", &slot->floor); //printf(" %d", slot->floor);
            fscanf(p, "%d", &slot->life);//printf("  %d", slot->life);
            fscanf(p, "%d", &slot->damage);//printf(" %d", slot->damage);
            fscanf(p, "%s", slot->name); //printf(" %s", slot->name);
            fscanf(p, "%d", &race); //printf(" %d", race);
            switch(race){
                case 1: slot->race = "Elf";
                    break;
                case 2: slot->race = "Dwarf";
                    break;
                case 3: slot->race = "Hobbit";
                    break;
                case 4: slot->race = "Human";
                    break;
                case 5: slot->race = "Argonian";
                    break;
                case 6: slot->race = "Khajiit";
                    break;
            }

            break;
        case 2:
            p = fopen("Slot 2.txt", "r");

            fscanf(p, "%d", &slot->level); //printf(" %d", slot->level);
            fscanf(p, "%d", &slot->floor); //printf(" %d", slot->floor);
            fscanf(p, "%d", &slot->life);//printf("  %d", slot->life);
            fscanf(p, "%d", &slot->damage);//printf(" %d", slot->damage);
            fscanf(p, "%s", slot->name); //printf(" %s", slot->name);
            fscanf(p, "%d", &race); //printf(" %d", race);
            switch(race){
                case 1: slot->race = "Elf";
                    break;
                case 2: slot->race = "Dwarf";
                    break;
                case 3: slot->race = "Hobbit";
                    break;
                case 4: slot->race = "Human";
                    break;
                case 5: slot->race = "Argonian";
                    break;
                case 6: slot->race = "Khajiit";
                    break;
            }
            break;
        case 3:
            p = fopen("Slot 3.txt", "r");

            fscanf(p, "%d", &slot->level); //printf(" %d", slot->level);
            fscanf(p, "%d", &slot->floor); //printf(" %d", slot->floor);
            fscanf(p, "%d", &slot->life);//printf("  %d", slot->life);
            fscanf(p, "%d", &slot->damage);//printf(" %d", slot->damage);
            fscanf(p, "%s", slot->name); //printf(" %s", slot->name);
            fscanf(p, "%d", &race); //printf(" %d", race);
            switch(race){
                case 1: slot->race = "Elf";
                    break;
                case 2: slot->race = "Dwarf";
                    break;
                case 3: slot->race = "Hobbit";
                    break;
                case 4: slot->race = "Human";
                    break;
                case 5: slot->race = "Argonian";
                    break;
                case 6: slot->race = "Khajiit";
                    break;
            }
            break;
        case 4: main();
            break;
        default: printf(" Not a valid option.\n"); goto slots;
    }
    fclose(p);
    printf(" Welcome back %s, The %s, lvl %d.", slot->name, slot->race, slot->level);
}

void Highscore(){
    printf(" The Best players are here:\n");
    FILE *p;
    p = fopen("Highscore.txt", "r");
    int n;
    Hs H;
    for(int i=0; i<10; i++){
        fscanf(p, "%d ", &n);
        fscanf(p, "%d %s", &H.score[0], H.nome);
        printf(" %2d.  %4d %s\n", n, H.score[0], H.nome);
    }
    fclose(p);
    printf("\n Write a number than click enter to go back to the menu.\n");
    scanf("%d", &n);
    system("cls");
    main();
}

void stats(Save *slot){
    int n;
    printf(" Status:\n");
    printf(" Name: %s\n", slot->name);
    printf(" Race: %s\n", slot->race);
    printf(" Level: %3d\n", slot->level);
    printf(" HP: %3d", slot->life);
    printf("\n Write a number than click enter to go back to the menu.\n");
    scanf("%d", &n);
    system("cls");
}

void save(Save *slot){
    FILE *p;
    int s;
    printf(" choose a slot to save:\n");
            printf(" 1. slot #1\n 2. slot #2\n 3. slot #3\n 4. Dont save\n");
            scanf("%d", &s);
            switch(s){
                case 1:
                    p= fopen("Slot 1.txt", "w");
                    fprintf(p, "%d \n%d \n%d \n%d \n%s \n", slot->level, slot->floor, slot->life, slot->damage, slot->name);
                    if(slot->race[1]=='l'){
                        slot->race1 = 1;
                    }else if(slot->race[1]=='w'){
                            slot->race1 = 2;
                        }else if(slot->race[1]=='o'){
                                slot->race1 = 3;
                            }else if(slot->race[1]=='u'){
                                    slot->race1 = 4;
                                }else if(slot->race[1]=='r'){
                                        slot->race1 = 5;
                                    }else if(slot->race[1]=='h'){
                                            slot->race1 = 6;
                                        }
                    fprintf(p, "%d\n", slot->race1);
                    break;
                case 2:p= fopen("Slot 2.txt", "w");
                    fprintf(p, "%d \n%d \n%d \n%d \n%s \n", slot->level, slot->floor, slot->life, slot->damage, slot->name);
                    if(slot->race[1]=='l'){
                        slot->race1 = 1;
                    }else if(slot->race[1]=='w'){
                            slot->race1 = 2;
                        }else if(slot->race[1]=='o'){
                                slot->race1 = 3;
                            }else if(slot->race[1]=='u'){
                                    slot->race1 = 4;
                                }else if(slot->race[1]=='r'){
                                        slot->race1 = 5;
                                    }else if(slot->race[1]=='h'){
                                            slot->race1 = 6;
                                        }
                    fprintf(p, "%d\n", slot->race1);
                    break;
                case 3:p= fopen("Slot 3.txt", "w");
                    fprintf(p, "%d \n%d \n%d \n%d \n%s \n", slot->level, slot->floor, slot->life, slot->damage, slot->name);
                    if(slot->race[1]=='l'){
                        slot->race1 = 1;
                    }else if(slot->race[1]=='w'){
                            slot->race1 = 2;
                        }else if(slot->race[1]=='o'){
                                slot->race1 = 3;
                            }else if(slot->race[1]=='u'){
                                    slot->race1 = 4;
                                }else if(slot->race[1]=='r'){
                                        slot->race1 = 5;
                                    }else if(slot->race[1]=='h'){
                                            slot->race1 = 6;
                                        }
                    fprintf(p, "%d\n", slot->race1);
                    break;
                case 4:
                    break;
            }
}

void rest(Save *slot){
    printf(" You look around and feel like you could rest for a while.\n");
    int sorte;
    sorte = random(100);
    if(sorte>49){
        printf(" By resting for a few minutes you regain some energy.\n");
        printf(" HP: %d + %d", slot->life, 5+random(20));            ///the hp is not adding up <-- *
    }else {
         printf(" While you were sleeping a monster approached.\n");
         //combat;
     }
}

void game(Save *slot){
    printf(" The floor is %d,\n You can feel the presence of monsters in the path ahead.\n", slot->floor);
    int free_time;

    nothing:
    printf(" What shall you do ?\n");
    printf(" 1. Move ahead to the next open space(not ready)\n");
    printf(" 2. Use something from your inventary(not ready)\n");
    printf(" 3. take your time and rest\n");
    printf(" 4. Check your status window\n");
    printf(" 5. Save and leave\n");
    scanf("%d", &free_time); system("cls");

    switch(free_time){
        case 1: printf("move");
            break;
        case 2: printf("inventary");
            break;
        case 3: rest(slot);
            goto nothing;
            break;
        case 4:
            stats(slot);
            goto nothing;
            break;
        case 5:
            save(slot); system("cls"); main();
            break;
    }

}

int main(){
    Save slot;
    int opc;
    firstmenu:
    opc = menu();
    srand(time(NULL));

    switch(opc){
        case 1:
            new_game(&slot);
            game(&slot);
            break;
        case 2:
            slots(&slot);
            game(&slot);
            break;
        case 3:
            Highscore();
            break;
        case 4:  exit(0); //close the game.
            break;
        default: printf(" Not a valid option.\n"); goto firstmenu;
    }

    return 0;
}
