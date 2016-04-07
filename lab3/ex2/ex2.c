#include <stdio.h>
#include <string.h>

int isPalindrome(char str[]);

int main(void) {
  char str[100];

  fgets(str, 100, stdin);
  if(isPalindrome(str)) {
      printf("%s is a palindrome\n", str);
      return 1;
  }
  printf("%s is NOT a palindrome\n", str);
  return 0;

}
/**
 * Checks is a string is a palindrome
 * @param  str        [string to check]
 * @return bool int   [0 - false, 1 -true]
 */
int isPalindrome(char str[]) {
  char invStr[100];
  int strSize = strlen(str); //Get string length
  for(int i = strSize-1; i >= 0; i--) {
     invStr[strSize-i-1] = str[i]; //Invert the string
   }

  int k =0;
  for(int i = 0; i < strSize; i++, k++) {
         invStr[i] = invStr[i+1]; //Shift the inverted string to the left
  }
  str[strSize-1] = '\0'; //Force end of string on the limit index
  invStr[strSize-1] = '\0'; //This has to be done because of the shifted string

  if(strcmp(str, invStr) == 0) { //Compare the strings if they are identical it is a palindrome
    return 1;
  }
  return 0;
}
