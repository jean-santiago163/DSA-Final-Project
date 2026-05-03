#include <stdio.h>   
#include <string.h>  
#include <stdlib.h>  

#define MAX 100  

// PRODUCT STRUCT 
// This structure stores information about a product in the inventory
struct Product {
    char name[50];   
    int quantity;    
    float price;     
};

// Array to store all products
struct Product products[MAX];
int count = 0;  // Keeps track of the number of products currently stored

// STACK (Undo System)
// This structure is used to store undo actions (LIFO - Last In First Out)
struct Undo {
    int index;  
    int qty;   
};

// Stack implementation using array
struct Undo stack[MAX];
int top = -1;  // Indicates the top of the stack (-1 means empty)

// QUEUE (Sales History)
// This structure stores each sale transaction
struct Sale {
    char name[50];  
    int qty;        
    float total;    
};

// Queue implementation using array (FIFO - First In First Out)
struct Sale queue[MAX];
int front = -1, rear = -1;  

// HEADER 
void displayHeader() {
    printf("\n==========================================================\n");
    printf("                   3N BAKESYNC SYSTEM\n");
    printf("             Bakery Stock Management System\n");
    printf("==========================================================\n");
}

// STACK FUNCTIONS 
// Push function: stores a transaction for undo
void push(int index, int qty) {
    // Check if stack is not full
    if (top < MAX - 1) {
        top++;  // Move top pointer
        stack[top].index = index;  
        stack[top].qty = qty;      
    }
}

// Pop function: performs undo (restores previous stock)
void pop() {
    // Check if stack is empty
    if (top == -1) {
        printf("\n=================================\n");
        printf("Nothing to undo!\n");
        printf("=================================\n");
        return;
    }

    // Retrieve last action (LIFO behavior)
    int index = stack[top].index;
    int qty = stack[top].qty;
    top--;  // Remove from stack

    // Restore the product quantity
    products[index].quantity += qty;

    printf("\n=================================\n");
    printf("UNDO SUCCESSFUL\n");
    printf("Product     : %s\n", products[index].name);
    printf("Restored Qty: %d\n", qty);
    printf("=================================\n");
}

// Displays all undo history stored in the stack
void showUndoHistory() {
    int i;

    if (top == -1) {
        printf("\nNo undo history.\n");
        return;
    }

    printf("\n================ UNDO HISTORY ================\n");
    printf("| %-5s | %-20s | %-10s |\n", "No", "Product", "Qty");
    printf("----------------------------------------------\n");

    // Traverse stack from top to bottom (latest to oldest)
    for (i = top; i >= 0; i--) {
        printf("| %-5d | %-20s | %-10d |\n",
               top - i + 1,
               products[stack[i].index].name,
               stack[i].qty);
    }

    printf("==============================================\n");
}

// QUEUE FUNCTIONS
// Enqueue: adds a new sale to the sales history
void enqueue(char name[], int qty, float total) {
    // Check if queue is full
    if (rear == MAX - 1) {
        printf("Sales history is full!\n");
        return;
    }

    // If first element, initialize front
    if (front == -1) front = 0;

    rear++;  // Move rear pointer

    // Store sale details
    strcpy(queue[rear].name, name);
    queue[rear].qty = qty;
    queue[rear].total = total;
}

// Dequeue: removes the oldest sale (FIFO behavior)
void dequeue() {
    // Check if queue is empty
    if (front == -1 || front > rear) {
        printf("\nNo sales to remove.\n");
        return;
    }

    
    printf("\n================ REMOVED SALE ===============\n");
    printf("Product : %s\n", queue[front].name);
    printf("Qty     : %d\n", queue[front].qty);
    printf("Total   : %.2f\n", queue[front].total);
    printf("=============================================\n");

    front++;  // Move front pointer

    // Reset queue if empty
    if (front > rear) {
        front = rear = -1;
    }
}

// Displays all sales history and total revenue
void displaySalesHistory() {
    int i;
    float sum = 0;  

    if (front == -1) {
        printf("\nNo sales history.\n");
        return;
    }

    printf("\n====================== SALES HISTORY =====================\n");
    printf("| %-5s | %-20s | %-10s | %-10s |\n", "No", "Product", "Qty", "Total");
    printf("----------------------------------------------------------\n");

    // Traverse queue from front to rear
    for (i = front; i <= rear; i++) {
        printf("| %-5d | %-20s | %-10d | %-10.2f |\n",
               i - front + 1,
               queue[i].name,
               queue[i].qty,
               queue[i].total);

        sum += queue[i].total;  // Accumulate total sales
    }

    printf("==========================================================\n");
    printf("TOTAL SALES: %.2f PHP\n", sum);
    printf("==========================================================\n");
}

