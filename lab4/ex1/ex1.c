#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1024

int calculateFileSize(FILE *file) {
  int size;
  fseek(file, 0l, SEEK_END);
  size = ftell(file);
  fseek(file, 0l, SEEK_SET);

  return size;
}

int main(int argc, char *argv[]) {
  FILE *file1, *file2;
  int fileSize = 0;
  char line[MAX_SIZE], line2[MAX_SIZE];
  int size = 0;
  file1 = fopen(argv[1], "r");
  file2 = fopen(argv[2], "r");
  if(file1==NULL || file2==NULL) {
    printf("Could not open the desired file\n");
    return 0;
  }
  fileSize = calculateFileSize(file1) + calculateFileSize(file2);
  char *concFile = (char *) malloc(fileSize*sizeof(char));
  if(concFile == NULL) {
    printf("Not enough memory");
    exit(1);
  }
  int i = 1;
  int ptr = 0;
  // while(fgets(line, 100, file1) || fgets(line2,100,file2)) {
  //     strcpy(&concFile[ptr], line);
  //     ptr += strlen(line);
  //     // fseek(file2, strlen(line), SEEK_END);
  //     strcpy(&concFile[ptr], line2);
  //     ptr += strlen(line2);
  //
  // }
  int file1EOF=0, file2EOF=0;
  char *rtv;
  while(!file1EOF || !file2EOF) {
      rtv = fgets(line, MAX_SIZE, file1);
      if(rtv==NULL) file1EOF=1;
      else {
        strcpy(&concFile[ptr], line);
        ptr += strlen(line);
      }
      // fseek(file2, strlen(line), SEEK_END);
      rtv= fgets(line2, MAX_SIZE, file2);
      if(rtv==NULL) file2EOF=1;
      else {
        strcpy(&concFile[ptr], line2);
        ptr += strlen(line2);
    }

  }

  for(int i = ptr; ptr > 0; ptr--) {
    printf("%c", concFile[ptr]);
  }
  printf("\n");
  free(concFile);
  fclose(file1);
  fclose(file2);
  return 1;

}
