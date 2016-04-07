#include <stdio.h>
#define MAX_SIZE 15

void createMatrixes(float A[][MAX_SIZE], float B[][MAX_SIZE], int matrix_size[][2] );
void fillMatrix(float matrix[][MAX_SIZE], int matrix_size[]);
void printMatrix(float matrix[][MAX_SIZE], int matrix_size[]);
void createMatrix(float matrix[][MAX_SIZE], int matrix_size[]);
void sumMatrixes(float A[][MAX_SIZE], float B[][MAX_SIZE], int matrix_size[][2] );
void multiplyMatrixes(float A[][MAX_SIZE], float B[][MAX_SIZE], float C[][MAX_SIZE], int matrix_size[][2]);
int menu();

int main(void) {
  int matrix_size[3][2] = {0};
  float A[MAX_SIZE][MAX_SIZE] = {{0}};
  float B[MAX_SIZE][MAX_SIZE] = {{0}};
  float C[MAX_SIZE][MAX_SIZE] = {{0}};

  createMatrixes(A,B,matrix_size);
  printf("Matrix A:\n");
  printMatrix(A, matrix_size[0]);
  printf("Matrix B:\n");
  printMatrix(B, matrix_size[1]);
  while(1) {
    int menu_op = menu();
    switch (menu_op) {
      case 1:
        sumMatrixes(A,B, matrix_size);
        printf("Matrix A:\n");
        printMatrix(A, matrix_size[2]);
        break;
      case 2:
        multiplyMatrixes(A,B,C,matrix_size);
        printf("Matrix C:\n");
        printMatrix(C, matrix_size[2]);
        break;
      case 3:
        return 0;
      default:
        return 0;
      }
  }
  return 1;
}

void sumMatrixes(float A[][MAX_SIZE], float B[][MAX_SIZE], int matrix_size[][2]) {
  if(matrix_size[0][0] != matrix_size[1][0] || matrix_size[0][1] != matrix_size[1][1]) {
    printf("As dimensões das matrizes tem de ser identicas para poderem ser somadas\n");
    return;
  }
  for(int n=0; n < matrix_size[0][0]; n++) {
    for(int m=0; m < matrix_size[0][1]; m++) {
      A[n][m] = A[n][m]+B[n][m];
    }
  }
}

void multiplyMatrixes(float A[][MAX_SIZE], float B[][MAX_SIZE], float C[][MAX_SIZE], int matrix_size[][2]) {
  if(matrix_size[0][1] != matrix_size[1][0]) {
    printf("O número de linhas da primeira matriz tem de ser igual ao numero de colunas da segunda!\n");
    return;
  }
  matrix_size[2][0] = matrix_size[0][0];
  matrix_size[2][1] = matrix_size[1][1];

  int cols = matrix_size[1][1];
  for(int n=0; n < matrix_size[2][0]; n++) {
    for(int m=0; m < matrix_size[2][1]; m++) {
      for(int k=0; k < matrix_size[0][1]; k++)
      {
        C[n][m] += A[n][k]*B[k][m];
      }
    }
  }
}

void createMatrixes(float A[][MAX_SIZE], float B[][MAX_SIZE], int matrix_size[][2]) {
    createMatrix(A, matrix_size[0]);
    createMatrix(B, matrix_size[1]);
}

void createMatrix(float matrix[][MAX_SIZE], int matrix_size[]) {
  int tmp;
  printf("Número de linhas e colunas da matriz?(formato nxm, valor maximo de n e m =15)\n");
  while(!scanf("%dx%d", &matrix_size[0], &matrix_size[1]) || matrix_size[0] > MAX_SIZE || matrix_size[1] > MAX_SIZE) {
    while((tmp=getchar()) != EOF && tmp != '\n'); // fixes infinite loop
    printf("Erro: formato invalido\n");
    printf("Número de linhas e colunas da matriz?(formato nxm, valor maximo de n e m =15)\n");
  }
  for(int n=0; n < matrix_size[0]; n++) {
    for(int m=0; m < matrix_size[1]; m++) {
      printf("Entrada %dx%d?\n",n,m);
      scanf("%f", &matrix[n][m]);
    }
  }
}

void printMatrix(float matrix[][MAX_SIZE], int matrix_size[]) {
  for(int n=0; n < matrix_size[0]; n++) {
    printf("[");
    for(int m=0; m < matrix_size[1]; m++) {
      printf("%.2f\t",matrix[n][m]);
    }
    printf("]\n");
  }
}

int menu() {
  int op;

  printf("///////////////////////////////\n");
  printf("/                             /\n");
  printf("/          Conversor          /\n");
  printf("/   1 -  Soma de matrizes     /\n");
  printf("/   2 -  Producto de matrizes /\n");
  printf("/   3 -  Sair                 /\n");
  printf("/                             /\n");
  printf("///////////////////////////////\n");

  scanf("%d", &op);
  if(op < 1 || op > 3) {
    printf("Por-favor escolha uma das opções validas\n");
    return menu();
  }
  return op;
}
