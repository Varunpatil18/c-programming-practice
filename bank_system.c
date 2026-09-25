#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int acc_no;
    char name[50];
    float balance;
} Account;

void create_account();
void display_all();
void search_account();
void deposit_money();
void withdraw_money();

int main() {
    int choice;

    while (1) {
        printf("\n=========================================\n");
        printf("     BANK ACCOUNT MANAGEMENT SYSTEM      \n");
        printf("=========================================\n");
        printf("1. Create New Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Search Account by Number\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                display_all();
                break;
            case 3:
                search_account();
                break;
            case 4:
                deposit_money();
                break;
            case 5:
                withdraw_money();
                break;
            case 6:
                printf("\nThank you for using the Banking System!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please select 1 to 6.\n");
        }
    }
    return 0;
}

void create_account() {
    FILE *fp = fopen("accounts.txt", "a");
    if (fp == NULL) {
        printf("\nError opening database file!\n");
        return;
    }

    Account acc;
    printf("\n--- Create Account ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc.acc_no);
    printf("Enter Account Holder Name: ");
    scanf("%s", acc.name);
    printf("Enter Initial Deposit: ");
    scanf("%f", &acc.balance);

    fprintf(fp, "%d %s %.2f\n", acc.acc_no, acc.name, acc.balance);
    fclose(fp);

    printf("\nAccount created and saved successfully!\n");
}

void display_all() {
    FILE *fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("\nNo records found or file does not exist yet.\n");
        return;
    }

    Account acc;
    printf("\n--- All Registered Accounts ---\n");
    printf("%-12s %-20s %-10s\n", "Acc No", "Name", "Balance");
    printf("-----------------------------------------\n");

    while (fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) == 3) {
        printf("%-12d %-20s %-10.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
}

void search_account() {
    FILE *fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("\nDatabase file empty or not found.\n");
        return;
    }

    int search_no, found = 0;
    Account acc;

    printf("\nEnter Account Number to Search: ");
    scanf("%d", &search_no);

    while (fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) == 3) {
        if (acc.acc_no == search_no) {
            printf("\n--- Account Found ---\n");
            printf("Account Number : %d\n", acc.acc_no);
            printf("Holder Name    : %s\n", acc.name);
            printf("Balance        : %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nAccount number %d not found.\n", search_no);
    }

    fclose(fp);
}

void deposit_money() {
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("\nDatabase error.\n");
        return;
    }

    int target_no, found = 0;
    float amount;
    Account acc;

    printf("\nEnter Account Number for Deposit: ");
    scanf("%d", &target_no);

    while (fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) == 3) {
   if (acc.acc_no == target_no) {
            printf("Current Balance: %.2f\n", acc.balance);
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            found = 1;
            printf("Deposit successful! New Balance: %.2f\n", acc.balance);
        }
        fprintf(temp, "%d %s %.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        printf("\nAccount number %d not found.\n", target_no);
    }
}

void withdraw_money() {
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("\nDatabase error.\n");
        return;
    }

    int target_no, found = 0;
    float amount;
    Account acc;

    printf("\nEnter Account Number for Withdrawal: ");
    scanf("%d", &target_no);

    while (fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) == 3) {
        if (acc.acc_no == target_no) {
            printf("Current Balance: %.2f\n", acc.balance);
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);
            if (amount > acc.balance) {
                printf("Insufficient balance!\n");
            } else {
                acc.balance -= amount;
                printf("Withdrawal successful! New Balance: %.2f\n", acc.balance);
            }
            found = 1;
        }
        fprintf(temp, "%d %s %.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        printf("\nAccount number %d not found.\n", target_no);
    }
}