#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define PORT 8080
#define MAX_LIMIT 1024

char *getInput();
   
int main(int argc, char const *argv[])
{
	int msg_count = 3;
		int sock = 0, valread;
		struct sockaddr_in serv_addr;
		// char *hello = getInput();
		// char buffer[MAX_LIMIT] = {0};
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			printf("\n Socket creation error \n");
			return -1;
		}
	
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);
		
		// Convert IPv4 and IPv6 addresses from text to binary form
		if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
		{
			printf("\nInvalid address/ Address not supported \n");
			return -1;
		}
	
		if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		{
			printf("\nConnection Failed \n");
			return -1;
		}
	while (msg_count > 0) {
		char *hello = getInput();
		char buffer[MAX_LIMIT] = {0};
		send(sock , hello , strlen(hello) , 0 );
		printf("Client: %s\n", hello);
		valread = read( sock , buffer, MAX_LIMIT);
		printf("Server: %s\n",buffer );
		free(hello);
		msg_count--;
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
