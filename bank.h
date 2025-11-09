#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct BankAccount {
    int account_id;
    double balance;
    pthread_mutex_t lock;
} BankAccount;

void init_accounts(BankAccount accounts[], int num_accounts, double balance);
void deposit(BankAccount *account, double amount);
int withdraw(BankAccount *account, double amount);
int transfer(BankAccount *from, BankAccount *to, double amount);
void print_balances(BankAccount accounts[], int num_accounts);

#endif