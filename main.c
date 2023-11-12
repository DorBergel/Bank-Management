/*
This code has written by Dor Bergel. 
This code expect valid input and not handeling with wrong types.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

// Constatnts values
#define LINE_LENGTH 100
#define ACCOUNT_FIELDS 4
#define BUFFER_SIZE 100


typedef struct Account {
    char* accountNumber;
    char* customerName;
    char* customerID;
    char* amount;
} Account;

// Prototypes
void loadAccounts(Account** accountsArray, int accountsCount);
int lineCount();
void printAccount(Account a);
void printAll(Account** accountsArray, int accountsCount);
void addAccount(Account** accountsArray, int* accountsCount);
void saveAccounts(Account** accountsArray, int accountCount);
void removeAccount(Account** accountsArray, int* accountCount);
void editAccount(Account** accountsArray, int accountCount);
void transact(Account** accountsArray, int accountsCount);
void clearBuffer();

int main()
{
    Account* accountsArray;
    int accountsCount = lineCount();
    int choice = 0;
    char temp;
	
    accountsArray = malloc(sizeof(Account) * accountsCount);
    loadAccounts(&accountsArray, accountsCount);

    while (choice != 7) {

        system("cls");

        printf("1- See all accounts info.\n");
        printf("2- Add account.\n");
        printf("3- Edit existing account.\n");
        printf("4- Remove account.\n");
        printf("5- Create new Transaction\n");
        printf("6- Save Changes\n");
        printf("7- Exit\n");
        printf("\n\nHow can I help you: ");
        scanf("%d", &choice);
		
        switch (choice)
        {
        case 1:
			// Print all accounts case
            system("cls");
            printAll(&accountsArray, accountsCount);
            printf("\n\n\n\n");
			printf("Press any key to continue\n");
			getch();
            continue;
        case 2:
			// Add new account case
            system("cls");
            addAccount(&accountsArray, &accountsCount);
            printf("\n\n\n\n");
            printf("Press any key to continue\n");
			getch();
            continue;
        case 3:
			// Edit existing account case
            system("cls");
            editAccount(&accountsArray, accountsCount);
            printf("\n\n\n\n");
            printf("Press any key to continue\n");
			getch();
            continue;
        case 4:
			// Remove existing account case
            system("cls");
            removeAccount(&accountsArray, &accountsCount);
            printf("\n\n\n\n");
            printf("Press any key to continue\n");
			getch();
            continue;
        case 5:
			// Make new transaction case
            system("cls");
            transact(&accountsArray, accountsCount);
            printf("\n\n\n\n");
			printf("Press any key to continue\n");
			getch();
            continue;
        case 6:
			// Exit
            system("cls");
            saveAccounts(&accountsArray, accountsCount);
            printf("\n\n\n\n");
            printf("Press any key to continue\n");
			getch();
            continue;
        default:
            break;
        }
        
        
    }
   
}

void loadAccounts(Account** accountsArray, int accountsCount)
{
	/*
	This function load the existing customer from txt file by specific pattern
	Input: accountsArray, accountsCount
	Output: None, update the accountsArray
	*/
    int i;
    FILE* fp = fopen("customer.txt", "r");
    char line[LINE_LENGTH];

    for (i = 0; i < accountsCount; i++) {
        fgets(line, LINE_LENGTH, fp);

        (*accountsArray)[i].accountNumber = malloc(BUFFER_SIZE);
        (*accountsArray)[i].customerName = malloc(BUFFER_SIZE);
        (*accountsArray)[i].customerID = malloc(BUFFER_SIZE);
        (*accountsArray)[i].amount = malloc(BUFFER_SIZE);

        sscanf(line, "%[^,],%[^,],%[^,],%s",
            (*accountsArray)[i].accountNumber,
            (*accountsArray)[i].customerName,
            (*accountsArray)[i].customerID,
            (*accountsArray)[i].amount);
    }
}

int lineCount() {
	
	/*
	Count how much line(=accounts) there is in customer.txt
	Input: None
	Output: linesCount (=accountsCount)
	*/
    char line[LINE_LENGTH];
    int linesC = 0;
    FILE* fp = fopen("customer.txt", "r");
    while (fgets(line, LINE_LENGTH, fp)) {
        linesC++;
    }
    fclose(fp);

    return linesC;
}

void printAccount(Account a)
{
	
	/*
	Print specific account - used for debug
	Input: Account
	Output: None
	*/
    printf("Account Number: %s\n", a.accountNumber);
    printf("Customer Name: %s\n", a.customerName);
    printf("Customer ID: %s\n", a.customerID);
    printf("Amount: %s\n", a.amount);
    printf("-------------------\n");
}

void printAll(Account** accountsArray, int accountsCount)
{
	
	/*
	Print all accounts
	*/
    for (int i = 0; i < accountsCount; i++) {
        printAccount((*accountsArray)[i]);
    }
}

