#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <mpi.h>

#define MAX_SENTENCES 240


typedef struct foo_struct foo_struct;

int memloadf(char *p);
int process(char *ln);

char *sentence[MAX_SENTENCES] = {NULL};
char *mem;
int count = 0;
int rank;
int total;
int size = 0;


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
  while (tmp != NULL) {
    int color_num = atoi(tmp);
    char ripharambe = color(strtok(NULL, ",;"));
    switch (ripharambe) {
    case 'b':
      if (color_num > blue)
	return 0;
      break;
    case 'r':
      if (color_num > red)
	return 0;
      break;
    case 'g':
      if (color_num > green)
	return 0;
      break;
    }
    //printf("Color: %c %i\n", ripharambe, color_num);
    tmp = strtok(NULL, " ");
  }
  return id;
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

    MPI_Init(&c, &v);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_sum = 0;
    int todo = count / size;
    // For le overflow
    if (rank < (count - (todo * size)))
      todo++;
    if (rank >= count)
      rank--;

    if (rank == 0) {
      printf("Count %i\n", count);
      printf("Rank %i\n", rank);
      printf("Size %i\n", size);
      printf("TODO %i\n", todo);
    }
    for(int i = rank; todo > 0; todo--,i+=size) {
      if(sentence[i]) {
	local_sum += process(sentence[i]);
      } else {
	printf("DERRRRP\n");
      }
    }

    MPI_Reduce(&local_sum, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
      printf("Sum: %i\n", total);
    }

    MPI_Finalize();
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