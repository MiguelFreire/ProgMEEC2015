#include <stdio.h>

int main(void) {
  char operador;
  float opA, opB, resultado;
  printf("Insira operador (+,-,*,/):");
  scanf("%c", &operador);
  printf("Insira operandos:");
  scanf("%f %f", &opA, &opB);

  switch (operador) {
    case '*': //multiplicação
      resultado = opA * opB;
    break;
    case '+': //adição
      resultado = opA + opB;
    break;
    case '-': //subtração
      resultado = opA - opB;
    break;
    case '/': //divisão
      resultado = opA - opB;
    break;
    default:
      printf("Operação Invalida\n");
    break;

  }
  printf("Resultado: %f\n", resultado);
  return 0;
}
