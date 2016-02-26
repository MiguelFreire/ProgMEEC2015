#include <stdio.h>


int main(void){

  int divisor, dividendo, quociente, resto;



  printf("Escreva o dividendo:\n");
  scanf("%d", &dividendo);

  printf("Escreva o divisor:\n");
  scanf("%d", &divisor);


  while(divisor == 0) {
    printf("Divisor igual a 0 escreva outro:\n");
    scanf("%d\n", &divisor);
  }

  quociente = dividendo / divisor;
  resto = divisor % dividendo;

  printf("Quociente: %d\n", quociente);
  printf("Resto: %d\n", resto);
  return 0;
}
