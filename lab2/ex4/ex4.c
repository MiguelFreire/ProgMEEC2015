#include <stdio.h>
#include <math.h>

void SieveOfEratosthenes(int array[]);
void FlagMultipleNumbers(int array[], int n);

int limit;

int main(void) {

  int max_number;
  printf("Número maximo?\n");
  scanf("%d", &limit);
  printf("Limite=%d\n", limit);
  int list[100];
  //preenche a lista com números naturais
  for(int i = 0; i <= limit-2; i++) {
    list[i] = i+2;
  }

  SieveOfEratosthenes(list);
  for(int n = 0; n <= limit-1; n++) {
    printf("%d\n", list[n]);
  }


  return 0;
}

void SieveOfEratosthenes(int array[]) {
  for(int m = 2; m <= sqrt(limit); m++) {
    FlagMultipleNumbers(array, m);
  }
 }

void FlagMultipleNumbers(int array[], int n) {
  for(int i = n; i < limit; i++) {
      if((array[i] % n) == 0) {
        array[i] = array[i+1];
        limit--;
        for(int k = i; k <= limit; k++) {
          array[k] = array[k+1];
        }
      }

    }
}
