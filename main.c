#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LENGTH 50
#define ACCOUNT_FIELDS 4

typedef struct Account {
	int accountNumber;
	char* customerName;
	char* customerID;
	float amount;
} Account;


void split(char *string, const char *delimiter, char* result[ACCOUNT_FIELDS]); 
void printAccount(Account a);


void main()
{
	char delimiter[] = ",";
	char* result[ACCOUNT_FIELDS];
	char line[] = "1,Dor Bergel,563854125,1000";
	
	Account* try;
	
	split(line, delimiter, result);
	
}


void split(char *string, const char *delimiter, char* result[5]) {
    char *token = strtok(string, delimiter);
    int count = 0;
	while (token != NULL) {
        printf("%s\n", token);
		result[count++] = token;
        token = strtok(NULL, delimiter);
    }
}


void printAccount(Account a)
{
	printf("Account Number: %d\n", a.accountNumber);
	printf("Customer Name: %s\n", a.customerName);
	printf("Customer ID: %s\n", a.customerID);
	printf("Amount: %f\n", (float)a.amount);
}