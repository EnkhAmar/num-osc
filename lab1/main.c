#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LIMIT 100


char *getInput() {
  int n = 0;
  char input[MAX_LIMIT];
  char *str;

  printf(">> ");
  fgets(input, MAX_LIMIT, stdin);
  int len = strlen(input) - 1;     // I had to minus 1, bcz "\n" is counted as character

  str = (char *)malloc(sizeof(char)*(len));  

  for (int i=0; i<len; i++) {
    str[i] = input[i]; 
  }

  return (char *)str;
}

int main() {
  bool is_running = true;
  int a = 100, cnt = 0;
  char input[MAX_LIMIT];

  while (is_running && cnt < 3) {
    char *test = getInput();

    char *token[3];
    int word_cnt = 0;
    while ((token[word_cnt] = strtok_r(test, " ", &test)) && word_cnt < 3) {
      word_cnt++;
    }

    if (strcmp(token[0], "dir") == 0 || strcmp(token[0], "ls") == 0)
    {
      /*
       * File-iin jagsaalt harna. "dir", "ls" commandiig ashiglah bolomjtoi
       */
      printf("showing all files\n");
    }
    else if (strcmp(token[0], "create") == 0 || strcmp(token[0], "touch") == 0)
    {
      /*
       * Shineer file uusgene. "create", "ls" commanding ashiglah bolomjtoi
       */
      printf("creating a new file.\n");
    }
    else if (strcmp(token[0], "input") == 0)
    {
      /*
       * Filed ogogdol orooulna. "input" commanding ashiglah bolomjtoi  
       * >> input text.txt sample data
       */
      printf("inserting data to file");
    }
    else if (strcmp(token[0], "rename") == 0) {
      /*
       * File-iin neriig oorchlono. "rename" commanding ashiglah bolomtjoi
       * >> rename text.txt file.txt
       */
      printf("renaming a file");
    }
    else if (strcmp(token[0], "del") == 0 || strcmp(token[0], "rm") == 0) {
      /*
       * File-iig ustgana. "del", "rm" commanding ashiglah bolomjtoi
       * >> del file.txt
       */
      printf("deleting a file");
    }
    else if (strcmp(token[0], "exit") == 0 || strcmp(token[0], "quit") == 0) {
      /*
       * Programming haana. "exit, "quit" commanding ashiglah bolomjtoi
       * >> exit
       * >> quit
       */
      free(test);
      exit(0);
    }

    for (int k=0; k<word_cnt && token[k]; k++) {
      printf("%s\t", token[k]);
    }
    printf("\n");
    free(test);
    cnt++;
  }
  return 0;
}