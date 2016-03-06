#include <stdio.h>
#include <ctype.h>


int main(void) {
  char c;
  char str[255];
  int n = 0;
  while((c = getchar()) != '\n') {
    str[n] = tolower(c);
    n++;
  }
  printf("%s\n", str);
  return 0;
}
