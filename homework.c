#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define MAX_STRING_LENGTH 100

typedef struct {
    char date[MAX_STRING_LENGTH];
    char category[MAX_STRING_LENGTH];
    double amount;
    char memo[MAX_STRING_LENGTH];
} Record;

Record records[MAX_RECORDS];
int record_count = 0;

void add_record() {
    if (record_count >= MAX_RECORDS) {
        printf("Cannot add more records. Maximum limit reached.\n");
        return;
    }

    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", records[record_count].date);
    printf("Enter category: ");
    scanf("%s", records[record_count].category);
    printf("Enter amount: ");
    scanf("%lf", &records[record_count].amount);
    printf("Enter memo: ");
    scanf(" %[^\n]", records[record_count].memo);

    record_count++;
    printf("Record added successfully.\n");
}

void show_transaction_history() {
    printf("\nTransaction History:\n");
    printf("Date       | Category    | Amount   | Memo\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < record_count; i++) {
        printf("%-10s | %-10s | %8.2f | %s\n", records[i].date, records[i].category, records[i].amount, records[i].memo);
    }
}

void calculate_balance() {
    double balance = 0.0;
    for (int i = 0; i < record_count; i++) {
        balance += records[i].amount;
    }
    printf("\nCurrent Balance: %.2f\n", balance);
}

int main() {
    int choice;

    while (1) {
        printf("\nBudget Tracker Menu:\n");
        printf("1. Add Income/Expense Record\n");
        printf("2. Show Transaction History\n");
        printf("3. Calculate and Display Balance\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_record();
                break;
            case 2:
                show_transaction_history();
                break;
            case 3:
                calculate_balance();
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}