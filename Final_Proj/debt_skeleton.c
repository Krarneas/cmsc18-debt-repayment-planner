#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_DEBTS 100


//store debt info/details
typedef struct Record{
	char title[50]; //debt title
	double amount; //debt amount, how much is the debt
	double intRate; //annual interest rate
	double minPayment; //how much you are willing to pay your debt per month
} rec;



//GLOBALS
rec* debtRecords = NULL; // Pointer for dynamic array of debt records, dynamic array that stores individual debt info
int debtCount = 0, i, j; 
double income;
FILE *file; 
char readFile[1000];
char fileName[100];
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
	printf("\t[7] Delete Debt\n");
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


//ERROR CATCHING MONTHLY INCOME
int readInteger3() {
    char input[100]; // Buffer to hold the input
    int value;

    while (1) {
        printf("Enter your Monthly Income: "); // Prompt for input
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove newline character if present
            input[strcspn(input, "\n")] = 0;

            // Check if the input is numeric
            int isValid = 1; // Flag to check validity
            for (i = 0; input[i] != '\0'; i++) {
                if (!isdigit(input[i])) {
                    isValid = 0; // Set flag to false if a non-digit is found
                    break;
                }
            }

            if (isValid) {
                value = atoi(input); // Convert string to integer
                return value; // Return the valid integer
            } else {
                red(); 
                printf("Invalid Input! Try again.\n");
                reset(); 
                sleep(1.5); // Use Sleep(1500) for Windows
            }
        } else {
            // Handle input error
            red();
            printf("Error reading input! Try again.\n");
            reset();
            sleep(1.5);
            system("cls");
        }
    }
}

//ERROR CATHCING FOR ADDING DEBT
double readDouble(const char* prompt) {
    char input[100]; // Buffer to hold the input
    double value;

    while (1) {
        printf("%s", prompt); // Prompt for input
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove newline character if present
            input[strcspn(input, "\n")] = 0;

            // Check if the input is numeric
            int isValid = 1; // Flag to check validity
            for ( i = 0; input[i] != '\0'; i++) {
                if (!isdigit(input[i]) && input[i] != '.' && input[i] != '-') {
                    isValid = 0; // Set flag to false if a non-digit is found
                    break;
                }
            }

            if (isValid) {
                value = atof(input); // Convert string to double
                return value; // Return the valid double
            } else {
                red(); 
                printf("Invalid Input! Please enter a valid number.\n");
                reset(); 
                sleep(1.5); // Use Sleep(1500) for Windows
            }
        } else {
            // Handle input error
            red();
            printf("Error reading input! Try again.\n");
            reset();
            sleep(1.5);
        }
    }
}


//FUNCTION TO INPUT THE MONTHLY INCOME
void monthlyIncome(){
	income = readInteger3();
	
	green();
	printf("\nMonthly Income has been saved successfully!\n");
	reset();
	
	goBack();
}


//FUNCTION FOR ADDING DEBT
void addDebt() {
    rec debt;

    // Getting debt info
    printf("INPUT DEBT DETAILS\n");

    // Reading the debt title (with spaces)
    printf("Debt Title: ");
    fgets(debt.title, sizeof(debt.title), stdin);
    debt.title[strcspn(debt.title, "\n")] = '\0'; // Remove newline

    // Use readDouble for numeric inputs
    debt.amount = readDouble("Debt Amount: ");
    debt.intRate = readDouble("Interest Rate (%%): ");
    debt.minPayment = readDouble("Amount of payment (per Month): ");

    // Adding Debt info in the global array
    debtRecords[debtCount++] = debt;

    green();
    printf("\nDebt #%d - %s has been added successfully!\n", debtCount, debt.title);
    reset();

    goBack();
}


// FUNCTION FOR VEIWING DEBT DATA
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



