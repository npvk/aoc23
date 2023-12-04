#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define MAX_SENTENCES 240


typedef struct foo_struct foo_struct;

int memloadf(char *p);
int process(char *ln);

char *sentence[MAX_SENTENCES] = {NULL};
char *mem;
int count = 0;
int total = 0;



// if the bag had been loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes
int red = 12;
int green = 13;
int blue = 14;
char color(char *str);

char color(char *str) {
  if (strcmp("blue", str) == 0) {
    return 'b';
  }
  if (strcmp("green", str) == 0) {
    return 'g';
  }
  if (strcmp("red", str) == 0) {
    return 'r';
  }
  return 'n';
}

int process(char *ln) {
  int id;
  register char *tmp;
  // Game <num>:
  id = atoi(strtok(ln, "Game :"));
  tmp = strtok(NULL, " ");

  int rmin = 0;
  int bmin = 0;
  int gmin = 0;
  while (tmp != NULL) {
    int color_num = atoi(tmp);
    char ripharambe = color(strtok(NULL, ",;"));
    switch (ripharambe) {
    case 'b':
      if (color_num > bmin)
	bmin = color_num;
      break;
    case 'r':
      if (color_num > rmin)
	rmin = color_num;
      break;
    case 'g':
      if (color_num > gmin)
	gmin = color_num;
      break;
    }
    //printf("Color: %c %i\n", ripharambe, color_num);
    tmp = strtok(NULL, " ");
  }
  return bmin*rmin*gmin;
}

int main(int c, char **v)
{
    if(c != 2) {
        printf("WRONG ARGS: [filename]\n\n");
        return -1;
    }
    if(memloadf(v[1])) {
      printf("RIP\n");
      return -1;
    }

    int todo = count;

    for(int i = 0; i < count; i++) {
      total += process(sentence[i]);
    }

    printf("Sum: %i\n", total);

    return 0;
}

int memloadf(char *p) {
    int fd;
    struct stat s;
    int status;

    fd = open(p, O_RDONLY);
    status = fstat(fd, &s);
    mem = mmap(mem, s.st_size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);

    register char *tmp = strtok(mem, "\n");
    if(tmp)
      sentence[count++] = tmp;
    else
      return -1;

    while(tmp != NULL) {
      tmp = strtok(NULL, "\n");
      sentence[count++] = tmp;
    }
    count--;
    return 0;
}
