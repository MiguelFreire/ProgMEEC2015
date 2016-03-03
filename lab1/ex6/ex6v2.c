#include <stdio.h>
#include <stdlib.h>

#define REF_YEAR 2012 //Ano de referencia
#define REF_MONTH 1 // Mês de referencia
#define REF_DAY 1 // Dia de referencia


unsigned char isLeap(int ano) {
  if (( ano % 4 == 0 && ano % 100 != 0 ) || ano % 400 == 0 ) return 1;
  return 0;
}

int main(void) {

  int d,m,y, num_days, ab, ac, dayofweek;
  int dif;
  unsigned char leap;
  //HANDLE YEAR
  printf("Data:\n");

  scanf("%d/%d/%d", &d, &m, &y);
  leap = isLeap(y);

  while((d < 1) || (d > 31) || (m < 1) || ( m > 12) || (m == 2 && leap && d > 28) || (m==2 && !leap && d > 29) ) {
    printf("Formato de data errado! Digite novamente a data:\n");
    scanf("%d/%d/%d", &d, &m, &y);
  }
  dif = y - REF_YEAR;
  printf("Dif: %d\n", dif);

  if(y > REF_YEAR) {
    for(int i = 0; i< abs(dif); i++ ) {
      if (isLeap(REF_YEAR+i)) ab++;
      printf("%d\n", ab);
    }
  } else {
    for(int i = 0; i< abs(dif); i++ ) {
      if (isLeap(y+i)) ab--;
      printf("%d\n", ab);
    }

  }
  ac = dif - ab;
  num_days = 366 * ab + 365*ac;

  //Handle Month
 switch (m) {
    case 2:
      num_days += 31;
    break;
    case 3:
      num_days += 31+28;
    break;
    case 4:
      num_days += 31+28+31;
    break;
    case 5:
      num_days += 31+28+31+30;
    break;
    case 6:
      num_days += 31+28+31+30+31;
    break;
    case 7:
      num_days += 31+28+31+30+31+30;
    break;
    case 8:
      num_days += 31+28+31+30+31+30+31;
    break;
    case 9:
      num_days += 31+28+31+30+31+30+31+31;
    break;
    case 10:
      num_days += 31+28+31+30+31+30+31+31+30;
    break;
    case 11:
      num_days += 31+28+31+30+31+30+31+31+30+31;
    break;
    case 12:
      num_days += 31+28+31+30+31+30+31+31+30+31+30;
    break;
  }

  d--;
  if(leap && m > 2) num_days = num_days + d + 1;
  else num_days = num_days + d;

  if(y > REF_YEAR) {
    dayofweek = num_days % 7;
  } else {
    dayofweek = num_days % 7;
    dayofweek = (7 - dayofweek) % 7;


  }
  printf("Dia da semana:");
  switch (dayofweek) {
    case 0:
    printf("Domingo\n");
    break;
    case 1:
    printf("Segunda-feira\n");
    break;
    case 2:
    printf("Terça-feira\n");
    break;
    case 3:
    printf("Quarta-feira\n");
    break;
    case 4:
    printf("Quinta-feira\n");
    break;
    case 5:
    printf("Sexta-feira\n");
    break;
    case 6:
    printf("Sábado\n");
    break;
    default:
    printf("ERRO\n");
    break;

  }

  return 0;

}
