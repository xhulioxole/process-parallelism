#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <ctype.h>
#include <conio.h>

int main(int argc, char const *argv[]) {
  if (argv[1] == NULL) {
    printf("No arguments specified\n");
    printf("Usage main numOfProcesses{number}\n");
    return 0;
  }
  int numOfChildProcesses = atoi(argv[1]);
  if (numOfChildProcesses == 0) {
    printf("No arguments specified\n");
    printf("Usage main numOfProcesses{number}\n");
    return 0;
  }
  STARTUPINFO si[numOfChildProcesses];
  PROCESS_INFORMATION pi[numOfChildProcesses];
  int numOfFiles = 100;
  int rangeForCurrentProcess = numOfFiles / numOfChildProcesses;
  int filesLeft = numOfFiles % numOfChildProcesses;
  int i, from, to;
  for (i=0; i<numOfChildProcesses; i++) {
    from = (i * rangeForCurrentProcess);
    if (i == (numOfChildProcesses - 1)) {
      to = ((i + 1) * rangeForCurrentProcess) + filesLeft;
    } else {
      to = (i + 1) * rangeForCurrentProcess;
    }
    if (i != 0) {
      from++; // When i != 0 for ex: process files from 0-50 then from 51-100 not 50-100
    }
    startChildProccess(si[i], pi[i], from , to);
  }
  return 0;
  }

/**
* Start child proccess to read files with range [from-to] // ex: 1-15 => 1.txt .. 15.txt
*/
void startChildProccess (STARTUPINFO si, PROCESS_INFORMATION pi, int from, int to) {
  char childProcessName[20] = "child.exe"; // Child process name to call - Same Directory
  char fromToName[10];
  sprintf(fromToName, " %d", from);
  strcat(childProcessName, fromToName);
  sprintf(fromToName, " %d", to);
  strcat(childProcessName, fromToName);
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));
  BOOL created = CreateProcess(NULL, childProcessName, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
  if (!created) {
      fprintf(stderr, "Gabim ne ekzekutimin e nenprocesit.\n");
  } else {
    printf("\n\nChild process reading [%d-%d].txt\n", from, to);
    printf("=====================\n");
  }
  WaitForSingleObject(pi.hProcess, 500); // Sleep 0.5 sec before creating another proccess
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
}
