#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
  /*  calcula maior raiz de
  ax^2 + bx + c = 0, a>=0 */
  double a, b, c, discr;
  printf("Escreva os valores de a (>=0), b e c: ");
  scanf("%lf %lf %lf", &a, &b, &c);
  printf("%lf\n %lf\n %lf\n", a,b,c);
  discr = ((b*b) - (4*a*c));
  printf("%lf\n", discr);
  if(discr < 0) {
    printf("Raizes complexas !\n");
  } else {
    if(a > 0) {
      printf("Maior raiz = %e\n", (-b + sqrt(discr))/(2*a) );
    } else {
      printf("Maior raiz = %e\n", (-b - sqrt(discr))/(2*a) );
    }

  }

  return EXIT_SUCCESS;
}
