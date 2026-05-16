#include <stdio.h>
#include <string.h>

// Structure to store Menu Items
struct MenuItem {
    int id;
    char name[30];
    float price;
};

int main() {
    // Restaurant Menu Card
    struct MenuItem menu[] = {
        {1, "Veg Burger", 120.00},
        {2, "Cheese Pizza", 250.00},
        {3, "Paneer Tikka", 180.00},
        {4, "Chicken Biryani", 280.00},
        {5, "Cold Coffee", 90.00},
        {6, "French Fries", 110.00}
    };
    
    int menuSize = sizeof(menu) / sizeof(menu[0]);
    int choice, quantity;
    char nextItem;
    float subTotal = 0.00, discount = 0.00, finalBill = 0.00;
    
    // Arrays to track what the user ordered
    int orderedItems[100];      // Stores Item IDs of ordered products
    int orderedQuantities[100]; // Stores Quantity of each ordered product
    int orderCount = 0;         // Keeps track of unique items ordered
    
    printf("=== WELCOME TO THE RESTAURANT ===\n\n");
    
    // Loop to take multiple items
    do {
        // Display Menu Card
        printf("--- MENU CARD ---\n");
        printf("%-5s %-20s %-10s\n", "ID", "Item Name", "Price (INR)");
        printf("-----------------------------------------\n");
        for(int i = 0; i < menuSize; i++) {
            printf("%-5d %-20s %-10.2f\n", menu[i].id, menu[i].name, menu[i].price);
        }
        printf("-----------------------------------------\n");
        
        // Take User Input
        printf("\nEnter Item ID to order: ");
        scanf("%d", &choice);
        
        // Validate Item ID
        if(choice < 1 || choice > menuSize) {
            printf("Invalid Item ID! Please choose a valid item.\n");
            continue;
        }
        
        printf("Enter Quantity: ");
        scanf("%d", &quantity);
        
        if(quantity <= 0) {
            printf("Quantity must be greater than 0!\n");
            continue;
        }
        
        // --- TRACKING LOGIC ---
        // Check if item is already added to the cart
        int alreadyExists = -1;
        for(int i = 0; i < orderCount; i++) {
            if(orderedItems[i] == choice) {
                alreadyExists = i;
                break;
            }
        }
        
        if(alreadyExists != -1) {
            // If item already exists, just update its quantity
            orderedQuantities[alreadyExists] += quantity;
        } else {
            // If it's a new item, add it to our tracking arrays
            orderedItems[orderCount] = choice;
            orderedQuantities[orderCount] = quantity;
            orderCount++;
        }
        // ----------------------
        
        float itemTotal = menu[choice - 1].price * quantity;
        subTotal += itemTotal;
        
        printf("Added: %dx %s (Cost: %.2f INR)\n", quantity, menu[choice - 1].name, itemTotal);
        
        // Ask if they want to add more items
        printf("\nDo you want to add more items? (y/n): ");
        scanf(" %c", &nextItem); 
        printf("\n");
        
    } while((nextItem == 'y' || nextItem == 'Y') && orderCount < 100);
    
    // Check for 15% Discount if total cart value is 1500+
    if(subTotal >= 1500.00) {
        discount = subTotal * 0.15; // 15% Discount
    }
    
    finalBill = subTotal - discount;
    
    // --- FINAL ITEMIZED BILL GENERATION ---
    printf("====================================================\n");
    printf("                    FINAL BILL                      \n");
    printf("====================================================\n");
    printf("%-20s %-10s %-10s %-10s\n", "Item Name", "Price", "Qty", "Total");
    printf("----------------------------------------------------\n");
    
    // Loop through the tracked orders and print them
    for(int i = 0; i < orderCount; i++) {
        int itemIndex = orderedItems[i] - 1; // Get actual array index of the menu item
        int qty = orderedQuantities[i];
        float cost = menu[itemIndex].price * qty;
        
        printf("%-20s %-10.2f %-10d %-10.2f\n", menu[itemIndex].name, menu[itemIndex].price, qty, cost);
    }
    
    printf("----------------------------------------------------\n");
    printf("Subtotal:                                 %.2f INR\n", subTotal);
    
    if(discount > 0) {
        printf("Discount (15%%):                          -%.2f INR\n", discount);
    } else {
        printf("Discount (15%%):                           0.00 INR\n");
    }
    
    printf("----------------------------------------------------\n");
    printf("Grand Total:                              %.2f INR\n", finalBill);
    printf("====================================================\n");
    printf("            Thank You! Visit Us Again.              \n");
    
    return 0;
}
