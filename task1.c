#include <stdio.h>
#include <stdlib.h>

// Defined constants
#define ESPRESSO_BEANS 8
#define ESPRESSO_WATER 30
#define CAPPUCCINO_MILK 70
#define MOCHA_MILK 160
#define MOCHA_CHOCOLATE 30

#define MIN_BEANS 10
#define MIN_WATER 50
#define MIN_MILK 50
#define MIN_CHOCOLATE 20

#define ADMIN_PASSWORD 1234

// Global variables
float total_amount = 0.0;
float espresso_price = 3.5, cappuccino_price = 4.5, mocha_price = 5.5;
int coffee_beans = 100, water = 200, milk = 200, chocolate_syrup = 100;

// Function declarations
void display_menu();
void order_coffee();
void admin_mode();
int validate_admin_password();
void replenish_ingredients();
void display_ingredients();
void change_coffee_price();
void alert_operator();
void update_sales(float coffee_price);
void insert_coins(float price);

int main() {
    int option;
    while (1) {
        display_menu();
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                order_coffee();
                break;
            case 2:
                admin_mode();
                break;
            case 3:
                printf("Exiting program\n");
                return 0;
            default:
                printf("Invalid option, please try again.\n");
        }
    }
    return 0;
}

void order_coffee() {
    int option;
    float price = 0.0;
    while (1) {
        printf("\nAvailable Coffee Types:\n");
        
        if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
            printf("1. Espresso (Price: AED %.2f)\n", espresso_price);
        } else {
            printf("1. Espresso (Unavailable due to insufficient ingredients)\n");
        }
        
        if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER && milk >= CAPPUCCINO_MILK) {
            printf("2. Cappuccino (Price: AED %.2f)\n", cappuccino_price);
        } else {
            printf("2. Cappuccino (Unavailable due to insufficient ingredients)\n");
        }
        
        if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER && milk >= MOCHA_MILK && chocolate_syrup >= MOCHA_CHOCOLATE) {
            printf("3. Mocha (Price: AED %.2f)\n", mocha_price);
        } else {
            printf("3. Mocha (Unavailable due to insufficient ingredients)\n");
        }
        
        printf("o. Exit\n");
    
        printf("Choose your coffee: ");
        scanf("%d", &option);
    
        switch (option) {
            case 1:
                if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
                    price = espresso_price;
                    printf("You selected Espresso (Price: AED %.2f)\n", price);
                } else {
                    printf("Espresso is unavailable. Please select another option.\n");
                    continue;
                }
                break;
            case 2:
                if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER && milk >= CAPPUCCINO_MILK) {
                    price = cappuccino_price;
                    printf("You selected Cappuccino (Price: AED %.2f)\n", price);
                } else {
                    printf("Cappuccino is unavailable. Please select another option.\n");
                    continue;
                }
                break;
            case 3:
                if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER && milk >= MOCHA_MILK && chocolate_syrup >= MOCHA_CHOCOLATE) {
                    price = mocha_price;
                    printf("You selected Mocha (Price: AED %.2f)\n", price);
                } else {
                    printf("Mocha is unavailable. Please select another option.\n");
                    continue;
                }
                break;
            case 0:
                return;
            default:
                printf("Invalid option. Please try again.\n");
                continue;
        }

        // Confirm order
        int confirm;
        printf("Confirm your order (1 for yes, 0 for no): ");
        scanf("%d", &confirm);
        if (confirm == 1) {
            insert_coins(price);
            
            // Update ingredients
            coffee_beans -= ESPRESSO_BEANS;
            water -= ESPRESSO_WATER;
            
            if (option == 2) milk -= CAPPUCCINO_MILK;
            if (option == 3) {
                milk -= MOCHA_MILK;
                chocolate_syrup -= MOCHA_CHOCOLATE;
            }
            
            printf("Enjoy your coffee! You bought a coffee for AED %.2f\n", price);
            update_sales(price);
            alert_operator();
        } else {
            printf("Order cancelled. Returning to menu...\n");
        }
    }
}