// FUNCTION FOR THE REPAYMENT PLAN
void calculateRepaymentPlan(){
	double totalDebt = 0.0, totalInt = 0.0, allInt = 0.0, monthlyPayment = 0.0; 
	
	yellow();
	printf("REPAYMENT PLAN\n");
	reset();
	
	for (i = 0; i < debtCount; i++){
		printf("DEBT NO. %d - %s\n", i + 1, debtRecords[i].title);
		printf("Debt Initial Amount: %.2lf\n", debtRecords[i].amount);
		printf("Amount of payment (per Month): Php %.2lf\n\n", debtRecords[i].minPayment);
		
		double balance = debtRecords[i].amount;
		double monthlyInt = debtRecords[i].intRate / 12 / 100; //Divide in how many months, then convert to decimal
		int months = 0, year = 0;
		double totalDebtInt = 0.0;
		monthlyPayment += debtRecords[i].minPayment;
		
		while (balance > 0) {
            // Calculate interest on the current balance (compound interest)
            double interest = balance * monthlyInt;
            totalDebtInt += interest;
			allInt += interest;

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
        
        year = months/12;
        months = months % 12;
        
        printf("Time to Payoff: %d years and %d months\n", year, months);
        printf("Total Interest Paid: Php %.2f\n", totalDebtInt);
        printf("______________________________________________________________\n\n");
	}
	
	red();
	printf("The Total Interest: Php %.2f\n", allInt);
	reset();
	green();
	printf("Monthly Income After Paying Monthly Debt: Php %.2f\n\n\n", income - monthlyPayment);
	reset();

	yellow();
	printf("---END OF LIST---");
	reset();
	
	goBack();
}



// FUCTION FOR CHANGING DEBT INFORMATION
void changeDebtDetails() {
    char searchTitle[50];
    int found = 0;

    // Prompt user for the debt title to search
    printf("Enter the Debt Title to change: ");
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = '\0'; // Remove newline

    // Search for the debt in the records
    for (i = 0; i < debtCount; i++) {
        if (strcmp(debtRecords[i].title, searchTitle) == 0) {
            found = 1; // Debt found
            printf("Current details for '%s':\n", debtRecords[i].title);
            printf("Debt Amount: Php %.2lf\n", debtRecords[i].amount);
            printf("Interest Rate (%%): %.2lf%%\n", debtRecords[i].intRate);
            printf("Amount of payment (per Month): Php %.2lf\n", debtRecords[i].minPayment);

            // Prompt user for new details
            printf("\n\nEnter new Debt Amount: ");
            scanf(" %lf", &debtRecords[i].amount);
            printf("Enter new Interest Rate (%%): ");
            scanf(" %lf", &debtRecords[i].intRate);
            printf("Enter new Amount of payment (per Month): ");
            scanf(" %lf", &debtRecords[i].minPayment);

            green();
            printf("Debt details updated successfully!\n");
            reset();
            break; // Exit the loop after updating
        }
    }

    if (!found) {
        red();
        printf("Debt with title '%s' not found.\n", searchTitle);
        reset();
    }

    goBack();
}


//FOR FILE HANDLING
void getFileName () {
	printf("Input file name: ");
	scanf("%s", inputFile);
	snprintf(fileName, sizeof(fileName),"%s.txt", inputFile); // Safe string concatenation
	printf("Your chosen file name is: %s\n", fileName);
}

// Open Existing File
int openFile(){
	getFileName();

	// Open file in Read/Write mode
	file = fopen(fileName, "r+");
	if (file == NULL) {
		red();
		printf("Failed to open file. It may not exist.\n");
		reset();
		return 1;
	}
	  

	//READ THE DATA FROM THE EXISTING FILE
	//Read first monthly income
	if (fscanf(file, "%lf", &income) != 1){
		red();
        printf("\nError: Failed to read monthly income from the file.\n");
        reset();
        fclose(file);
        return 1;
	}
	
	//Then debt details
	while (fscanf(file, " %[^\n] %lf %lf %lf", 
              debtRecords[debtCount].title, 
              &debtRecords[debtCount].amount, 
              &debtRecords[debtCount].intRate, 
              &debtRecords[debtCount].minPayment) == 4) {
	    debtCount++;
	    if (debtCount >= MAX_DEBTS) {
	        printf("Reached maximum debt limit.\n");
	        break;
	    }
	}
	
	// Close the file after reading
	fclose(file);

}


//Saves the current file to the specified text file
void saveFile() {
    file = fopen(fileName, "w");
    if (file == NULL) {
        red();
        printf("Error opening file for saving.\n");
        reset();
        return;
    }

    // Write the monthly income to the file
    fprintf(file, "%.2f\n\n", income);

    // Write each debt record to the file
    for (i = 0; i < debtCount; i++) {
        fprintf(file, "%s\n%.2f\n%.2f\n%.2f\n\n", 
                debtRecords[i].title, 
                debtRecords[i].amount, 
                debtRecords[i].intRate, 
                debtRecords[i].minPayment);
    }

    fclose(file);
}


// 	FUNCTION TO DELETE DEBT BASED ON NAME
void deleteDebt() {
    char searchTitle[50];
    int found = 0;

    // Prompt user for the debt title to delete
    printf("Enter the Debt Title to delete: ");
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = '\0'; // Remove newline

    // Search for the debt in the records
    for (i = 0; i < debtCount; i++) {
        if (strcmp(debtRecords[i].title, searchTitle) == 0) {
            found = 1; // Debt found
            // Shift records down to remove the debt
            for (j = i; j < debtCount - 1; j++) {
                debtRecords[j] = debtRecords[j + 1];
            }
            debtCount--; // Decrease the count of debts
            green();
            printf("Debt '%s' has been deleted successfully!\n", searchTitle);
            reset();
            break; // Exit the loop after deleting
        }
    }

    if (!found) {
        red();
        printf("Debt with title '%s' not found.\n", searchTitle);
        reset();
    }

    goBack();
}

//FOR LOADINGS (for the aesthetics)
void loadAnimation(){
    printf("Saving File");
    fflush(stdout); // Ensure the output is printed immediately
    for ( i = 0; i < 3; i++) {
        printf(". ");
	    fflush(stdout);
	    sleep(1);
    }
    green();
    printf("\nFile Saved Successfully!\n");
    reset();
}

//MEMORY CLEAR
void cleanup() {
    if (debtRecords != NULL) {
        free(debtRecords);
        debtRecords = NULL; 
        debtCount = 0; // Reset count
    }
}

//MAIN PROGRAM
int main(){
	// Dynamically allocate memory for debtRecords
    debtRecords = malloc(MAX_DEBTS * sizeof(rec));
    if (debtRecords == NULL) {
        red();
        printf("ERROR: Memory allocation failed.\n");
        reset();
        return 1;
    }
	
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
				if (openFile() != 1){
					sleep(2.5);
                	system("cls");
					goto SecondMenu;
				}
				else{
					sleep(2.5);
                	system("cls");
					goto Menu;
				}
			//CREATE NEW FILE
			case 2:
				system("cls");
				getFileName();
                file = fopen(fileName, "r+");
	                if (file != NULL) {
                        red();
                        printf("File Already Exist... Try Again\n");
                        reset();
                        sleep(2.5);	
                        system("cls");
                        break;
                    }
                sleep(2.5);	
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
				changeDebtDetails();
				break;
            case 6:
            	system("cls");
            	saveFile();
            	loadAnimation();
			    sleep(2.5);
			    system("cls");
            	break;
			case 7:
				system("cls");
				deleteDebt();
				break;
            case 0:
            	yellow();
                printf("Going Back to Main Menu.\n");
                reset();
                sleep(1.5);
                system("cls");
                cleanup(); // Free memory
			    debtRecords = malloc(MAX_DEBTS * sizeof(rec)); // Reallocate memory
			    if (debtRecords == NULL) {
			        red();
			        printf("ERROR: Memory allocation failed.\n");
			        reset();
			        exit(1); // Exit the program if memory allocation fails
			    }
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