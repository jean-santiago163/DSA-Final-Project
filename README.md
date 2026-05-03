3N BAKESYNC SYSTEM

OVERVIEW

       3N BakeSync System is a console-based bakery stock management application developed in C. It is designed to streamline daily bakery 
operations by providing an efficient way to manage products, monitor inventory, and track sales. The system allows users to perform essential 
tasks such as adding products, processing sales, searching and sorting items, and reviewing transaction history. It also includes an undo feature, 
ensuring that recent mistakes can be corrected easily. This project demonstrates the practical application of data structures and algorithms in 
solving real-world inventory management problems.

FEATURES
  * Add and update products
  * View all products with stock levels
  * Process product sales with receipt display
  * Search products by name
  * Sort products by price or quantity
  * Undo recent transactions
  * Low stock monitoring (≤2 items)
  * View sales history with total revenue
  * Remove oldest sale record

DATA STRUCTURES AND THEIR IMPLEMENTATION

- ARRAYS
Used as the main storage for:
  * Product inventory (products[])
  * Undo actions (stack[])
  * Sales records (queue[])

- STACK (LIFO - Last In, First Out)
  * Implemented using an array (stack[]) with a "top" pointer
  * Used for the Undo feature
  * Ensures the most recent transaction is reversed first

- QUEUE (FIFO - First In, First Out)
  * Implemented using an array (queue[]) with "front" and "rear" pointers
  * Used for Sales History
  * Maintains chronological order of transactions

ALGORITHMS USED

- LINEAR SEARCH
  * Used in "searchProduct()"
  * Finds products by comparing names sequentially

- BUBBLE SORT
  * Used in "sortProducts()"
  * Sorts products based on:
    - Price
    - Quantity

SYSTEM FLOW
  1. User selects an option from the menu
  2. System processes input using appropriate functions
  3. Data is stored/updated in arrays
  4. Stack handles undo operations
  5. Queue records all sales transactions

INSTRUCTIONS:
  1. Open the file 3N BakeSync.c
  2. Click Compile & Run
  3. The menu-driven system will appear

GROUP MEMBERS
  - Angel S. Redecilla
  - Jean Rose B. Santiago
  - Shanice Lai P. Villamor
  
NOTE: Academic Integrity & AI Usage
This project was developed as part of CC104: Data Structures and Algorithms.

AI tools were used as a learning aid during the development process, particularly for:
  - Debugging errors  
  - Improving code structure and logic  
  - Clarifying implementation of data structures and algorithms  

All AI-generated suggestions were carefully reviewed, modified, and fully understood by the developers. The final code reflects the group’s own work and understanding.

