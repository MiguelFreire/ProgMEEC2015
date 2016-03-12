#include <stdio.h>
#include <math.h>

int convert_to_bin(int n);
int convert_to_dec(int n);
int menu();

int main(void) {
  while(1) {
    int op = menu();
    int n;
    int cn;
    if(op == 3) return 0;
    printf("Insira um número:\n");
    scanf("%d", &n);

    if(op == 1) {
      printf("%d(10) = %d(2)\n", n, convert_to_bin(n));
    } else if(op == 2) {
      printf("%d(2) = %d(10)\n", n, convert_to_dec(n));
    }

  }
}

int convert_to_bin(int n) {
  int resto, i, binary;
  i=1;
  while(n!=0) {
    resto = n%2;
    n /= 2;
    binary += resto*i;
    i *=10;
  }

  return binary;
}

int convert_to_dec(int n) {
  int resto, i, decimal;
  i=0;
  while(n!=0) {
    resto = n%10;
    n /= 10;
    decimal += (resto * pow(2,i));
    i++;
  }

  return decimal;
}

int menu() {
  int op;

  printf("//////////////////////////////\n");
  printf("/                            /\n");
  printf("/          Conversor         /\n");
  printf("/   1 -  Decimal-Binário     /\n");
  printf("/   2 -  Binario-Decimal     /\n");
  printf("/   3 -  Sair                /\n");
  printf("/                            /\n");
  printf("//////////////////////////////\n");

  scanf("%d", &op);
  if(op < 1 || op > 3) return menu();
  return op;
}
