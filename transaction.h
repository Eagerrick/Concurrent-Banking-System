#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "bank.h"

typedef struct Transactions {
    int thread_id;
    BankAccount *accounts;
    int num_accounts;
    int num_transactions;
} Transactions;

void *customer_thread(void *arg);

#endif