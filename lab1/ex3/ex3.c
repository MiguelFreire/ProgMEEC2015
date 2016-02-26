#include <stdio.h>
#include <math.h>

#define PI 3.14159265

float convertAngleToRad(float angle) {
  return ((angle * PI)/180);
}



int main(void){

  double angle, angle_sen, angle_cos, result;
  printf("Angulo em graus?\n");
  scanf("%lf", &angle);
  angle = convertAngleToRad(angle);
  angle_sen = sin(angle);
  angle_cos = cos(angle);

  result = ((angle_sen * angle_sen) + (angle_cos * angle_cos));

  printf("Resultado: %lf\n", result);


  return 0;
}
