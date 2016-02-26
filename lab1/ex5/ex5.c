#include <stdio.h>


#define VSOM 340

int main(void){

  int t,d;
  printf("Intervalo entre o relapango e o trovão em segundos?\n");
  scanf("%d", &t);
  d = VSOM * t;
  printf("Distância à trovoada: %d m\n", d);

  return 0;
}
