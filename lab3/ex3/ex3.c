#include <stdio.h>
#include <string.h>

int countStrOnStr(char haystack[], char needle[], char *token);

int main(void) {
  char haystack[100] = "sou um pro a programar programação";
  char needle[25] = "pro";
  char *token;
  int counter = countStrOnStr(haystack, needle, token);

  printf("%d\n", counter);
}
/**
 * Counts how many times a small string is in a bigger string
 * @param  haystack     [the big string to be searched]
 * @param  needle       [the small string to search in the big string]
 * @param  token        [the result of the strstr function]
 * @return int counter  [the number of time the small string was in the big string]
 */
int countStrOnStr(char haystack[], char needle[], char *token) {
  int counter=0;
  for(int i=0;i < strlen(haystack) ; i++) {
    token = strstr(&haystack[i], needle);
    if(&haystack[i] == token) {
      counter++;
    }
  }
  return counter;
}
