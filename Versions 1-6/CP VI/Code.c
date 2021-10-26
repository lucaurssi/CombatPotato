#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<math.h>


/*
  =========To do list==========

  * Balancear o combate
  * aplicar variacao de dano em monstros
  * Mais eventos
  * Itens
      |* consumiveis
  * Finalizar o boss

  =============================
*/

typedef struct{
    char name[20];
    int level;
    int Hp, Max_Hp;
    int Mp, Max_Mp;
    int Xp, Max_Xp;

    int Arma, A_variacao; // dano da arma; (weapon)
    int defesa;

}Stats;

typedef struct{
    char *name;
    int level;
    int Hp, Max_Hp;
    int Mp, Max_Mp;
    int St;
    int defesa;
}Monster;

typedef struct{
    int x, y, Sx, Sy; // x, y e seus tamanhos maximos.
    char **xy;
    int floor;
    int floor_progress;
}Mapa;

void mapping(Mapa* m);
void firstStep(Stats* p, Mapa* m);
void save(Stats *p, Mapa *m);
int load(Stats *p, Mapa *m);
int random(int n);
void GenerateMonster(int aux, Stats* p, Mapa* m, Monster* z);
void newgame(Stats* p, Mapa* m);
void Event(Stats* p, Mapa* m, Monster *z);
void levelUp(Stats* p);
int A_v(Stats *p);
void Combat(int aux, Stats* p, Mapa* m, Monster* z);
void CombatEvent(Stats* p, Mapa* m, Monster* z);
void combat_boss(Stats *p, Mapa *m, Monster *z);
void boss(Stats *p, Mapa *m, Monster *z);
void nextStep(Stats* p, Mapa* m, Monster* z);
void MapView(Mapa* m);
void moveAround(Stats* p, Mapa* m, Monster* z);
void Status(Stats* p);
void Game(Stats* p, Mapa* m, Monster* z);

