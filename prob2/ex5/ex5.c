#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char line[1024], *p, *e;
  long v;
  int last;
  int grt = 0, sml=0;
  if(fgets(line, sizeof(line), stdin) != NULL) {
    p = line;
    for (p = line; ; p = e) {
        v = strtol(p, &e, 10);
        if (p == e)
            break;
        if(p == line) last = v;
        else {
          if(v > last) grt=1;
          else if(v < last) sml=1;
        }
      }
}
  if(grt && sml) printf("Sequencia Mista\n");
  else if(grt && !sml ) printf("Sequencia Cresceste\n");
  else if(!grt && sml) printf("Sequencia Descrescente\n");
  return 0;
}
