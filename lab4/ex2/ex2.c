#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 100

typedef struct {
  int day;
  int month;
  int year;
} date;

typedef struct {
  char *name;
  date birthdate;
  int age;
} teacher;

int calcAge(date , date);
void readTeacher(teacher *, date);
void orderByAge(teacher *, int);
void printData(teacher *, int);

int main(void) {
  date today = {21,4,2016};
  int n = 0;
  char buffer[MAX_BUFFER_SIZE];
  int rtn;

  printf("How many teachers to introduce?\n");
  do {
    fgets(buffer, MAX_BUFFER_SIZE, stdin);
    rtn = sscanf(buffer, "%d",&n);
  } while(rtn != 1);

  teacher *t = (teacher *) malloc(n*sizeof(teacher));
  if(t == NULL) {
    printf("Not enough memory\n");
    exit(1);
  }
  for(int i=0; i < n; i++) {
    readTeacher(&t[i], today);
  }
  orderByAge(t, n);
  printData(t, n);

  free(t);
  return 0;
}
/**
 * Calculates a teachers age
 * @param  date bday  [birthdate]
 * @param  date today [today's date]
 * @return int  age
 */
int calcAge(date bday, date today) {
  if(today.month < bday.month) {
      return today.year-bday.year-1;
  } else if(today.month == bday.month) {
    if(today.day < bday.day) return today.year-bday.year-1;
    return today.year-bday.year;
  }
  return today.year-bday.year;
}
/**
 * Reads a new teacher
 * @param teacher t     [teacher's vector]
 * @param date    today [today's date]
 */
void readTeacher(teacher *t, date today) {
  char buffer[MAX_BUFFER_SIZE];
  printf("Teacher's name?\n");
  fgets(buffer, MAX_BUFFER_SIZE, stdin);
  t->name = (char *) malloc((strlen(buffer)+1)*sizeof(char)); //Name dynamic memory alloc

  if(t->name == NULL) {
    printf("Not enough memory\n");
    exit(1);
  }
  strcpy(t->name, buffer);
  t->name[strlen(t->name)-1] = '\0'; //Terminate the string with nullbyte

  printf("Teacher's birthdate?\n");
  fgets(buffer, MAX_BUFFER_SIZE, stdin);
  sscanf(buffer, "%d/%d/%d", &t->birthdate.day, &t->birthdate.month, &t->birthdate.year);
  t->age = calcAge(t->birthdate, today);
}


/**
 * Order vector by age, using the date struct and the bubblesort algorithm
 * @param t           [teacher's vector]
 * @param numTeachers [number of teachers]
 */
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
/**
 * Prints the data
 * @param teacher t [teachers vector]
 * @param int     n [number of teachers]
 */
void printData(teacher *t, int n) {
  printf("Younger teacher: %s (%d/%d/%d)\n", t[n-1].name, t[n-1].birthdate.day, t[n-1].birthdate.month, t[n-1].birthdate.year);
  printf("Older teacher: %s (%d/%d/%d)\n", t[0].name, t[0].birthdate.day, t[0].birthdate.month, t[0].birthdate.year);

  int sum=0;
  for(int i=0; i < n; i++) {
    sum += t[i].age;
  }

  printf("Average age: %.2f\n", (sum/(float) n));
}
