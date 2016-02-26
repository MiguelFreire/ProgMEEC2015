#include <stdio.h>
int main(void){

  char c;

  while((c = getchar()) != EOF) {
    if(c == '\n') continue;
    printf("Caracter: %c\n", c);
    printf("Representação decimal: %d\n", (int) c);
  }

  return 0;
}
