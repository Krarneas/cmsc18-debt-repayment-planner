#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_DEBTS 10

// Structure to store debt information
typedef struct {
    char name[50];
    double amount;       // Debt amount
    double interestRate; // Annual interest rate in percentage
    double minPayment;   // Minimum monthly payment
} Debt;

// Function prototypes
void inputDebts(Debt debts[], int *count);
void calculateRepaymentPlan(Debt debts[], int count, double monthlyIncome);
void displaySummary(double totalDebt, double totalInterest);

int main() {
    Debt debts[MAX_DEBTS];
    int debtCount = 0;
    double monthlyIncome;

    printf("Debt Repayment Planner\n");
    printf("=======================\n");

    // Input user's monthly income
    printf("Enter your monthly income: $");
    scanf(" %lf", &monthlyIncome);

    // Input debt details
    inputDebts(debts, &debtCount);

    // Calculate and display repayment plan
    calculateRepaymentPlan(debts, debtCount, monthlyIncome);

    return 0;
}

// Function to input debt details
void inputDebts(Debt debts[], int *count) {
    int numDebts;

    printf("\nEnter the number of debts (max %d): ", MAX_DEBTS);
    scanf("%d", &numDebts);

    if (numDebts > MAX_DEBTS || numDebts <= 0) {
        printf("Invalid number of debts! Please restart the program.\n");
        exit(1);
    }

    getchar(); // Clear the newline character left by previous scanf

    for (int i = 0; i < numDebts; i++) {
        printf("\nDebt %d:\n", i + 1);

        // Use fgets for reading string input to handle spaces
        printf("Enter debt name: ");
        fgets(debts[i].name, sizeof(debts[i].name), stdin);
        debts[i].name[strcspn(debts[i].name, "\n")] = '\0'; // Remove newline

        printf("Enter amount owed: $");
        scanf(" %lf", &debts[i].amount);

        printf("Enter annual interest rate (%%): ");
        scanf(" %lf", &debts[i].interestRate);

        printf("Enter minimum monthly payment: $");
        scanf(" %lf", &debts[i].minPayment);

        getchar(); // Clear the newline character after reading numbers
    }

    *count = numDebts;
}

// Function to calculate repayment plan
void calculateRepaymentPlan(Debt debts[], int count, double monthlyIncome) {
    double totalDebt = 0.0, totalInterest = 0.0;

    printf("\nRepayment Plan\n");
    printf("==============\n");

    for (int i = 0; i < count; i++) {
        printf("\nDebt: %s\n", debts[i].name);
        printf("Initial Amount: $%.2f\n", debts[i].amount);

        double balance = debts[i].amount;
        double monthlyInterestRate = debts[i].interestRate / 12 / 100;
        int months = 0;
        double totalDebtInterest = 0.0;

        while (balance > 0) {
            double interest = balance * monthlyInterestRate;
            totalDebtInterest += interest;

            double payment = (balance + interest < debts[i].minPayment) ? (balance + interest) : debts[i].minPayment;

            if (payment <= interest) {
                printf("Warning: Insufficient payment to cover interest. Debt will grow!\n");
                break;
            }

            balance += interest - payment;
            months++;
        }

        totalInterest += totalDebtInterest;
        totalDebt += debts[i].amount;

        printf("Time to Payoff: %d months\n", months);
        printf("Total Interest Paid: $%.2f\n", totalDebtInterest);
    }

    // Display overall summary
    displaySummary(totalDebt, totalInterest);
}

// Function to display the summary of all debts
void displaySummary(double totalDebt, double totalInterest) {
    printf("\nSummary\n");
    printf("=======\n");
    printf("Total Debt: $%.2f\n", totalDebt);
    printf("Total Interest Paid: $%.2f\n", totalInterest);
}
