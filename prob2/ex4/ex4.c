#include <stdio.h>

int main(void) {
  int n,i,j,blank;
  printf("Altura do triangulo?\n");
  scanf("%d", &n);
  for (i=n; i >= 1; i--) { 
    for(blank=0; blank < n-i;blank++) printf("  ");
    for(j=i; j<=2*i-1; j++) printf("* ");
    for(j=0; j<i-1;j++) printf("* ");
    printf("\n");

  }
  return 0;
}
