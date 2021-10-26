#include<stdio.h>
#include<stdlib.h>
int main(){
  int life, strength, enemy_life, enemy_strength, evade, choose, attack, enemy_balance, balance;

  balance = 1;
  enemy_balance = 1;
  attack = 0;
  evade = 0;
  life = 10;
  strength = 2;
  enemy_life = 10;
  enemy_strength = 2;


  printf("Welcome to the CombatPotato Mk.II !\n");
  printf("you have %d life points and %d points of attack \n", life, strength);
  printf("You get in the arena, and see your enemy !\n");

  printf("\n#\n\n [Enemy life] = %d\n", enemy_life);
  printf(" [Your life] = %d\n", life);


   while (life > 0 && enemy_life > 0){


  if (enemy_balance == 0){
    printf("you take advantage of your enemy's mistake!!\n");
    enemy_life = enemy_life - strength;
    enemy_balance = 1;
    printf(" [enemy life] = %d\n", enemy_life);
  }else{
        printf("Choose, attack(1) or evade(2):\n");
        scanf("%d", &choose);


  if (choose <= 1){
    attack = 1;
    evade = 0;
    enemy_life = enemy_life - strength;
    printf("You hit your enemy in the face!!\n");
    printf(" [enemy life] = %d\n", enemy_life);

   }else if (choose == 2){
       attack = 0;
       evade = 1;
       printf("You evaded your enemy attack!\n");}

       else {
            printf("You did something stupid, lose 1 life point.\n");
       life = life - 1;
       printf(" [Your life] = %d\n", life);}

  if (enemy_life > 0){
     if (evade == 0){
     printf("\nthe enemy attacks you !!\n");
     life = life - enemy_strength;
     printf(" [Your life] = %d\n", life);

    } else if (evade == 1){
     printf("the enemy miss his attack on you and lose his balance!!\n");
     enemy_balance = 0;
     evade = 0;
    }}}}


  if (life > 0){
    printf("You won !!");
  }
   else if (enemy_life > 0){
    printf("You lose!!");
   }else {printf("it's a draw !!");}
  printf("\nThe End!\n\n");
  return 0;
  }
