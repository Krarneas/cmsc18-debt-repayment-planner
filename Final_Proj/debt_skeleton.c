#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
char readFile[1000];


//to easily locate the file
//change the fileName Path corresponding to your Device Location Choice
char fileName[100] = {"C:\\Users\\Infinite\\Desktop\\"};
char inputFile[50];

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
	printf("\t[1] Open Existing File\n");
	printf("\t[2] Create New File\n");
	printf("\t[0] Exit Program\n");
}

//DISPLAYS PROGRAM PROPER
void secondMenu(){
	printf("DEBT REPAYMENT PLANNER\n");
	printf("\t[1] Input Monthly Income\n");
	printf("\t[2] Add Debt Details\n");
	printf("\t[3] View All Debts\n");
	printf("\t[4] View Repayment Plan\n");
	printf("\t[5] Change Debt Information\n");
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
    fgets(debt.title, sizeof(debt.title), stdin);
    
    debt.title[strcspn(debt.title, "\n")] = '\0'; // Remove newline
	
	printf("Debt Amount: ");
	scanf(" %lf", &debt.amount);
	printf("Interest Rate (%%): ");
	scanf(" %lf", &debt.intRate);
	printf("Amount of payment (per Month): ");
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
		printf("Interest Rate (%%): %.2lf%%\n", debtRecords[i].intRate);
		printf("Amount of payment (per Month): Php %.2lf\n\n", debtRecords[i].minPayment);
	}
	
	yellow();
	printf("---END OF LIST---");
	reset();
	
	goBack();
}

void calculateRepaymentPlan(){
	double totalDebt = 0.0, totalInt = 0.0; 
	
	yellow();
	printf("REPAYMENT PLAN\n");
	reset();
	
	for (i = 0; i < debtCount; i++){
		printf("DEBT NO. %d - %s\n", i + 1, debtRecords[i].title);
		printf("Debt Initial Amount: %.2lf\n", debtRecords[i].amount);
		
		double balance = debtRecords[i].amount;
		double monthlyInt = debtRecords[i].intRate / 12 / 100; //Divide in how many months, then convert to decimal
		int months = 0;
		double totalDebtInt = 0.0;
		
		while (balance > 0) {
            // Calculate interest on the current balance (compound interest)
            double interest = balance * monthlyInt;
            totalDebtInt += interest;

            // Ensure the payment is enough to cover interest and part of the balance
            double payment = (balance + interest < debtRecords[i].minPayment) ? (balance + interest) : debtRecords[i].minPayment;

            if (payment <= interest) {
                printf("Warning: Insufficient payment to cover interest. Debt will grow!\n");
                break;
            }

            // Update balance by adding interest, then subtracting the payment
            balance = balance + interest - payment;
            months++;
        }
        
        totalInt += totalDebtInt;
        totalDebt += debtRecords[i].amount;
        
        printf("Time to Payoff: %d months\n", months);
        printf("Total Interest Paid: $%.2f\n\n", totalDebtInt);
	}
	
	yellow();
	printf("---END OF LIST---");
	reset();
	
	goBack();
}

void getFileName () {
	printf("Input file name: ");
	scanf("%s", inputFile);
	snprintf(fileName, sizeof(fileName),"%s.txt", inputFile); // Safe string concatenation
	printf("Your chosen file name is: %s\n", fileName);
}

// Open Existing File
void openFile(){
	getFileName();

	// Open file in Read/Write mode
	FILE *file = fopen(fileName, "r+");
	if (file == NULL) {
		printf("Failed to open file. It may not exist.");
		return;
	}
	  
	// Perform file operations here..
	// Read and Print every line from the file
	while ((fgets(readFile, sizeof(readFile), file)) != NULL) {
		printf("%s", readFile);
	}
	// Close the file after reading
	fclose(file);

	// Reopen file in Append mode to add new data
	file = fopen(fileName, "a");
	if (file == NULL) {
		printf("Error opening file for appending");
		return;
	}

	// Append here..

	// Close the file
	fclose(file);
}

// Create New File
void addFile(){
	getFileName();

	// Open file in Append mode (Creates file if it doesn't exist)
	FILE *file = fopen(fileName, "a");
	if (file == NULL) {
		printf("Error creating file");
		return;
	}
	
	// Perform file operations here..

	// Close the file
	fclose(file);
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
			//OPEN EXISTING FILE
			case 1:
				system("cls");
				//file = fopen("name of file", "mode (r/w/rw/a)");
				goto SecondMenu;
			//CREATE NEW FILE
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
                calculateRepaymentPlan();
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