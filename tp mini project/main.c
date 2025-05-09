#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char name[MAX];
    char acc_num[MAX];
    char password[MAX];
    float balance;
} Account;

Account accounts[MAX];
int total = 0;

void loadAccounts() {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) return;

    while (fscanf(file, "%s %s %s %f", accounts[total].name, accounts[total].acc_num,
                  accounts[total].password, &accounts[total].balance) ==4 ) {
        total++;
    }
    fclose(file);
}
void saveAccounts() {
    FILE *file = fopen("accounts.txt", "w");
    for (int i = 0; i < total; i++) {
        fprintf(file, "%s %s %s %.2f\n", accounts[i].name, accounts[i].acc_num,
                accounts[i].password, accounts[i].balance);
    }
    fclose(file);
}
int findAccount(char acc_num[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(accounts[i].acc_num, acc_num) == 0) {
            return i;
        }
    }
    return -1;
}
void createAccount() {
    Account acc;
    printf("Enter Name: ");
    scanf("%s", acc.name);
    printf("Enter Account Number: ");
    scanf("%s", acc.acc_num);
    if (findAccount(acc.acc_num) != -1) {
        printf("Account number already exists.\n");
        return;
    }
    printf("Set Password: ");
    scanf("%s", acc.password);
    acc.balance = 0.0;

    accounts[total++] = acc;
    saveAccounts();
    printf("Account Created Successfully\n");
}
void login() {
    char acc_num[MAX], password[MAX];
    printf("Enter Account Number: ");
    scanf("%s", acc_num);
    printf("Enter Password: ");
    scanf("%s", password);

    int index = findAccount(acc_num);
    if (index != -1 && strcmp(accounts[index].password, password) == 0) {
        int choice;
        printf("Login Successful!\n");
        do {
            printf("\n1. Deposit\n2. Transfer\n3. Check Balance\n4. Logout\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1: deposit(index); break;
                case 2: transfer(index); break;
                case 3: checkBalance(index); break;
                case 4: break;
                default: printf("Invalid option.\n");
            }
        } while (choice != 4);
    } else {
        printf("Invalid credentials.\n");
    }
}
void deposit(int index) {
    float amt;
    printf("Enter amount to deposit: ");
    scanf("%f", &amt);
    if (amt > 0) {
        accounts[index].balance += amt;
        printf("Deposit successful. New Balance: %.2f\n", accounts[index].balance);
    } else {
        printf("Invalid amount.\n");
    }
    saveAccounts();
}
void transfer(int index) {
    char to_acc[20];
    float amt;
    printf("Enter recipient account number: ");
    scanf("%s", to_acc);
    int to_index = findAccount(to_acc);

    if (to_index == -1) {
        printf("Recipient not found.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &amt);
    if (amt > 0 && accounts[index].balance >= amt)  {
        accounts[index].balance -= amt;
        accounts[to_index].balance += amt;
        printf("Transfer successful.\n");
        saveAccounts();
    } else {
        printf("Insufficient balance or invalid amount.\n");
    }
}
void checkBalance(int index) {
    printf("Your current balance is: %.2f\n", accounts[index].balance);
}
void deleteAccount() {
    char acc_num[20];
    printf("Enter account number to delete: ");
    scanf("%s", acc_num);
    int index = findAccount(acc_num);

    if (index != -1 ) {
        for (int i = index; i < total - 1; i++) {
            accounts[i] = accounts[i + 1];
        }
        total--;
        saveAccounts();
        printf("Account deleted.\n");
    } else {
        printf("Account not found .\n");
    }
}

int main() {
    int choice;
    loadAccounts();

    while (1) {
        printf("\n--------------------------------------------- Welcome to Our Bank ------------------------------------------------\n");
        printf("1. Create Account\n");
        printf("2. Login to Account\n");
        printf("3. Delete Account\n");
        printf("4. Quit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: login(); break;
            case 3: deleteAccount(); break;
            case 4: saveAccounts(); exit(0);
            default: printf("unavilable choise.\n");
        }
    }
    return 0;
}





