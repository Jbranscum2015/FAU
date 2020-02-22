/*Jared Branscum COP 2220
October 30, 2016
Program 2*/

//preprocessor directive
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>


// Displays the list of apps available
//prompts for the user’s selection and sets the value of the selection
void DisplayApps(char *selectionPtr);
//sets the cost of the item based on value stored in purchase
void SetCost(char selection, double *costPtr);
//Displays the codes for the user to input money - gets user input amounts
//compares the int codes and updates the deposit amount
void PaymentOptions(double *depositPtr, double cost);
//compares the amount the user has in deposits to the price of app selected.
//It returns 1 if the amount is enough to cover the cost, 0 if there is not enough.
int Compare(double deposit, double choiceCost);
//uses PaymentOptions function to display and collect dollar amounts from the user
//uses Compare function to keep comparing the added deposited amount to the item cost.
void Pay(double *depositPtr, double choiceCost);
//calculates the amount of leftover from your deposits
void GetChange(double *depositPtr, double choiceCost);
//Asks the user if they want another app);
void DoItAgain(char *quitPtr);
//takes an array of all the purchase transactions costs
//and the number of items purchased
//and displays the information onto the screen
void DisplayPurchases(double priceList[], int num);

int main()
{
	//variables
	char selection, quit;
	double bank = 0.0, cost;
	double purchase[20];
	int count = 0;
	
	//greets the user
	printf("Welcome to the App Store!");

	//shows current balance
	printf("\n\nYou have $0.00 in your bank.\n\n---------------------------");

	do {
		// Displays the list of apps available
		//prompts for the user’s selection and sets the value of the selection
		DisplayApps(&selection);

		//sets the cost of the item based on value stored in purchase
		SetCost(selection, &cost);

		//puts cost of the item into the array and updates count
		purchase[count] = cost;
		count++;

		//uses PaymentOptions function to display and collect dollar amounts from the user
		//uses Compare function to keep comparing the added deposited amount to the item cost.
		Pay(&bank, cost);
		printf("\n\nYou have purchased: %c\n\n", selection);
		//calculates the amount of leftover from your deposits
		GetChange(&bank, cost);
		printf("\nYou now have $%.2lf in your bank", bank);

		//Asks the user if they want another app
		DoItAgain(&quit);
		quit = toupper(quit);
	} while (quit == 'Y');

	DisplayPurchases(purchase, count);
}

// Displays the list of apps available
//prompts for the user’s selection and sets the value of the selection
void DisplayApps(char *selectionPtr)
{
	//shows the list of apps
	printf("\n\nHere are the selections:");
	printf("\n\nC -- Clash of Clans        $299.99");
	printf("\nV -- Virtual Globe         $349.99");
	printf("\nR -- Remote PC             $999.99");
	printf("\nG -- Groupon               $2.99");
	printf("\nM -- Mobile Cam Viewer     $89.99");

	//prompt the user
	printf("\n\nPlease enter a selection: ");
	scanf(" %c", selectionPtr);
}
//sets the cost of the item based on value stored in purchase
void SetCost(char selection, double *costPtr)
{
	selection = toupper(selection);
	switch (selection){
		case 'C':
			*costPtr = 299.99;
			break;
		case 'V':
			*costPtr = 349.99;
			break;
		case 'R':
			*costPtr = 999.99;
			break;
		case 'G':
			*costPtr = 2.99;
			break;
		case 'M':
			*costPtr = 89.99;
			break;
		default:
			break;
	}
}
//Displays the codes for the user to input money - gets user input amounts
//compares the int codes and updates the deposit amount
void PaymentOptions(double *depositPtr, double cost)
{
	int num;

	//how much is in bank, how much the item costs, prompts for payment selection and adds money to bank
	printf("\nYou do not have enough money in the bank.");
	printf("\n\nThe bank has $%.2lf and the item costs $%.2lf", *depositPtr, cost);
	printf("\n\nPlease make a payment selection:");
	printf("\n--- 1    $1000.00");
	printf("\n--- 2    $500.00");
	printf("\n--- 3    $100.00");
	printf("\n--- 4    $10.00");

	printf("\nEnter payment selection: ");
	scanf("%d", &num);
	if (num == 1) {
		*depositPtr = *depositPtr + 1000.00;
	}
	if (num == 2) {
		*depositPtr = *depositPtr + 500.00;
	}
	if (num == 3) {
		*depositPtr = *depositPtr + 100.00;
	}
	if (num == 4) {
		*depositPtr = *depositPtr + 10.00;
	}
	else {
		*depositPtr = *depositPtr;
	}

}
//compares the amount the user has in deposits to the price of app selected.
//It returns 1 if the amount is enough to cover the cost, 0 if there is not enough.
int Compare(double deposit, double choiceCost)
{
	if (choiceCost <= deposit) {
		return 1;
	}
	else {
		return 0;
	}
}
//uses PaymentOptions function to display and collect dollar amounts from the user
//uses Compare function to keep comparing the added deposited amount to the item cost.
void Pay(double *depositPtr, double choiceCost)
{
	int enough;
	enough = Compare(*depositPtr, choiceCost);
	while (enough == 0)
	{
		//get money
	PaymentOptions(depositPtr, choiceCost);

	enough = Compare(*depositPtr, choiceCost);
	}
}
//calculates the amount of leftover from your deposits
void GetChange(double *depositPtr, double choiceCost)
{
	*depositPtr = *depositPtr - choiceCost;
}
//Asks the user if they want another purchase
void DoItAgain(char *quitPtr)
{
	printf("\n\nWould you like to make another purchase?");
	scanf(" %c", quitPtr);

}

//takes an array of all the purchase transactions costs
//and the number of items purchased
//and displays the information onto the screen
void DisplayPurchases(double priceList[], int num)
{
	int i;
	printf("\nThank you for your purchase(s)!");
	printf("\nYou made %d purchases as follows:\n\n", num);
	for (i = 0; i < num; i++)
	{
		printf("%.2f\n", priceList[i]);
	}
}