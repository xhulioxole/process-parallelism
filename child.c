#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char DIR[100] = "C:\\Users\\Xhulio\\Desktop\\det\\"; // Files directory
int charCounter[256] = {0}; // ASCII 8 bit
int tmpCharCounter[256] = {0};
int indexMapper[256] = {0}; // Table used to store indexes of sorted array ex: t[0] = 2 (Index of max number in charCounterArray)

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
        // Last file
        sortDesc();
        prinfCharCounters();
      }
    }
  }
  return 0;
}

/**
* Count character
*/
void processFile(FILE *file) {
  char currentChar;
  char toLowerChar;
  while((currentChar = fgetc(file)) != EOF) {
    if (currentChar != '\n' && !isspace(currentChar)) { // Ignore newline and whitespaces
      charCounter[(int) tolower(currentChar)]++;
    }
  }
}

/**
 * Sort array desc by mapping indexes in indexMapper arrray
 */
void sortDesc() {
  int j;
  for (j=0; j<256; j++) {
    tmpCharCounter[j] = charCounter[j];
  }
  int indexOfMax;
  int i;
  for (i=0; i<256; i++) {
    indexOfMax = getIndexOfMaxAndDeleteMax(tmpCharCounter, 256);
    indexMapper[i] = indexOfMax;
  }
}

/**
 * Returns index of max number and deletes number from array;
 */
int getIndexOfMaxAndDeleteMax(int t[], int n) {
  int i;
  int max = -1;
  int maxIndex = -1;
  for (i=0; i<n-1; i++) {
    if (t[i] >= max) {
      max = t[i];
      maxIndex = i;
    }
  }
  t[maxIndex] = -1;
  return maxIndex;
}

/**
* Print count of every char found
*/
void prinfCharCounters() {
  int i=0;
  int mappedIndex;
  for(i; i<256; i++) {
    mappedIndex = indexMapper[i];
    if (charCounter[mappedIndex] != 0) {
      printf("Karakteri %c u gjet %d here\n", (char) mappedIndex, charCounter[mappedIndex]);
    }
  }
  printf("==============\n");
}
