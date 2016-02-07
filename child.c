#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char DIR[100] = "C:\\Users\\Xhulio\\Desktop\\det\\";
int charCounter[256] = {0}; // ASCII 8 bit

int main(int argc, char const *argv[]) {
  if (argv[1] == NULL || argv[2] == NULL) {
    printf("No arguments specified!\n");
    printf("Usage child {from} {to}\n");
    return;
  } else {
    int i = atoi(argv[1]);
    int max = atoi(argv[2]);
    char fileName[15];
    char fullFileDir[100];
    for (i; i <= max; i++) {
      sprintf(fileName, "%d", i); //1, 2, 3
      strcat(fileName, ".txt"); // 1.txt, 2.txt, 3.txt
      strcpy(fullFileDir, DIR); // DIR
      strcat(fullFileDir, fileName); // DIR + 1.txt
      FILE *file = fopen(fullFileDir, "r");
      if (file != NULL) {
          processFile(file);
      }
      if (i == max) {
        prinfCharCounters();
      }
    }
  }
  return 0;
}

/**
* Count characte
*/
void processFile(FILE *file) {
  char currentChar;
  char toLowerChar;
  while((currentChar = fgetc(file)) != EOF) {
    if (currentChar != '\n' && !isspace(currentChar)) {
      charCounter[(int) tolower(currentChar)]++;
    }
  }
}

/**
* Print count of every char found
*/
void prinfCharCounters() {
  int i=0;
  for(i; i<256; i++) {
    if (charCounter[i] != 0) {
      printf("Karakteri %c u gjet %d here\n", (char) i, charCounter[i]);
    }
  }
  printf("==============\n");
}
