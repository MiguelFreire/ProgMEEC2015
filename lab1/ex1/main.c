#include <stdio.h>
#include <math.h>

int main(void){
  /*  calcula maior raiz de
  ax^2 + bx + c = 0, a>=0 */
  double a, b, c, discr;
  printf("Escreva os valores de a (>=0), b e c: ");
  scanf("%f %f %f", &a, &b, &c);
  printf("%f\n %f\n %f\n", a,b,c);
  discr = ((b*b) - (4*a*c));
  printf("%f\n", discr);
  if(discr < 0) {
    printf("Raizes complexas !\n");
  } else {
    printf("Maior raiz = %e\n", (-b -sqrt(discr))/(2*a) );
  }

  return 0;
}
