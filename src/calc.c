#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *test(char *str);

void main() {
  char *test1 = test("1 + 2 - fsd     12");
  printf("problem: %s'n", test1);
  free(test1);
}

char *test(char *str) {
  char *buf = calloc(strlen(str), sizeof(char));
  int k = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] != ' ') {
      buf[k] = str[i];
      k++;
    }
  }
  return buf;
}