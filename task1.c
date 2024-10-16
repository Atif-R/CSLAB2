#include <stdio.h>
#include <stdlib.h>

// Define constants
#define ESPRESSO_BEANS 8
#define ESPRESSO_WATER 30
#define CAPPUCCINO_MILK 70
#define MOCHA_WATER 39
#define MOCHA_MILK 160
#define MOCHA_SYRUP 30

#define ADMIN_PASSWORD 1234

#define LOW_THRESHOLD_BEANS 10
#define LOW_THRESHOLD_WATER 50
#define LOW_THRESHOLD_MILK 100
#define LOW_THRESHOLD_SYRUP 20

// Coffee prices
float espresso_price = 3.5;
float cappuccino_price = 4.5;
float mocha_price = 5.5;

float total_amount = 0.0;

// Ingredient quantities in the machine
int coffee_beans = 100;
int water = 300;
int milk = 300;
int chocolate_syrup = 100;

// Admin password variable (modifiable by the operator)
int admin_password = ADMIN_PASSWORD;

// Function prototypes
void order_coffee();
void admin_mode();
void replenish_ingredients();
void change_price();
void check_ingredient_levels();
void display_ingredients();
void update_sales(float amount);
int get_password();
void display_menu();
void reset_sales();
void change_admin_password();

int main() {
    int choice;
    
    while(1) {
        display_menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                order_coffee();
                break;
            case 2:
                admin_mode();
                break;
            case 3:
                printf("Exiting the application. Goodbye!\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
    return 0;
}

void display_menu() {
    printf("\n---- Coffee Maker Menu ----\n");
    printf("1. Order a Coffee\n");
    printf("2. Admin Mode\n");
    printf("3. Exit\n");
    printf("Select an option: ");
}

void order_coffee() {
    int choice;
    int confirm;
    float price = 0.0;
    
    while(1) {
        printf("\n---- Select Coffee Type ----\n");
        if(coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
            printf("1. Espresso - AED %.2f\n", espresso_price);
        } else {
            printf("1. Espresso - Unavailable due to temporarily insufficient ingredients\n");
        }
        
        if(coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER && milk >= CAPPUCCINO_MILK) {
            printf("2. Cappuccino - AED %.2f\n", cappuccino_price);
        } else {
            printf("2. Cappuccino - Unavailable due to temporarily insufficient ingredients\n");
        }
        
        if(coffee_beans >= ESPRESSO_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && chocolate_syrup >= MOCHA_SYRUP) {
            printf("3. Mocha - AED %.2f\n", mocha_price);
        } else {
            printf("3. Mocha - Unavailable due to temporarily insufficient ingredients\n");
        }
        
        printf("0. Exit\n");
        printf("Select a coffee type: ");
        scanf("%d", &choice);

        if(choice == 0) return;

        switch(choice) {
            case 1:
                if(coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
                    price = espresso_price;
                    printf("You selected: Espresso - AED %.2f\n", espresso_price);
                } else {
                    printf("Espresso is unavailable. Please select another option.\n");
                    continue;
                }
                break;
            case 2:
                if(coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER && milk >= CAPPUCCINO_MILK) {
                    price = cappuccino_price;
                    printf("You selected: Cappuccino - AED %.2f\n", cappuccino_price);
                } else {
                    printf("Cappuccino is unavailable. Please select another option.\n");
                    continue;
                }
                break;
            case 3:
                if(coffee_beans >= ESPRESSO_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && chocolate_syrup >= MOCHA_SYRUP) {
                    price = mocha_price;
                    printf("You selected: Mocha - AED %.2f\n", mocha_price);
                } else {
                    printf("Mocha is unavailable. Please select another option.\n");
                    continue;
                }
                break;
            default:
                printf("Invalid selection. Try again.\n");
                continue;
        }

        printf("Confirm your selection (1 for Yes, 0 for No): ");
        scanf("%d", &confirm);

        if(confirm == 1) {
            float total_paid = 0.0;
            float coin;
            printf("Please pay AED %.2f\n", price);
            while(total_paid < price) {
                printf("Insert coin (1 or 0.5 AED): ");
                scanf("%f", &coin);
                if(coin == 1.0 || coin == 0.5) {
                    total_paid += coin;
                    printf("Total paid: AED %.2f\n", total_paid);
                } else {
                    printf("Invalid coin. Please collect your coin and insert a valid one.\n");
                }
            }

            if(total_paid > price) {
                printf("Change due: AED %.2f\n", total_paid - price);
            }
            
            update_sales(price);
            switch(choice) {
                case 1:
                    coffee_beans -= ESPRESSO_BEANS;
                    water -= ESPRESSO_WATER;
                    break;
                case 2:
                    coffee_beans -= ESPRESSO_BEANS;
                    water -= ESPRESSO_WATER;
                    milk -= CAPPUCCINO_MILK;
                    break;
                case 3:
                    coffee_beans -= ESPRESSO_BEANS;
                    water -= MOCHA_WATER;
                    milk -= MOCHA_MILK;
                    chocolate_syrup -= MOCHA_SYRUP;
                    break;
            }
            check_ingredient_levels();
            printf("Thank you for purchasing! Enjoy your coffee!\n");
            return;
        }
    }
}

void update_sales(float amount) {
    total_amount += amount;
}

void check_ingredient_levels() {
    if(coffee_beans <= LOW_THRESHOLD_BEANS) {
        printf("Alert: Coffee beans are running low!\n");
    }
    if(water <= LOW_THRESHOLD_WATER) {
        printf("Alert: Water is running low!\n");
    }
    if(milk <= LOW_THRESHOLD_MILK) {
        printf("Alert: Milk is running low!\n");
    }
    if(chocolate_syrup <= LOW_THRESHOLD_SYRUP) {
        printf("Alert: Chocolate syrup is running low!\n");
    }
}

