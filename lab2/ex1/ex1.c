#include <stdio.h>


int calcula_digito_controlo(int nic[]);
int cc_valido(int nic[], int c);

int controlo[] = {9,8,7,6,5,4,3,2};
//14678962 8
int main(void) {
  int vector[7];

  int unsigned nic;
  int dc;

  printf("Insira NIF:\n");
  scanf("%d", &nic);

  int k=7;
  while(nic) {
    vector[k] = nic%10;
    nic /= 10;
    k--;
  }


  printf("Insira digito de controlo\n");
  scanf("%d", &dc);
  if(cc_valido(vector, dc)) {
    printf("CC Válido\n");
    return 1;
  }

  printf("CC invalido\n");
  return 0;


}

int cc_valido(int nic[], int c) {
  int dc = calcula_digito_controlo(nic);
  printf("%d\n", dc);
  if(dc == c) return 1;
  return 0;
}

int calcula_digito_controlo(int nic[]) {
  int sum;
  for(int n = 0; n <= 7; n++) {
      sum += (controlo[n] * nic[n]);
  }
  if((sum%11) == 0) return 0;
  else return (11 - sum%11);
}