void addAccount(Account** accountsArray, int* accountsCount)
{
	
	/*
	Ask for necesserry details for create new account
	Input: accountsArray, accountsCount
	Output: None (just update the accountsArray)
	*/
    (*accountsCount)++;
    *accountsArray = realloc(*accountsArray, sizeof(Account) * (*accountsCount));

    (*accountsArray)[(*accountsCount) - 1].accountNumber = malloc(BUFFER_SIZE);
    (*accountsArray)[(*accountsCount) - 1].customerName = malloc(BUFFER_SIZE);
    (*accountsArray)[(*accountsCount) - 1].customerID = malloc(BUFFER_SIZE);
    (*accountsArray)[(*accountsCount) - 1].amount = malloc(BUFFER_SIZE);

    printf("Please enter new account number: ");
    scanf("%s", (*accountsArray)[(*accountsCount) - 1].accountNumber);
	fseek(stdin,0,SEEK_END);
    printf("Please enter new customer name: ");
    scanf("%s", (*accountsArray)[(*accountsCount) - 1].customerName);
	fseek(stdin,0,SEEK_END);
    printf("Please enter new customer ID: ");
    scanf("%s", (*accountsArray)[(*accountsCount) - 1].customerID);
	fseek(stdin,0,SEEK_END);
    printf("Please enter new customer amount: ");
    scanf("%s", (*accountsArray)[(*accountsCount) - 1].amount);
	fseek(stdin,0,SEEK_END);

}

void saveAccounts(Account** accountsArray, int accountCount)
{
	
	/*
	Save the current accountsArray to customer.txt in the readable pattern
	Input: accountsArray, accountsCount
	Output: None
	*/
    FILE* fp = fopen("customer.txt", "w");
    int i;

    for (i = 0; i < accountCount; i++) {
        fprintf(fp, "%s,%s,%s,%s\n", (*accountsArray)[i].accountNumber, (*accountsArray)[i].customerName, (*accountsArray)[i].customerID, (*accountsArray)[i].amount);
    }

}

void removeAccount(Account** accountsArray, int* accountCount)
{
	
	/*
	Remove account by his number from the accountsArray
	Input: accountsArray, accountsCount
	Output: None
	*/
    int i;
    char delAccount[BUFFER_SIZE];
    int flag = 0;

    printf("Please enter the account number you would like to remove: ");
    scanf("%s", delAccount);

    for (i = 0; i < (*accountCount); i++) {
        if (strcmp(delAccount, (*accountsArray)[i].accountNumber) == 0) {
            strcpy((*accountsArray)[i].accountNumber, (*accountsArray)[(*accountCount) - 1].accountNumber);
            strcpy((*accountsArray)[i].customerName, (*accountsArray)[(*accountCount) - 1].customerName);
            strcpy((*accountsArray)[i].customerID, (*accountsArray)[(*accountCount) - 1].customerID);
            strcpy((*accountsArray)[i].amount, (*accountsArray)[(*accountCount) - 1].amount);
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        printf("Account number not found.\n");
    }
    else {
        (*accountCount)--;
        *accountsArray = realloc(*accountsArray, sizeof(Account) * (*accountCount));

        printf("Account deleted successfully.\n");
    }
}

void editAccount(Account** accountsArray, int accountCount)
{
	/*
	Edit existing account detailes
	Input: accountsArray, accountsCount
	Output: None
	*/
    int i;
    char edAccount[BUFFER_SIZE];
    char tempString[BUFFER_SIZE];
    int field = 0;

    printf("Please enter which account (by his number) would you like to edit: ");
    scanf("%s", edAccount);

    for (i = 0; i < accountCount; i++) {
        if (strcmp(edAccount, (*accountsArray)[i].accountNumber) == 0)
        {
            printf("1- update customer name\n");
            printf("2- update customer ID\n");
            printf("3- update account amount\n");
            printf("Please enter which field would you like to update: ");
            scanf("%d", &field);

            switch (field)
            {
                case 1:
                    printf("Please enter the new name: ");
                    scanf("%s", tempString);
                    strcpy((*accountsArray)[i].customerName, tempString);
                    break;
                case 2:
                    printf("Please enter the new ID: ");
                    scanf("%s", tempString);
                    strcpy((*accountsArray)[i].customerID, tempString);
                    break;
                case 3:
                    printf("Please enter the new amount: ");
                    scanf("%s", tempString);
                    strcpy((*accountsArray)[i].amount, tempString);
                    break;
                default:
                    printf("Didn't find your choice\n");
                    break;
            }
        }
    }
}

void transact(Account** accountsArray, int accountsCount)
{
	
	/*
	Make new transaction between to accounts
	Input: accountsArray, accountsCount
	Output: None
	*/
    int i;
    char transmit[BUFFER_SIZE];
    char recieve[BUFFER_SIZE];
    int transaction = 0;
    int temp;
    
    printf("Please enter your account number: ");
    scanf("%s", transmit);

    printf("Please enter who would you like transfer to: ");
    scanf("%s", recieve);

    printf("How much money whould you like to transfer: ");
    scanf("%d", &transaction);

    for (i = 0; i < accountsCount; i++)
    {
        if (strcmp(transmit, (*accountsArray)[i].accountNumber) == 0)
        {
            temp = atoi((*accountsArray)[i].amount);
            temp -= transaction;
            //itoa(temp, transmit, 10);
			sprintf(transmit, "%d", temp);
            strcpy((*accountsArray)[i].amount, transmit);
            break;
        }
    }

    for (i = 0; i < accountsCount; i++)
    {
        if (strcmp(recieve, (*accountsArray)[i].accountNumber) == 0)
        {
            temp = atoi((*accountsArray)[i].amount);
            temp += transaction;
            //itoa(temp, recieve, 10);
			sprintf(recieve, "%d", temp);
            strcpy((*accountsArray)[i].amount, recieve);
            break;
        }
    }

}
