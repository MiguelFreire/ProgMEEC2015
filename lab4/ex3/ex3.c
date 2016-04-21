#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 100


typedef struct {
  char firstname[100];
  char lastname[100];
} name;

typedef struct {
  int day;
  int month;
  int year;
} date;

typedef struct {
  name name;
  date birthdate;
  int age;
} teacher;

int calcAge(date bday, date today) {
  if(today.month < bday.month) {
      return today.year-bday.year-1;
  } else if(today.month == bday.month) {
    if(today.day < bday.day) return today.year-bday.year-1;
    return today.year-bday.year;
  }
  return today.year-bday.year;
}

void readTeacher(teacher *t, date today) {
  char buffer[MAX_BUFFER_SIZE];
  printf("Teacher's name?\n");
  fgets(buffer, MAX_BUFFER_SIZE, stdin);
  sscanf(buffer, "%s %s", t->name.firstname, t->name.lastname);


  printf("Teacher's birthdate?\n");
  fgets(buffer, MAX_BUFFER_SIZE, stdin);
  sscanf(buffer, "%d/%d/%d", &t->birthdate.day, &t->birthdate.month, &t->birthdate.year);
  t->age = calcAge(t->birthdate, today);
}



void orderByAge(teacher *t, int numTeachers) {
  teacher tmp;
  int cntYears=0;
  int cntMonths=0;
  for(int i=numTeachers-1; i >= 1; i--)
  {
    for( int j=0; j < i ; j++)
    {
      if(t[j].birthdate.year > t[j+1].birthdate.year)
      {
        tmp = t[j];
        t[j] = t[j+1];
        t[j+1] = tmp;
      }
      if(t[j].birthdate.year == t[j+1].birthdate.year) cntYears++;
    }

  }
  if(cntYears != 0) {
    for(int i=cntYears-2; i >= 1; i--)
    {
      for( int j=0; j < i ; j++)
      {
        if(t[j].birthdate.month > t[j+1].birthdate.month)
        {
          tmp = t[j];
          t[j] = t[j+1];
          t[j+1] = tmp;
        }
        if(t[j].birthdate.month == t[j+1].birthdate.month) cntMonths++;
      }

    }
  }
  if(cntMonths != 0) {
    for(int i=cntMonths-3; i >= 1; i--)
    {
      for( int j=0; j < i ; j++)
      {
        if(t[j].birthdate.day > t[j+1].birthdate.day)
        {
          tmp = t[j];
          t[j] = t[j+1];
          t[j+1] = tmp;
        }
      }

    }
  }
}

void printResult(teacher *t, int n) {
  printf("Younger teacher: %s %s (%d/%d/%d)\n", t[n-1].name.firstname, t[n-1].name.lastname, t[n-1].birthdate.day, t[n-1].birthdate.month, t[n-1].birthdate.year);
  printf("Older teacher: %s %s (%d/%d/%d)\n", t[0].name.firstname, t[0].name.lastname,t[0].birthdate.day, t[0].birthdate.month, t[0].birthdate.year);

  int sum=0;
  for(int i=0; i < n; i++) {
    sum += t[i].age;
  }
  printf("Average age: %.2f\n", (sum/(float) n));
}

int main(void) {
  date today = {21,4,2016};
  char *fileName;
  char buffer[MAX_BUFFER_SIZE];
  printf("File name?\n");
  fgets(buffer, MAX_BUFFER_SIZE, stdin);
  fileName= (char *) malloc((strlen(buffer)+1)*sizeof(char));
  strcpy(fileName, buffer);
  fileName[strlen(fileName)-1] = '\0';
  FILE *file = fopen(fileName, "r+");
  if(file == NULL) {
    printf("File not found\n");
    return 0;
  }
  int numLines = 0;
  int c;

  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') ++numLines;
  }

  printf("%d\n", numLines);
  teacher *t = (teacher *) malloc(numLines*sizeof(teacher));
  rewind(file);
  int i =0;
  while(fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
    sscanf(buffer, "%s %s %d / %d / %d", t[i].name.firstname, t[i].name.lastname, &t[i].birthdate.day, &t[i].birthdate.month, &t[i].birthdate.year);
    t[i].age = calcAge(t[i].birthdate, today);
    i++;
  }


  int n = numLines;

  while(1) {
    orderByAge(t, n);
    printResult(t, n);
    int c;
    printf("Press (a) to add a new teacher or (q) to quit\n");
    while((c = getchar()) != EOF) {
      if(c == 'a') {
        printf("\n");
        n++;
        t = (teacher *) realloc(t, n*sizeof(teacher));
        readTeacher(&t[n-1], today);
        orderByAge(t, n);
        printResult(t, n);
        break;
      }
      if(c == 'q') {
        fclose(file);
        free(fileName);
        free(t);
        return 0;
      }
    }

  }
