#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_DEBTS 100

//store debt info/details
typedef struct Record{
	char title[50]; //debt title
	double amount; //debt amount, how much is the debt
	double intRate; //interest rate, per month?
	double minPayment; //how much you are willing to pay your debt 
} rec;

//GLOBALS
rec debtRecords[MAX_DEBTS]; //array that stores individual debt info
int debtCount = 0, i; 
double income;
FILE *file; 

//FOR TEXT COLORS
void red () {
	printf("\033[0;31m");
}
void green(){
	printf("\033[0;32m");
}
void yellow(){
	printf("\033[0;33m");
}
void reset () {
  printf("\033[0m");
}

//GOES BACK TO MAIN SCREEN
void goBack(){
	yellow();
	printf("\nPress any key to go back.");
	reset();
 	_getch();
    system("cls");
}

//DISPLAYS EXISTING DATA SCREEN (MAIN MENU)
void mainMenu(){
	yellow();
	printf("WELCOME TO DEBT REPAYMENT PLANNER!\n");
	reset();
	printf("\t[1] View Existing File\n");
	printf("\t[2] Create New File\n");
	printf("\t[0] Exit Program\n");
}

//DISPLAYS PROGRAM PROPER
void secondMenu(){
	printf("DEBT REPAYMENT PLANNER\n");
	printf("\t[1] Add Monthly Income\n");
	printf("\t[2] Add Debt Details\n");
	printf("\t[3] View All Debts\n");
	printf("\t[4] View Repayment Plan\n");
	printf("\t[5] Upcoming Payment Deadlines\n");
	printf("\t[6] Save File\n");
	printf("\t[0] Back to Menu\n");
}

//ERROR CATCHING FOR CHARACTER INPUTS (MAIN MENU)
int readInteger() {
    int value;
    while (1) {
    	
        if (scanf("%d", &value) != 1) {
            red(); 
            printf("Invalid Choice! Try again.\n");
            reset(); 
            sleep(1.5);
            system("cls");
            mainMenu();
			printf("\nEnter choice: ");
            // Clear the invalid input
            while (getchar() != '\n'); // Clear the input buffer
        } else {
            while (getchar() != '\n'); // Clear any remaining input
            return value;
        }
    }
}

//ERROR CATCHING FOR CHARACTER INPUTS (SECOND MENU)
int readInteger2() {
    int value;
    while (1) {
    	
        if (scanf("%d", &value) != 1) {
            red(); 
            printf("Invalid Choice! Try again.\n");
            reset(); 
            sleep(1.5);
            system("cls");
            secondMenu();
			printf("\nEnter choice: ");
            // Clear the invalid input
            while (getchar() != '\n'); // Clear the input buffer
        } else {
            while (getchar() != '\n'); // Clear any remaining input
            return value;
        }
    }
}


void monthlyIncome(){
	printf("Enter your Monthly Income: ");
	scanf("%lf", &income);
	
	green();
	printf("\nMonthly Income has been saved successfully!\n");
	reset();
	
	goBack();
}

void addDebt(){
	rec debt;
	
	//Getting debt info
	printf("INPUT DEBT DETAILS\n");
	
	//getchar();  // This reads the stray newline character from the buffer
    
    // Reading the debt title (with spaces)
    printf("Debt Title: ");
    fgets(debt.title, 100, stdin);
    
    // Remove the trailing newline character if it exists
    size_t len = strlen(debt.title);
    if (len > 0 && debt.title[len - 1] == '\n') {
        debt.title[len - 1] = '\0';
    }
	
	printf("Debt Amount: ");
	scanf(" %lf", &debt.amount);
	printf("Interest Rate: ");
	scanf(" %lf", &debt.intRate);
	printf("Amount of payment(per Month): ");
	scanf(" %lf", &debt.minPayment);
	
	//Adding Debt info in the global array
	debtRecords[debtCount++] = debt;
	
	green();
	printf("\nDebt #%d - %s has been added successfully!\n", debtCount, debt.title);
	reset();
	
	goBack();	
}

void viewDebts(){
	if (debtCount == 0){
		red();
		printf("No debt details to display.\n");
		reset();
        return;
	}
	
	//will display all debts (ATM)
	for (i = 0; i < debtCount; i++){
		printf("DEBT NO. %d\n", i + 1);
		printf("Debt Title: %s\n", debtRecords[i].title);
		printf("Debt Amount: Php %.2lf\n", debtRecords[i].amount);
		printf("Interest Rate: %.2lf%%\n", debtRecords[i].intRate * 100);
		printf("Amount of payment(per Month): %.2lf\n\n", debtRecords[i].minPayment);
	}
	
	yellow();
	printf("---END OF LIST---");
	reset();
	
	goBack();
}

//MAIN PROGRAM
int main(){
	int choice;
	Menu:
	do{
		mainMenu();
		
		printf("\nEnter choice: ");
		choice = readInteger();
		
		//NOTE: make a file folder dedicated for debt details
		switch (choice) {
			//VIEW EXISTING FILE
			case 1:
				system("cls");
				//file = fopen("name of file", "mode (r/w/rw/a)");
				goto SecondMenu;
			case 2:
				system("cls");	
				goto SecondMenu;
			//EXIT PROGRAM
			case 0:
				yellow();
				printf("\nExiting Program...");
				reset();
				break;
			
			//ERROR TRAPPING
			default:
            	red(); 
                printf("Invalid Choice! Try again.\n");
                reset(); 
                sleep(1.5);
                system("cls");
		}
	}
	while (choice != 0); 
    return 0;
	
	int choice2;
	SecondMenu:
	do{
    	secondMenu(); //Display second screen
                             
        printf("\nEnter choice: ");
        choice2 = readInteger2();
        switch (choice2) {
            case 1:
            	system("cls");
                monthlyIncome();
                break;
            case 2:
                system("cls");
                addDebt();
                break;
             case 3:
                system("cls");
                viewDebts();
                break;
            case 4:
                system("cls");
                //view repayment plan function
                break;
            case 5:
            	system("cls");
            	//upcoming payment deadlines function
            	//hierarchical order (largest interest to lowest)
            	break;
            case 6:
            	system("cls");
            	//Save file
            	break;
            case 0:
            	yellow();
                printf("Going Back to Main Menu.\n");
                reset();
                sleep(1.5);
                system("cls");
                goto Menu;
                break;
            default:
            	red(); 
                printf("Invalid Choice! Try again.\n");
                reset(); 
                sleep(1.5);
                system("cls");
        }
    } 
	while (1); 
}