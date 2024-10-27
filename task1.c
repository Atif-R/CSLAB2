#include <stdio.h>
#include <stdlib.h>

// Define constants for ingredient quantities per coffee type
#define ESPRESSO_BEANS 8
#define ESPRESSO_WATER 30
#define CAPPUCCINO_MILK 70
#define MOCHA_WATER 39
#define MOCHA_MILK 160
#define MOCHA_SYRUP 30

// Define admin password and thresholds for ingredient levels
#define ADMIN_PASSWORD 1234
#define LOW_THRESHOLD_BEANS 10
#define LOW_THRESHOLD_WATER 50
#define LOW_THRESHOLD_MILK 100
#define LOW_THRESHOLD_SYRUP 20

// Define coffee prices
float espresso_price = 3.5;
float cappuccino_price = 4.5;
float mocha_price = 5.5;

// Total sales amount
float total_amount = 0.0;

// Initial ingredient quantities in the machine
int coffee_beans = 100;
int water = 300;
int milk = 300;
int chocolate_syrup = 100;

// Modifiable admin password
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
        display_menu();  // Display main menu
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                order_coffee();  // Customer orders coffee
                break;
            case 2:
                admin_mode();    // Admin accesses admin mode
                break;
            case 3:
                printf("Exiting the application. Goodbye!\n");
                return 0;       // Exit application
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
    return 0;
}

// Displays the main menu options
void display_menu() {
    printf("\n---- Coffee Maker Menu ----\n");
    printf("1. Order a Coffee\n");
    printf("2. Admin Mode\n");
    printf("3. Exit\n");
    printf("Select an option: ");
}

// Handles coffee ordering process
void order_coffee() {
    int choice;
    int confirm;
    float price = 0.0;
    
    while(1) {
        printf("\n---- Select Coffee Type ----\n");
        
        // Display coffee options based on ingredient availability
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

        if(choice == 0) return;  // Exit if the user chooses to

        // Select price based on the coffee type and ingredient availability
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

        // Process payment if confirmed
        if(confirm == 1) {
            float total_paid = 0.0;
            float coin;
            printf("Please pay AED %.2f\n", price);

            // Accept coins until payment is complete
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

            // Return change if overpaid
            if(total_paid > price) {
                printf("Change due: AED %.2f\n", total_paid - price);
            }
            
            update_sales(price);  // Update sales record

            // Deduct ingredients based on coffee choice
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
            
            check_ingredient_levels();  // Check if ingredients are low
            printf("Thank you for purchasing! Enjoy your coffee!\n");
            return;
        }
    }
}

// Updates the total sales amount
void update_sales(float amount) {
    total_amount += amount;
}

// Checks if ingredients are below the low threshold and alerts
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

// Handles admin mode access and functions
void admin_mode() {
    int password;
    password = get_password();
    if(password != admin_password) {
        printf("Incorrect password. Access denied.\n");
        return;
    }

    int admin_choice;
    while(1) {
        printf("\n---- Admin Mode ----\n");
        printf("1. Display Ingredients and Sales\n");
        printf("2. Replenish Ingredients\n");
        printf("3. Change Coffee Prices\n");
        printf("4. Reset Total Sales\n");
        printf("5. Change Admin Password\n");
        printf("0. Exit Admin Mode\n");
        printf("Select an option: ");
        scanf("%d", &admin_choice);

        switch(admin_choice) {
            case 1:
                display_ingredients();       // Display ingredients and sales
                break;
            case 2:
                replenish_ingredients();     // Replenish ingredients
                break;
            case 3:
                change_price();              // Change coffee prices
                break;
            case 4:
                reset_sales();               // Reset total sales
                break;
            case 5:
                change_admin_password();     // Change admin password
                break;
            case 0:
                return;                      // Exit admin mode
            default:
                printf("Invalid option. Try again.\n");
        }
    }
}

// Gets the admin password from the user
int get_password() {
    int password;
    printf("Enter Admin Password: ");
    scanf("%d", &password);
    return password;
}

// Displays current ingredient levels and sales total
void display_ingredients() {
    printf("\n---- Ingredient Levels ----\n");
    printf("Coffee Beans: %d grams\n", coffee_beans);
    printf("Water: %d milliliters\n", water);
    printf("Milk: %d milliliters\n", milk);
    printf("Chocolate Syrup: %d milliliters\n", chocolate_syrup);
    printf("Total Sales: AED %.2f\n", total_amount);
}

// Replenishes ingredients with random values within specified ranges
void replenish_ingredients() {
    coffee_beans = (rand() % 100) + 100;
    water = (rand() % 300) + 200;
    milk = (rand() % 300) + 200;
    chocolate_syrup = (rand() % 100) + 100;
    printf("Ingredients replenished successfully.\n");
}

// Allows admin to change coffee prices
void change_price() {
    int coffee_choice;
    printf("\n---- Change Coffee Prices ----\n");
    printf("1. Espresso (Current Price: AED %.2f)\n", espresso_price);
    printf("2. Cappuccino (Current Price: AED %.2f)\n", cappuccino_price);
    printf("3. Mocha (Current Price: AED %.2f)\n", mocha_price);
    printf("Select coffee to change the price: ");
    scanf("%d", &coffee_choice);

    float new_price;
    printf("Enter new price: ");
    scanf("%f", &new_price);

    switch(coffee_choice) {
        case 1:
            espresso_price = new_price;
            break;
        case 2:
            cappuccino_price = new_price;
            break;
        case 3:
            mocha_price = new_price;
            break;
        default:
            printf("Invalid selection.\n");
            return;
    }
    printf("Price updated successfully.\n");
}

// Resets total sales amount to zero
void reset_sales() {
    total_amount = 0.0;
    printf("Total sales have been reset.\n");
}

// Allows admin to change the admin password
void change_admin_password() {
    int old_password;
    printf("Enter old password: ");
    scanf("%d", &old_password);
    
    if(old_password != admin_password) {
        printf("Incorrect old password.\n");
        return;
    }

    int new_password;
    printf("Enter new password: ");
    scanf("%d", &new_password);
    admin_password = new_password;
    printf("Admin password changed successfully.\n");
}
