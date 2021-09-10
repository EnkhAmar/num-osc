#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#define MAX_LIMIT 100


char *getInput();
void directoryFunc();
void createFunc(char *filname);
void inputFunc(char *filename, char *txt);
void renameFunc(char *oldname, char *newname);
void delFunc(char *filename);

int main() {
  bool is_running = true;
  char input[MAX_LIMIT];

  while (is_running) {
    char *userInput = getInput();

    char *token[MAX_LIMIT];
    int word_cnt = 0;
    while ((token[word_cnt] = strtok_r(userInput, " ", &userInput))) {
      word_cnt++;
    }

    if ((strcmp(token[0], "dir") == 0 || strcmp(token[0], "ls") == 0) && word_cnt == 1)
    {
      /*
       * File-iin jagsaalt harna. "dir", "ls" commandiig ashiglah bolomjtoi
       */
      directoryFunc();
    }
    else if ((strcmp(token[0], "create") == 0 || strcmp(token[0], "touch") == 0) && word_cnt > 1)
    {
      /*
       * Shineer file uusgene. "create", "ls" commanding ashiglah bolomjtoi
       */
      for (int i=1; i<word_cnt; i++)
        createFunc(token[i]);
    }
    else if ((strcmp(token[0], "input") == 0) && word_cnt > 2)
    {
      /*
       * Filed ogogdol orooulna. "input" commanding ashiglah bolomjtoi  
       * >> input text.txt sample data
       */
      char dest[1000] = "";
      for (int i=2; i < word_cnt; i++) {
        strcat(dest, token[i]);
        dest[strlen(dest)] = ' ';
      }
      inputFunc(token[1], dest);
    }
    else if ((strcmp(token[0], "rename") == 0) && word_cnt > 2) {
      /*
       * File-iin neriig oorchlono. "rename" commanding ashiglah bolomtjoi
       * >> rename text.txt file.txt
       */
      renameFunc(token[1], token[2]);
    }
    else if ((strcmp(token[0], "del") == 0 || strcmp(token[0], "rm") == 0) && word_cnt > 1) {
      /*
       * File-iig ustgana. "del", "rm" commanding ashiglah bolomjtoi
       * >> del file.txt
       */
      for (int i=1; i<word_cnt; i++)
        delFunc(token[i]);
    }
    else if ((strcmp(token[0], "exit") == 0 || strcmp(token[0], "quit") == 0) && word_cnt == 1) {
      /*
       * Programming haana. "exit, "quit" commanding ashiglah bolomjtoi
       * >> exit
       * >> quit
       */
      free(userInput);
      return 0;
    }

    free(userInput);
  }
  return 0;
}

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

void directoryFunc() {
  DIR *d = opendir(".");
  struct dirent *dir;
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      // if (dir->d_type == DT_REG)
        printf("%s\t", dir->d_name);
    }
    printf("\n");
    closedir(d);
  }
}

void createFunc(char *filename) {
  FILE *fp;
  fp = fopen(filename, "w");

  if (fp == NULL || filename == NULL)
    printf("Error: Could not create the file\n");

  fclose(fp);
}

void inputFunc(char *filename, char *txt) {
  FILE *fp;
  fp = fopen(filename, "w");

  if (fp == NULL)
    printf("Error: Could not insert the data\n");

  fprintf(fp, "%s", txt);
  fclose(fp);
}

void renameFunc(char *oldname, char *newname) {
  if (rename(oldname, newname) == 0) {
    printf("File renamed successfully\n");    
  } else {
    printf("Error: Could not rename the file\n");
  }
}

void delFunc(char *filename) {
  if (remove(filename) == 0) {
    printf("The file has been deleted\n");
  } else {
    printf("Error: Could not delete the file\n");
  }
}