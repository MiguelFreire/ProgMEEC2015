#include <stdio.h>

void changeToCoins(int change, int *coins[6]);

int coins_values[] = {200, 100, 50, 20, 10, 5, 2};

//passagem por referencia n funciona

int main(void) {
  int c[6];
  int change = 245;
  changeToCoins(change, &c[6]);
  for(int i = 0; i <= 6; i++) {
    printf("%d\n", c[i]);
  }
}

void changeToCoins(int change, int *coins[6]) {
  for(int i = 0; i <= 6; i++) {
    *coins[i] = change/coins_values[i];
    change = change % coins_values[i];
  }
}
