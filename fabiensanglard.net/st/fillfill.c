#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>

void malloc_and_fill(size_t s) {
  uint8_t* buffer = (uint8_t*) malloc(s);
  for (size_t i = 0; i < s; i++) {
    *(buffer+ i) = 'F';
  }
  free(buffer);
}

int main(int argc, char **argv) {
  malloc_and_fill(1L << 30);
  int pid = fork();
  if (pid == 0) {
    malloc_and_fill(1L << 31);   
  } else {
    waitpid(pid, NULL, 0);
  }
  return 0;
}