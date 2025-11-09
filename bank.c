#include "bank.h"

void init_accounts(BankAccount accounts[], int num_accounts, double balance) {
    for (int i = 0; i < num_accounts; i++) {
        accounts[i].account_id = i;     // Assigns a unique ID to each account
        accounts[i].balance = balance; // Initializes balance
        pthread_mutex_init(&accounts[i].lock, NULL); // Initializes the mutex lock
    }
}

void deposit(BankAccount *account, double amount) {
    pthread_mutex_lock(&account->lock); // Locks the account for thread operation
    account->balance += amount;  // Updates the balance
    pthread_mutex_unlock(&account->lock); // Unlocks the account
}

int withdraw(BankAccount *account, double amount) {
    pthread_mutex_lock(&account->lock); // Locks the account for thread operation
    if (account->balance >= amount) { // Checks for sufficient funds
        account->balance -= amount; // Updates the balance
        pthread_mutex_unlock(&account->lock); // Unlocks the account
        return 1; // Withdrawal successful
    }
    else {
        pthread_mutex_unlock(&account->lock); // Unlocks the account
        return 0; // Withdrawal failed due to insufficient funds
    }
}

int transfer(BankAccount *from, BankAccount *to, double amount) {  
    // Lock both accounts
    pthread_mutex_lock(&from->lock);
    pthread_mutex_lock(&to->lock);

    if (from->balance >= amount) { // Checks for sufficient funds
        // Updates balances
        from->balance -= amount;
        to->balance += amount;

        // Unlocks both accounts
        pthread_mutex_unlock(&from->lock);
        pthread_mutex_unlock(&to->lock);
        return 1; // Transfer successful
    }
    else {
        // Unlocks both accounts
        pthread_mutex_unlock(&from->lock);
        pthread_mutex_unlock(&to->lock);
        return 0; // Transfer failed due to insufficient funds
    }
}

void print_balances(BankAccount accounts[], int num_accounts) {
    for (int i = 0; i < num_accounts; i++) {
        pthread_mutex_lock(&accounts[i].lock); // Locks the account for thread operation
        printf("Account %d: Balance = %.2f\n", accounts[i].account_id, accounts[i].balance); // Prints account balance
        pthread_mutex_unlock(&accounts[i].lock); // Unlocks the account
    }
}