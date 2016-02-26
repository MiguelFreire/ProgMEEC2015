#include <stdio.h>
#include <string.h>

int dayofweek(int d, int m, int y)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}


int main(void){
  int d, m, y;
  int weekday;
  scanf("%d/%d/%d", &d, &m, &y);
  weekday = dayofweek(d,m,y);
  switch (weekday) {
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
      printf("Sabado\n");
    break;
  }
  return 0;
}
