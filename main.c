#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "bank.h"
#include "transaction.h"

int main() {
    srand(time(NULL));
    int num_accounts = 10;
    int num_threads = 5;
    int num_transactions = 20;
    BankAccount *accounts = malloc(num_accounts * sizeof(BankAccount));
    init_accounts(accounts, num_accounts, 200.0);
    pthread_t threads[num_threads];
    Transactions thread_data[num_threads];
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].accounts = accounts;
        thread_data[i].num_accounts = num_accounts;
        thread_data[i].num_transactions = num_transactions;
        pthread_create(&threads[i], NULL, customer_thread, (void *)&thread_data[i]);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    print_balances(accounts, num_accounts);
    free(accounts);
    return 0;
}