void save(Stats *p, Mapa *m){
    int aux, aux2;
    FILE *S;
    while(1){
        printf("Choose a slot to save.\n");
        printf("1. slot1\n2. slot2\n3. slot3\n4. back\n");
        scanf("%d", &aux); system("cls");
        if(aux == 1)
            S = fopen("slot1.txt", "r");
        else if(aux == 2)
            S = fopen("slot2.txt", "r");
        else if(aux == 3)
            S = fopen("slot3.txt", "r");
        else return;

        if(S != NULL){
            printf("There is already a savegame in this slot.\n");
            printf("Do you want to overwrite it ?\n");
            printf("1. Yes\n2. No\n");
            fclose(S);

            if(scanf("%d", &aux2) == 1){
                system("cls");
                if(aux == 1)
                    S = fopen("slot1.txt", "w");
                else if(aux == 2)
                    S = fopen("slot2.txt", "w");
                else if(aux == 3)
                    S = fopen("slot3.txt", "w");

                fprintf(S, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d", p->name, p->level, p->Hp, p->Max_Hp, p->Mp, p->Max_Mp, p->Xp, p->Max_Xp, p-> Arma, p->A_variacao, p->defesa, m->x, m->y, m->floor, m->floor_progress); /* dados */
                for(int i=0; i<m->Sx; i++)
                    for(int j=0; j<m->Sy; j++)
                        fprintf(S, "%c", m->xy[i][j]);
                fclose(S);
                return;
            }
        }else{
            system("cls");
            fclose(S);
            if(aux == 1)
                S = fopen("slot1.txt", "w");
            else if(aux == 2)
                S = fopen("slot2.txt", "w");
            else if(aux == 3)
                S = fopen("slot3.txt", "w");

            fprintf(S, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d", p->name, p->level, p->Hp, p->Max_Hp, p->Mp, p->Max_Mp, p->Xp, p->Max_Xp, p-> Arma, p->A_variacao, p->defesa, m->x, m->y, m->floor, m->floor_progress); /* dados */
            for(int i=0; i<m->Sx; i++)
                for(int j=0; j<m->Sy; j++)
                    fprintf(S, "%c", m->xy[i][j]);
            fclose(S);
            return;
        }
    }
}

int load(Stats *p, Mapa *m){
    int aux;
    char v[200];
    FILE *S;
    while(1){
        printf("Choose a slot to load.\n");
        printf("1. slot1\n2. slot2\n3. slot3\n4. back\n");
        scanf("%d", &aux); system("cls");

        if(aux == 1)
            S = fopen("slot1.txt", "r");
        else if(aux == 2)
            S = fopen("slot2.txt", "r");
        else if(aux == 3)
            S = fopen("slot3.txt", "r");
        else return 0;

        if(S == NULL){
            printf("There is nothing in slot%d.\n", aux);
            fclose(S);
        }else{
            if(aux == 1)
                S = fopen("slot1.txt", "r");
            else if(aux == 2)
                S = fopen("slot2.txt", "r");
            else if(aux == 3)
                S = fopen("slot3.txt", "r");

            firstStep(p, m);

            fscanf(S ,"%s", p->name);
            fscanf(S, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d", &p->level, &p->Hp, &p->Max_Hp, &p->Mp, &p->Max_Mp, &p->Xp, &p->Max_Xp, &p-> Arma, &p->A_variacao, &p->defesa, &m->x, &m->y, &m->floor, &m->floor_progress); /* dados */
            fscanf(S, "%s",  v);

            for(int i=0; i<m->Sx; i++)
                for(int j=0; j<m->Sy; j++)
                    m->xy[i][j] = v[(i*m->Sy)+ j];

            fclose(S);
            return 1;
        }
    }
}

int random(int n){
    return rand()%n;
}

void mapping(Mapa* m){
    // coloca o mapa todo em modo incognito.
    m->floor_progress = 0; // contador de salas visitadas.
    for(int i=0; i<m->Sx; i++){
        for(int j=0; j<m->Sy; j++){
            m->xy[i][j] = 63; // '?' na tabela ask.
        }
    }
    m->xy[m->x][m->y] = 64; // coloca '@' na posi��o do personagem.
}

void firstStep(Stats* p, Mapa* m){
    // escolhe lugar aleat�rio para posicionar o jogador.
    m->Sx = 5;      // tamanho do mapa.
    m->Sy = 10;
    m->x = random(m->Sx);   // seleciona posi��o aleat�ria.
    m->y = random(m->Sy);
    m->xy = (char**)malloc(sizeof(char*)*m->Sx);    // pega espa�o para o mapa.
    for(int i=0; i<m->Sx; i++){
        m->xy[i] = (char*)malloc(sizeof(char)*m->Sy);
    }
}

void newgame(Stats* p, Mapa* m){
    printf("Welcome, what's your name ?\n");
    scanf("%s", p->name); system("cls");
    printf("%s, ...\n", p->name);
    printf("Well that is the first time I hear such weird name\n");
    printf("So... let's go with it\n");
    printf("Here take this,\n");
    printf("* You got a sword *\n");
    printf("It may help you with whats is coming next\n");
    printf("And good Luck mate, you will need it\n\n");

    p->level = 1;
    p->Max_Hp = 10;
    p->Max_Mp = 10;
    p->Max_Xp = 10;     /* inicia valores para um personagem level 1 */
    p->Hp = p->Max_Hp;
    p->Mp = p->Max_Mp;
    p->Xp = 0;
    p->Arma = 1;
    p->A_variacao = 3;
    m->floor = 1;
    m->xy = NULL;
    p->defesa = 0;
    firstStep(p, m);
    mapping(m);
}

void Event(Stats* p, Mapa* m, Monster *z){ /* 30% */
    int aux = random(100);
    int a=0, b=0;
/* nothing */
    if(aux < 5)
        printf("A tiny rock fall on the ground...yep, nothing interesting here.\n");

/* NPC stuff */
    else if(aux < 20){
        aux = random(100);
        if(aux < 10)
            printf("A green dude look at you for a few seconds and run away...\n"); // NPC
        else if(aux < 40){
            printf("You watch some monsters fighting each other from a safe place,\n by watching you learn how to counter then. +1 to attacks\n");
            p->Arma++;
        }else if(aux < 60)
            printf("There is a lot of bones here, this is a bad sign...\n");
        else{
            printf("You feel eyes on your back,\nyou turn around but there is no one there.\n");
        }
    }

/* bonus Stats */
    else if(aux < 40){
        if(random(100) < 50){   /* damage */
            aux = random(100);
            if(aux < 20){
                p->Arma++; a= 1;
                p->A_variacao++; b=1;
            }
            else if(aux < 60){
                p->Arma++;
                a=1;
            }
            else {
                p->A_variacao++;
                b=1;
            }
            printf("You got touched by something warm, +(%d-%d) Damage\n", a, a+b);
        }else{    /* life */
            printf("You step on something mushy, +1 max life, don't question it...\n");
            p->Max_Hp++;
            p->Hp++;
        }

/* fountain */
    }else if(aux < 65){
        aux = random(5);
        int aux17 = 1, aux18;

        printf("You found a ");
        switch(aux){
            case 0: printf("blue");
                break;
            case 1: printf("green");
                break;
            case 2: printf("red");
                break;
            case 3: printf("yellow");
                break;
            case 4: printf("orange");
                break;
        }
        printf(" fountain, ");
        while(aux17){
            printf("What do you do ?\n");
            printf(" 1. Drink from it.\n");
            printf(" 2. Drop a rock at it.\n");
            printf(" 3. Touch it.\n");
            printf(" 4. Leave it.\n");

            scanf("%d", &aux18); system("cls");
            switch(aux18){
                case 1:
                    if(random(3)<= 1){
                        printf("You feel refreshed, +5 Hp\n");
                        p->Hp += 5; if(p->Hp > p->Max_Hp) p->Hp = p->Max_Hp;
                    }else{
                        printf("It wasn't a good thing to drink, -7 Hp\n");
                        p->Hp -= 7;
                    }
                case 4:
                    aux17 = 0;
                    break;
                case 2:
                case 3:
                default:
                    printf("Nothing interesting happens.");
            }
        }

/* Traps */
    }else if(aux < 75){  /** 5% */
        aux = random(100);
        if(aux < 20){ /* 20% */
            printf("A boulder comes rouling in your direction, -15 HP\n");
            p->Hp -= 15;
        }else if(aux < 40){ /* 20% */
            printf("You step on a pressure plate and some darts comes from the wall, -6 HP\n");
            p->Hp -= 6;
        }else{ /* 60% */
            printf("You break a thin line with your step, and a crossbow, hidden in the wall, shoot at you, -7 HP\n");
            p->Hp -= 7;
        }

/* Mimics */
    }else{
        printf("You found a chest, it looks old. Do you want to open it ?\n");
        printf("1. Yes\n2. No\n");
        scanf("%d", &aux); system("cls");
        if(aux == 1){
            if(random(2)){ // Mimics
                Combat(-1, p, m, z);
            }else{
                aux = random(5);
                if(aux == 0){
                    printf("Smoke comes out of the old chest.\n");
                    printf("The smoke seems to heal your wounds. There's nothing left on the chest.\n");
                    p->Hp = p->Max_Hp;
                }else if(aux == 1){
                    printf("Smoke comes out of the old chest.\n");
                    printf("The smoke is toxic your current health is halved. The chest is empty now.\n");
                    p->Hp = p->Hp/2;
                }else if(aux == 2){
                    printf("There is an essence of might in there, +1 to your attacks.\n");
                    p->Arma++;
                }else if(aux == 3){
                    printf("A blue slimy thing fly to your nose, +1 Mp.\n");
                    p->Max_Mp++; p->Mp++;
                }else
                    printf("The chest is empty, nothing to look at.\n");
            }
        }
    }
}

void GenerateMonster(int aux, Stats* p, Mapa* m, Monster* z){
    z->level = m->floor;
    z->Max_Hp = z->level*10;
    z->Hp = z->Max_Hp;
    z->Max_Mp = z->Max_Hp;
    z->Mp = z->Max_Mp;
    z->St = 2*z->level;
    z->defesa = z->level -1;

    int aux2 = random(10);
    if(aux == 1){
        z->Hp *= 1.5;
        z->Max_Hp *= 1.5;
        z->Mp *= 1.5;
        z->Max_Mp *= 1.5;
        z->St *= 2;
        z->defesa = z->level;
        switch(aux2){
            case 1: z->name = (char*)"Big Slime";
                break;
            case 2: z->name = (char*)"Big Zombie";
                break;
            case 3: z->name = (char*)"Crazy Ghoul";
                break;
            case 4: z->name = (char*)"Skeletron";
                break;
            case 5: z->name = (char*)"White Ghost";
                break;
            case 6: z->name = (char*)"Hobgoblin";
                break;
            case 7: z->name = (char*)"Hairy Spider";
                break;
            case 8: z->name = (char*)"Big Snake";
                break;
            case 9: z->name = (char*)"Rat King";
                break;
            case 0: z->name = (char*)"really weird Dude";
                break;
        }
    }else if(aux == 0){
        switch(aux2){
            case 1: z->name = (char*)"Slime";
                break;
            case 2: z->name = (char*)"Zombie";
                break;
            case 3: z->name = (char*)"Ghoul";
                break;
            case 4: z->name = (char*)"Skeleton";
                break;
            case 5: z->name = (char*)"Ghost";
                break;
            case 6: z->name = (char*)"Goblin";
                break;
            case 7: z->name = (char*)"Spider";
                break;
            case 8: z->name = (char*)"Snake";
                break;
            case 9: z->name = (char*)"Rat";
                break;
            case 0: z->name = (char*)"Weirdo";
                break;
        }
    }else{
        z->Hp *= 2.5;
        z->Max_Hp *= 2.5;
        z->Mp *= 2.5;
        z->Max_Mp *= 2.5;
        z->St *= 3;
        z->defesa = z->level*2;
        switch(aux2){
            case 1: z->name = (char*)"King Slime";
                break;
            case 2: z->name = (char*)"Giant Zombie";
                break;
            case 3: z->name = (char*)"Berserker Ghoul";
                break;
            case 4: z->name = (char*)"The Skeletron";
                break;
            case 5: z->name = (char*)"Wraith";
                break;
            case 6: z->name = (char*)"Orc";
                break;
            case 7: z->name = (char*)"Giant Spider";
                break;
            case 8: z->name = (char*)"Giant Anaconda";
                break;
            case 9: z->name = (char*)"Giant Rat";
                break;
            case 0: z->name = (char*)"A hairy and really creepy guy";
                break;
        }
    }
}

void levelUp(Stats* p){
    while(p->Xp >= p->Max_Xp){ // check for possible level up (multiple times if necessary)
        p->Xp -= p->Max_Xp;
        p->Max_Xp = (int)(p->Max_Xp *1.5);
        p->level++;
        p->Max_Hp+= 2;
        printf("\nHp +2\n");
        p->Hp = p->Max_Hp;
        p->Max_Mp+= 2;
        printf("Mp +2\n");
        p->Mp = p->Max_Mp;
        p->Arma++;
        printf("Dmg +1\n");
        int aux = random(2);
        if(aux > 0) printf("Def +%d\n", aux);
        p->defesa += aux;

        printf("You leved up !!\n\n");
    }
}

int A_v(Stats *p){ // arma variacao
    return p->Arma + (rand()%p->A_variacao);
}

void Combat(int aux, Stats* p, Mapa* m, Monster* z){
    int aux2 = 0;
	int vet = aux;
    if(aux == 1)
        printf("There is a veteran monster here.\n");
    else
        printf("There is a monster in this room.\n");
    if(vet == -1) aux = 0;
    GenerateMonster(aux, p, m, z);

    if(vet == -1)z->name = (char*)"Mimic";
    printf("it's a %s.\n", z->name);
    if(vet != -1){
        printf("what do you want to do ?\n");
        printf("1. fight it\n");
        printf("2. run\n");

        printf("\n");
        scanf("%d", &aux); system("cls");
    }else{
        aux = 1;

    }
    switch(aux){
        case 1: /* fight it */
            if(vet != -1)printf("You decided to fight !!\n");
            else vet++;

            while(p->Hp >0 && z->Hp > 0){
                printf("\n");
                printf("[%s's life] : %d/%d\n", z->name, z->Hp, z->Max_Hp);
                printf("[Your life] : %d/%d\n", p->Hp, p->Max_Hp);
                printf("\n");

                printf("What's your move ?\n");
                printf("1. Attack (%d - %d)\n", p->Arma, p->Arma+p->A_variacao-1);
                printf("2. Strong Attack (%d - %d) (70 acc)\n", p->Arma*2, (p->Arma+p->A_variacao-1)*2);
                printf("3. Run away\n");
                /* use item, magic, run */
    /***/
                scanf("%d", &aux); system("cls");

                switch(aux){
                    case 1: /* falta calibrar a evas�o enimiga */
                        aux = A_v(p) - z->defesa;
                        printf("You attack %s for %d of damage\n", z->name, aux);
                        z->Hp -= aux;
                        break;
                    case 2:
                        if(random(100) < 70){ // 70%
                            aux = (A_v(p)*2) - z->defesa;
                            printf("You do a strong attack on %s for %d of damage\n", z->name, aux);
                            z->Hp -= aux;
                        }else
                            printf("Your attack failed ...\n");
                        break;
                    case 3:
                        if(random(100) < 51){
                            z->Hp = 0;
                            aux2 = 1;
                        }else
                            printf("You couldn't run from it ...\n");
                        break;
                }
                if(z->Hp <= 0) // check enemy life
                    break;  // enemy attack

                if(z->St > p->defesa) // enemy atack
                  aux = z->St - p->defesa;
                else
                  aux = 0;
                printf("%s attacks you for %d damage\n", z->name, aux);
                p->Hp -= aux;

                if(p->Hp <= 0) // check if player died
                  break;
            }
            if(aux2 == 0)
                if(z->Hp <= 0){
                    printf("You killed %s, earning %d Xp.\n", z->name, m->floor*10*(vet+1));
      						  p->Xp += m->floor*10*(vet+1);
                    levelUp(p);
                }else
                    printf("You were killed by the %s\n", z->name);
            else
                printf("You ran away !\n");
            break;

        case 2: /* run */
            if(random(100) <= 10){ /* 10% chance of fail when running away */
              printf("You didn't run far enough,\nthe enemy take the first hit !\n");

              while(p->Hp >0 && z->Hp > 0){
                  printf("\n");
                  printf("[%s's life] : %d/%d\n", z->name, z->Hp, z->Max_Hp);
                  printf("[Your life] : %d/%d\n", p->Hp, p->Max_Hp);
                  printf("\n");

                  printf("What's your move ?\n");
                  printf("1. Attack (%d - %d)\n", p->Arma, p->Arma+p->A_variacao-1);
                  printf("2. Strong Attack (%d - %d) (70 acc)\n", p->Arma*2, (p->Arma+p->A_variacao-1)*2);
                  printf("3. Run away\n");
                  /* use item, magic, run */
      /***/
                  scanf("%d", &aux); system("cls");

                  switch(aux){
                      case 1: /* falta calibrar a evas�o enimiga */
                          aux = A_v(p) - z->defesa;
                          printf("You attack %s for %d of damage\n", z->name, aux);
                          z->Hp -= aux;
                          break;
                      case 2:
                          if(random(100) < 70){ // 70%
                              aux = (A_v(p)*2) - z->defesa;
                              printf("You do a strong attack on %s for %d of damage\n", z->name, aux);
                              z->Hp -= aux;
                          }else
                              printf("Your attack failed ...\n");
                          break;
                      case 3:
                          if(random(100) < 51){
                              z->Hp = 0;
                              aux2 = 1;
                          }else
                              printf("You couldn't run from it ...\n");
                          break;
                  }
                  if(z->Hp <= 0) // check enemy life
                      break;  // enemy attack

                  if(z->St > p->defesa) // enemy atack
                    aux = z->St - p->defesa;
                  else
                    aux = 0;
                  printf("%s attacks you for %d damage\n", z->name, aux);
                  p->Hp -= aux;

                  if(p->Hp <= 0) // check if player died
                    break;
              }
              if(aux2 == 0)
                  if(z->Hp <= 0){
                      printf("You killed %s, earning %d Xp.\n", z->name, m->floor*10*(vet+1));
        						  p->Xp += m->floor*10*(vet+1);
                      levelUp(p);
                  }else
                      printf("You were killed by the %s\n", z->name);
              else
                  printf("You ran away !\n");
            }
            break;
    }
}

void CombatEvent(Stats* p, Mapa* m, Monster* z){
    int aux = random(100);
    if(aux <20){
        Combat(1, p, m, z);    /** Veteran 20% */
    }else {
        Combat(0, p, m, z);    /** normal monster 80% */
    }
}

void combat_boss(Stats *p, Mapa *m, Monster *z){
    int aux2;
    GenerateMonster(2, p, m, z);
    printf("\n");
    printf("[%s's life] : %d\n", z->name, z->Max_Hp);
    printf("[Your life] : %d/%d\n", p->Hp, p->Max_Hp);
    while(p->Hp >0 && z->Hp > 0){
        aux2 = A_v(p);
        printf("You attack %s for %d of damage\n", z->name, aux2);
        z->Hp -= aux2;
        if(z->Hp <= 0)
            break;
        printf("%s attacks you for %d of damage\n", z->name, z->St);
        p->Hp -= z->St;
        if(p->Hp <= 0)
            break;
    }
    if(z->Hp <= 0){
        printf("You killed %s, earning %d Xp.\n", z->name, m->floor*100);
        p->Xp += m->floor*100;
        levelUp(p);
        printf("You were teleported to the next floor\n");
        mapping(m); // reset the map
        m->x = random(m->Sx);   // seleciona posi��o aleat�ria.
        m->y = random(m->Sy);
        m->floor++;
    }else
        printf("You were killed by the %s\n", z->name);

}

void boss(Stats *p, Mapa *m, Monster *z){
    printf("You killed every monster on this floor, by doing that\n");
    printf("a big door apears in front of you, you rest for a few minutes\n");
    printf("to regain your heath and open the door.\n");
    p->Hp = p->Max_Hp;
    p->Mp = p->Max_Mp;
    printf("It's the boss room, the door closes behind you!!\n");
    combat_boss(p, m, z);
}

void nextStep(Stats* p, Mapa* m, Monster* z){ // define what happens after moving.
    int aux;
    if(m->xy[m->x][m->y]==63){  // if '?'.
        m->floor_progress++;
        aux = random(100);
        if(aux < 50){         /** combat 50%  */
            CombatEvent(p, m, z);
        }else if(aux < 55){   /** nothing 5% */
            printf("Nothing in this room!\n");
        }else{
            Event(p, m, z);  /** Event 45% */    // random events.
        }
    }else if(m->xy[m->x][m->y]==48){    // se for '0'.
        printf("you alredy passed here, so nothing is here right now.\n");
    }
    m->xy[m->x][m->y]= 64; // nova posi��o recebe '@'.
    if(m->floor_progress >= (m->Sx*m->Sy-1)/2) // se ja tiver visitado todas as salas
        boss(p, m, z);
}

void MapView(Mapa* m){

    for(int i=0; i<m->Sx; i++){
        for(int j=0; j<m->Sy; j++){
            printf("%c",m->xy[i][j]);
        }
        printf("\n");
    }
}

void moveAround(Stats* p, Mapa* m, Monster* z){
    int aux, aux2=1;
    printf("Where do you want to move ?\n");
    while(aux2 == 1){
            aux2--;
        if(m->x != 0)
            printf("1. North\n");
        if(m->y != 0)
            printf("2. West\n");
        if(m->x != m->Sx-1)
            printf("3. South\n");
        if(m->y != m->Sy-1)
            printf("4. East\n");
        scanf("%d", &aux); system("cls");
        switch(aux){
            case 1:
                if(m->x != 0){
                    m->xy[m->x][m->y]= 48;
                    m->x--;
                    nextStep(p, m, z);
                }else printf("You can't go this way!\n");
                break;
            case 2:
                if(m->y != 0){
                    m->xy[m->x][m->y]= 48;
                    m->y--;
                    nextStep(p, m, z);
                }else printf("You can't go this way!\n");
                break;
            case 3:
                if(m->x != m->Sx-1){
                    m->xy[m->x][m->y]= 48;
                    m->x++;
                    nextStep(p, m, z);
                }else printf("You can't go this way!\n");
                break;
            case 4:
                if(m->y != m->Sy-1){
                    m->xy[m->x][m->y]= 48;
                    m->y++;
                    nextStep(p, m, z);
                }else printf("You can't go this way!\n");
                break;
            default: printf("Nope, that is not working try one of the numbers bellow.\n"); aux2++;
        }
    }
}

void Status(Stats* p){
    printf("N. : %s\n", p->name);
    printf("Lvl: %d\n", p->level);
    printf("Hp : %d/%d\n", p->Hp, p->Max_Hp);
    printf("Mp : %d/%d\n", p->Mp, p->Max_Mp);
    printf("Xp : %d/%d\n", p->Xp, p->Max_Xp);
    printf("Dmg: %d-%d\n", p->Arma, p->Arma+p->A_variacao-1);
    printf("Def: %d\n\n", p->defesa);

}

void Game(Stats* p, Mapa* m, Monster* z){
    while(p->Hp >0){
        MapView(m);
        printf("what's next ?\n");
        printf(" 1. Move around.\n");
        printf(" 2. Rest and heal.\n");
        printf(" 3. Stats.\n");
        printf(" 4. Save.\n");
        printf(" 5. Exit the Menu.\n");
        int aux;
        scanf("%d", &aux); system("cls");
        switch(aux){
            case 1:
                MapView(m); // print the map
                moveAround(p, m, z); // move to another square.
                break;
            case 2:
                aux = random(100);
                if(aux<10){
                    printf("While you were resting a monster apeared.\n");
                    Combat(0, p, m, z);
                }else{
                    aux= 2+random(5);
                    printf("You manage to rest for a bit, restoring %d heath points.\n", aux);
                    p->Hp += aux;
                    if(p->Hp > p->Max_Hp)
                        p->Hp = p->Max_Hp;
                }

                break;
            case 3:
                Status(p);
                break;
            case 4:
                save(p, m);
                break;
            case 5:
                for(int i=0; i<m->Sx; i++){
                    free(m->xy[i]);
                }
                free(m->xy);
                return;
                break;
            default: printf("Nope, try another number.\n");
        }
    }
    printf("You died, Game Over!\n\n");
}

int main(){
    srand(time(NULL));
    Stats p;    /// perfil do jogador.
    Mapa m;     /// informa��es do mapa.
    Monster z;  /// perfil do monstro.

    while(1){
        printf("    *MENU*\n");
        printf("1. New Game\n");
        printf("2. Load Game\n");
        printf("3. Exit Game\n");
        int aux5;
        scanf("%d", &aux5); system("cls"); getchar(); ///getchar pega um \n que estava atrapalhando
        switch(aux5){
            case 1:
                newgame(&p, &m);    /// cria um personagem com uma pequena introdu��oo.
                Game(&p, &m, &z);     /// fun��o generica de a��o pr�/p�s outras a��es.
                break;
            case 2:
                if(load(&p, &m))
                    Game(&p, &m, &z);
                break;
            case 3:
                exit(0);
                break;
        }
    }
    exit(0);
}
