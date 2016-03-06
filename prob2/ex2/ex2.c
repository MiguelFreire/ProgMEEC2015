#include <stdio.h>

int main(void) {
  int n;
  int d = 0;
  static int sum;
  int divisores[10];
  printf("Número:");
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    if(n%i == 0) {
      printf("I: %d D: %d\n", i,d);
      divisores[d] = i;
      d++;
    }
  }

  for(int k = 0; k <= d-1; k++) {
    printf("%d\n", divisores[k]);
    sum += divisores[k];
  }

  printf("Soma: %d\n", sum);
  return 0;
}
