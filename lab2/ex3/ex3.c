#include <stdio.h>
#include <math.h>

void changeToCoins(float change, int coins[]);

float coins_values[] = {2.00, 1.00, 0.50, 0.20, 0.10, 0.05, 0.02};


int main(void) {
  int c[7];
  float price, mgiven, change;
  printf("Preço do produto?\n");
  scanf("%f", &price);
  printf("Dinheiro dado?\n");
  scanf("%f", &mgiven);
  change = mgiven - price;
  if(change < 0)
  {
    printf("Sem troco. Falta pagar %f euros\n", -change);
    return 0;
  }

  printf("Troco: %.2f\n", change);

  changeToCoins(change, c);

  for(int i = 0; i <= 6; i++) {
    switch (i) {
      case 0:
      if(c[i]!=0) printf("%d moeda(s) de 2 euros\n", c[i]);
      break;
      case 1:
      if(c[i]!=0) printf("%d moeda(s) de 1 euros\n", c[i]);
      break;
      case 2:
      if(c[i]!=0) printf("%d moeda(s) de 50 centimos\n", c[i]);
      break;
      case 3:
      if(c[i]!=0) printf("%d moeda(s) de 20 centimos\n", c[i]);
      break;
      case 4:
      if(c[i]!=0) printf("%d moeda(s) de 10 centimos\n", c[i]);
      break;
      case 5:
      if(c[i]!=0) printf("%d moeda(s) de 5 centimos\n", c[i]);
      break;
      case 6:
      if(c[i]!=0) printf("%d moeda(s) de 2 centimos\n", c[i]);
      break;
    }
  }
  return 0;
}

void changeToCoins(float change, int coins[]) {
  float d;
  for(int i = 0; i <= 6 ; i++) {
    d = (change/coins_values[i]) + 0.001; // é necessário somar 0.001 devido ao erro que acontece na divisão de 2 floats ex 0.10/0.1000 = 0.999..9
    coins[i] = (int) d;
    if(d >= 1) {
      change -= coins[i] * coins_values[i];
    }
  }
}
