#include <stdio.h>


int teste(int m) {
  static int t[] = { 0 , 1 , 2 , 3, 4, 5};
  t[m]++;
  return t[m];
}

int main(void) {
  int y;
  for(int i = 0; i <= 5; i++) {
    y = teste(2);
    printf("%d\n", y);
  }

}
