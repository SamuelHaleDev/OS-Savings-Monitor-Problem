#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

pthread_mutex_t mut;
pthread_cond_t cond;

float savingsAmount;
int numCustIn;
int numCustWaiting;

bool isSafe() {
    if (numCustIn > 0) {
        return false; // returns false as there is somebody writing currently
    } else return true;
}

// Write the withdrawal method
void withdraw(float amount) {
    pthread_mutex_lock(&mut);
    while(!isSafe() || (savingsAmount - amount) < 0) {
        pthread_cond_wait(&cond, &mut);
    }
    numCustIn += 1;
    savingsAmount -= amount;
    printf("Customer is withdrawing %f new Bank balance %f\n", amount, savingsAmount);
    numCustIn -= 1;
    pthread_mutex_unlock(&mut);
    sched_yield();
}
// Write the deposit method
void deposit(float amount) {
    pthread_mutex_lock(&mut);
    savingsAmount += amount;
    printf("Customer is depositing %f new Bank balance %f\n", amount, savingsAmount);
    pthread_mutex_unlock(&mut);
    sched_yield();
}
// Write the thread entry point 
void *OneCustomer(void *args) {
    pthread_mutex_lock(&mut);
    float amount;
    char userInput = 'q';
    while (userInput != 'f') {
        printf("Enter d to deposit | Enter w to withdraw | Enter f to exit: ");
        scanf("%c", &userInput); // gets userinput 
        printf("\n");
        if (userInput == 'd') {
            printf("Please enter an amount to deposit into your savings account: ");
            scanf("%f", amount);
            printf("\n");
            pthread_mutex_unlock(&mut);
            deposit(amount);
        } else if (userInput == 'w') {
            printf("please enter an amount to withdraw from your savings account: ");
            scanf("%f", amount);
            printf("\n");
            pthread_mutex_unlock(&mut);
            withdraw(amount);
        } else if (userInput == 'f') {
            printf("Goodbye!\n");
            pthread_mutex_unlock(&mut);
            break;
        }
    }
    pthread_mutex_unlock(&mut);
    pthread_exit(NULL);
    // I think you should do random numbers between 1 and 500
}



int main() {
    pthread_mutex_t mut;
    pthread_mutex_init(&mut, NULL);
    pthread_cond_t cond;
    pthread_cond_init(&cond, NULL);
    savingsAmount = 0;
    numCustIn = 0;
    numCustWaiting = 0;
    pthread_t cust1, cust2, cust3, cust4, cust5, cust6, cust7, cust8, cust9, cust10;
    // Initialize any arguments
    // Create threads for customers to withdraw or deposit
    pthread_create(&cust1, NULL, OneCustomer, NULL);
    pthread_create(&cust2, NULL, OneCustomer, NULL);
    pthread_create(&cust3, NULL, OneCustomer, NULL);
    pthread_create(&cust4, NULL, OneCustomer, NULL);
    pthread_create(&cust5, NULL, OneCustomer, NULL);
    pthread_create(&cust6, NULL, OneCustomer, NULL);
    pthread_create(&cust7, NULL, OneCustomer, NULL);
    pthread_create(&cust8, NULL, OneCustomer, NULL);
    pthread_create(&cust9, NULL, OneCustomer, NULL);
    pthread_create(&cust10, NULL, OneCustomer, NULL);

    pthread_join(cust1, NULL);
    pthread_join(cust2, NULL);
    pthread_join(cust3, NULL);
    pthread_join(cust4, NULL);
    pthread_join(cust5, NULL);
    pthread_join(cust6, NULL);
    pthread_join(cust7, NULL);
    pthread_join(cust8, NULL);
    pthread_join(cust9, NULL);

    // Entry point should be a function that will call for customers to deposit a random sum and withdrawal a random sum
    pthread_exit(0);
}