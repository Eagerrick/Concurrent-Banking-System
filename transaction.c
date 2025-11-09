#include "transaction.h"

void *customer_thread(void *arg) {
    srand(time(NULL));
    Transactions *transactions = (Transactions *)arg;
    int tid = transactions->thread_id;
    BankAccount *accounts = transactions->accounts;
    int num_accounts = transactions->num_accounts;
    int num_transactions = transactions->num_transactions;

    for (int i = 0; i < num_transactions; i++) {
        int account_id = rand() % num_accounts;
        double amount = (rand() % 1000) / 10.0;
        int op = rand() % 3; 

        switch(op) {
            case 0:
                deposit(&accounts[account_id], amount);
                printf("Thread %d: Deposited %.2f to account %d\n", tid, amount, account_id);
                break;
            case 1:
                if (withdraw(&accounts[account_id], amount)) {
                    printf("Thread %d: Withdrew %.2f from account %d\n", tid, amount, account_id);
                } else {
                    printf("Thread %d: Failed to withdraw %.2f from account %d (Insufficient funds)\n", tid, amount, account_id);
                }
                break;
            case 2: {
                int to_account_id;
                do {
                    to_account_id = rand() % num_accounts;
                } while (to_account_id == account_id);

                if (transfer(&accounts[account_id], &accounts[to_account_id], amount)) {
                    printf("Thread %d: Transferred %.2f from account %d to account %d\n", tid, amount, account_id, to_account_id);
                } else {
                    printf("Thread %d: Failed to transfer %.2f from account %d to account %d (Insufficient funds)\n", tid, amount, account_id, to_account_id);
                }
                break;
            }
        }
    }
    return NULL;
}