// PRODUCT FUNCTIONS 
// Adds a new product or updates existing one
void addProduct() {
    char name[50];
    int qty, i;
    float price;

    printf("Enter product name: ");
    scanf(" %[^\n]", name);

    printf("Enter quantity: ");
    scanf("%d", &qty);

    printf("Enter price: ");
    scanf("%f", &price);

    // Check if product already exists
    for (i = 0; i < count; i++) {
        if (strcmp(products[i].name, name) == 0) {
            products[i].quantity += qty;  // Update quantity
            printf("Product updated!\n");
            return;
        }
    }

    // Add new product
    strcpy(products[count].name, name);
    products[count].quantity = qty;
    products[count].price = price;
    count++;

    printf("Product added!\n");
}

// Displays all products
void viewProducts() {
    int i;

    if (count == 0) {
        printf("\nNo products available.\n");
        return;
    }

    printf("\n===================== PRODUCT LIST =======================\n");
    printf("| %-5s | %-20s | %-10s | %-10s |\n", "No", "Name", "Qty", "Price");
    printf("----------------------------------------------------------\n");

    for (i = 0; i < count; i++) {
        printf("| %-5d | %-20s | %-10d | %-10.2f",
               i + 1,
               products[i].name,
               products[i].quantity,
               products[i].price);

        // Highlight low stock
        if (products[i].quantity <= 2)
            printf("  LOW!");

        printf(" |\n");
    }

    printf("==========================================================\n");
}

// Handles selling of products
void sellProduct() {
    int choice, qty;
    char confirm;
    float total;

    if (count == 0) {
        printf("No products available.\n");
        return;
    }

    viewProducts();

    printf("\nEnter product number: ");
    scanf("%d", &choice);
    choice--;  

    printf("Enter quantity: ");
    scanf("%d", &qty);

    printf("Confirm sale? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y') {
        printf("Cancelled.\n");
        return;
    }

    // Check if enough stock
    if (products[choice].quantity >= qty) {
        products[choice].quantity -= qty;

        push(choice, qty);  // Save action for undo

        total = qty * products[choice].price;

        enqueue(products[choice].name, qty, total);  // Save sale in queue

       
        printf("\n================ RECEIPT ===============\n");
        printf("Product  : %s\n", products[choice].name);
        printf("Quantity : %d\n", qty);
        printf("----------------------------------------\n");
        printf("TOTAL    : %.2f PHP\n", total);
        printf("========================================\n");

    } else {
        printf("Not enough stock!\n");
    }
}

// Searches for a product by name
void searchProduct() {
    char name[50];
    int i;

    printf("Enter product name: ");
    scanf(" %[^\n]", name);

    // Linear search algorithm
    for (i = 0; i < count; i++) {
        if (strcmp(products[i].name, name) == 0) {
            printf("\n============ RESULT ============\n");
            printf("Name     : %s\n", products[i].name);
            printf("Quantity : %d\n", products[i].quantity);
            printf("Price    : %.2f\n", products[i].price);
            printf("================================\n");
            return;
        }
    }

    printf("Not found.\n");
}

// Sorts products using Bubble Sort
void sortProducts() {
    int option, i, j;
    struct Product temp;

    printf("\nSort by:\n1. Price\n2. Quantity\nChoice: ");
    scanf("%d", &option);

    // Bubble Sort Algorithm
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {

            if ((option == 1 && products[j].price > products[j + 1].price) ||
                (option == 2 && products[j].quantity > products[j + 1].quantity)) {

                // Swap elements
                temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }

    printf("Sorting completed!\n");
}

// Displays products with low stock (<=2)
void lowStockReport() {
    int i, found = 0;

    printf("\n================ LOW STOCK ==================\n");
    printf("| %-5s | %-20s | %-10s |\n", "No", "Name", "Qty");
    printf("---------------------------------------------\n");

    for (i = 0; i < count; i++) {
        if (products[i].quantity <= 2) {
            printf("| %-5d | %-20s | %-10d |\n",
                   i + 1,
                   products[i].name,
                   products[i].quantity);
            found = 1;
        }
    }

    if (!found)
        printf("No low stock items.\n");

    printf("=============================================\n");
}

// MAIN MENU 
int main() {
    int choice;

    // Infinite loop for continuous program execution
    while (1) {
        system("cls");  
        displayHeader();

        printf("\n======================= MAIN MENU ========================\n");
        printf("[1] Add Product\n");
        printf("[2] View Products\n");
        printf("[3] Sell Product\n");
        printf("[4] Search Product\n");
        printf("[5] Sort Products\n");
        printf("[6] Undo\n");
        printf("[7] Low Stock\n");
        printf("[8] Undo History\n");
        printf("[9] Sales History\n");
        printf("[10] Remove Oldest Sale\n");
        printf("[11] Exit\n");
        printf("==========================================================\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        // Switch-case to handle menu selection
        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: sellProduct(); break;
            case 4: searchProduct(); break;
            case 5: sortProducts(); break;
            case 6: pop(); break;
            case 7: lowStockReport(); break;
            case 8: showUndoHistory(); break;
            case 9: displaySalesHistory(); break;
            case 10: dequeue(); break;
            case 11:
                printf("Thank you!\n");
                return 0;  
            default:
                printf("Invalid choice!\n");
        }

        printf("\nPress Enter to continue...");
        getchar();  // Wait for user input
        getchar();  // Ensures pause works properly
    }
}
