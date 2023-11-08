#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define LINE_LENGTH 100
#define ACCOUNT_FIELDS 4

typedef struct Account {
	int accountNumber;
	char* customerName;
	char* customerID;
	char* amount;
} Account;


void splitLine(char* string, const char* delimiter, char* result[ACCOUNT_FIELDS]);
void printAccount(Account a);
int lineCount();

void main()
{
	char delimiter[] = ",";
	char* result[ACCOUNT_FIELDS];
	//char line[] = "1,Dor Bergel,563854125,1000";
	char line[LINE_LENGTH];
	Account** accountsArray;
	int accountsNum;
	int i;
	FILE* fp;

	accountsNum = lineCount();

	accountsArray = (Account**)malloc(sizeof(Account) * accountsNum);

	fp = fopen("customer.txt", "r");

	for (i = 0; i < accountsNum; i++)
	{
		fgets(line, LINE_LENGTH, fp);
		accountsArray[i] = (Account*)malloc(sizeof(Account));
		splitLine(line, delimiter, result);
		accountsArray[i]->accountNumber = (int)*result[0];
		accountsArray[i]->customerName = result[1];
		accountsArray[i]->customerID = result[2];
		accountsArray[i]->amount = result[3];

		printAccount(*accountsArray[i]);

		printf("---------------------\n");
	}






}


void splitLine(char* string, const char* delimiter, char* result[5]) {
	char* token = strtok(string, delimiter);
	int count = 0;
	while (token != NULL) {
		//printf("%s\n", token);
		result[count++] = token;
		token = strtok(NULL, delimiter);
	}
}


void printAccount(Account a)
{
	printf("Account Number: %d\n", a.accountNumber);
	printf("Customer Name: %s\n", a.customerName);
	printf("Customer ID: %s\n", a.customerID);
	printf("Amount: %s\n", a.amount);
}


int lineCount() {

	int lines = 0;
	char ch;
	FILE* fp = fopen("customer.txt", "r");

	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (ch == '\n')
		{
			lines++;
		}
	}

	fclose(fp);

	return lines;
}