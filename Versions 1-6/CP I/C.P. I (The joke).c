#include<stdio.h>
int main(){
  int life, strength, enemy_life, choose;

  life = 1;
  strength = 1;
  enemy_life = 2;

  printf("Welcome to the fighting hole !\n");
  printf("you have %d life points and %d points of attack \n", life, strength);

  printf("You get in the arena, and see your enemy !\n");
  printf(" [Enemy life] = %d\n", enemy_life);
  printf(" [Your life] = %d\n", life);
  printf("You approach your enemy. Now what do you do, attack(1) or evade(2)\n");
  scanf("%d", &choose);

  if (choose <= 1){
    enemy_life = enemy_life - strength;
    printf("You hit your enemy in the face!\n and now he have %d life points left!\n", enemy_life);
    printf("[Enemy life] =%d\n", enemy_life);

   }else if (choose == 2){printf("You evaded your enemy attack!\n");}

    else {printf("You did something stupid, now you are dead...\n"); life = life - 1; printf(" [Your life] = %d\n", life);}
  if (life > 0){
    printf("aaaaaand a meteor came and killed everyone...\n"); life = 0; enemy_life = 0; printf(" [Your life] = 0\n [enemy life] = 0\n");
  }
  printf("The End!");
  return 0;
  }
