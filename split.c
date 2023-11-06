#include <stdio.h>
#include <string.h>

void split(char *string, const char *delimiter, char* result[5]) {
    char *token = strtok(string, delimiter);
    int count = 0;
	while (token != NULL) {
        printf("%s\n", token);
		result[count++] = token;
        token = strtok(NULL, delimiter);
    }
}

int main() {
    char str[] = "Hello,World,How,Are,You";
    char delimiter[] = ",";
    char* result[5];
    split(str, delimiter, result);
    
    for(int i=0;i<5;i++)
	{
		printf("i=%d ----> %s\n", i, result[i]);
	}
	
    return 0;
}


