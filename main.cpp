#include <iostream>
#include <string>
using namespace std;

// Product class definition
class Product {
public:
    int id;             // Product ID
    string name;        // Product name
    string brand;       // Brand of the product
    string category;    // Product category
    double price;       // Price per unit (including tax)
    int quantity;       // Available quantity in stock

    Product* next;      // Pointer to the next product in the Linked List

    Product(int id, string name, string brand, string category, double price, int quantity) {
        this->id = id;
        this->name = name;
        this->brand = brand;
        this->category = category;
        this->price = price;
        this->quantity = quantity;
        this->next = nullptr;  // No next product initially
    }
};

// Makeup Store system class
class MakeupStore {
private:
    Product* head;  // Pointer to the first product in the list
    double taxRate; // Tax rate for all products

public:
    MakeupStore() {
        head = nullptr;  
        taxRate = 0.15; // 15% tax rate (can be changed)
    }

    void addProduct();              // Function to add a new product
    Product* searchProduct(int id);  // Function to search a product by ID only
    void updateProduct(int id);     // Function to update product info by ID
    bool deleteProduct(int id);     // Function to delete a product by ID
    void displayAllProducts();         // Function to display all products
};

// Add a new product
void MakeupStore::addProduct() {
    int id, quantity;
    double price;
    string name, brand, category;

    cout << "Enter Product ID: ";
    cin >> id;   // Get product ID from user
    cin.ignore(); // Ignore the newline left by previous input

    cout << "Enter Product Name: ";
    getline(cin, name);  // Get product name from user
    cout << "Enter Brand: ";
    getline(cin, brand); // Get product brand from user
    cout << "Enter Category: ";
    getline(cin, category); // Get product category from user
    cout << "Enter Price (including tax): ";
    cin >> price;   // Get product price (with tax) from user
    cout << "Enter Quantity: ";
    cin >> quantity; // Get product quantity from user
    cin.ignore();    // Ignore the newline left by previous input

    Product* newProduct = new Product(id, name, brand, category, price, quantity);  // Create a new product object

    newProduct->next = head;  // Point new product to the current head (first product)
    head = newProduct;        // Set head of the list to the new product

    cout << "Product added successfully.\n"; // Confirm the product was added
}

// Search product by ID only
Product* MakeupStore::searchProduct(int id) {
    Product* temp = head;

    while (temp != nullptr) {
        if (temp->id == id) {  // Search by ID only
            double priceWithoutTax = temp->price / (1 + taxRate); // Calculate price without tax

            cout << "\n--- Product Found ---\n";
            cout << "ID: " << temp->id << "\n";
            cout << "Name: " << temp->name << "\n";
            cout << "Brand: " << temp->brand << "\n";
            cout << "Category: " << temp->category << "\n";
            cout << "Price (with tax): " << temp->price << "\n";
            cout << "Price (without tax): " << priceWithoutTax << "\n"; // Display price without tax
            cout << "Quantity: " << temp->quantity << "\n";
            return temp;
        }
        temp = temp->next;  // Move to the next product in the list
    }

    cout << "Product not found!\n";  // If no product found
    return nullptr;
}

// Update product info by ID only
void MakeupStore::updateProduct(int id) {
    Product* product = searchProduct(id);  // Search for the product by ID only

    if (product == nullptr) {  // If product does not exist
        cout << "Cannot update. Product does not exist.\n";
        return;
    }

    int choice;
    cout << "\nWhat do you want to update?\n";
    cout << "1. Price\n";
    cout << "2. Quantity\n";
    cout << "Enter your choice: ";
    cin >> choice;  // Get the user's choice

    if (choice == 1) {
        double newPrice;
        cout << "Enter new price: ";
        cin >> newPrice;  // Get new price from user
        product->price = newPrice;  // Update product price
        cout << "Price updated successfully.\n";
    } 
    else if (choice == 2) {
        int newQuantity;
        cout << "Enter new quantity: ";
        cin >> newQuantity;  // Get new quantity from user
        product->quantity = newQuantity;  // Update product quantity
        cout << "Quantity updated successfully.\n";
    } 
    else {
        cout << "Invalid choice.\n";  // If the choice is invalid
    }
}

// Delete a product by ID only
bool MakeupStore::deleteProduct(int id) {
    Product* temp = head;
    Product* prev = nullptr;

    while (temp != nullptr) {
        if (temp->id == id) {  // If ID matches
            if (prev == nullptr) {
                head = temp->next;  // If the product is the head, update the head to next product
            } else {
                prev->next = temp->next;  // Remove product from the list by updating previous product's next
            }
            delete temp;  // Free memory of deleted product
            cout << "Product deleted successfully.\n";
            return true;  // Product was deleted successfully
        }
        prev = temp;       // Move prev to current product
        temp = temp->next; // Move temp to next product
    }

    cout << "Product not found. Cannot delete.\n";  // If no product found
    return false;  // Product not found
}

// Display all products
void MakeupStore::displayAllProducts() {

    if (head == nullptr) {  // If the list is empty
        cout << "\nNo products available.\n";
        return;
    }

    cout << "\n================= PRODUCT LIST =================\n";
    cout << "---------------------------------------------------------------------\n";
    cout << " ID  | Name     | Brand      | Category      | Price (with tax) | Price (without tax) | Qty      \n";
    cout << "---------------------------------------------------------------------\n";

    Product* temp = head;

    while (temp != nullptr) {
        double priceWithoutTax = temp->price / (1 + taxRate); // Calculate price without tax

        cout << " " << temp->id;
        if (temp->id < 10) cout << "    | ";  // Adjust spacing for ID
        else if (temp->id < 100) cout << "   | ";
        else cout << "  | ";

        string name = temp->name;
        name.resize(15, ' ');  // Adjust spacing for name
        cout << name << " | ";

        string brand = temp->brand;
        brand.resize(13, ' ');  // Adjust spacing for brand
        cout << brand << " | ";

        string category = temp->category;
        category.resize(10, ' ');  // Adjust spacing for category
        cout << category << " | ";

        cout << temp->price << " | ";  // Display price with tax
        cout << priceWithoutTax << " | ";  // Display price without tax
        cout << temp->quantity << "\n";  // Display quantity

        temp = temp->next;  // Move to next product
    }

    cout << "---------------------------------------------------------------------\n";
}

int main() {
    MakeupStore store;
    int choice, id;

    do {
        cout << "\n========= MAKEUP STORE SYSTEM =========";
        cout << "\n1. Add Product";
        cout << "\n2. Search Product";
        cout << "\n3. Update Product";
        cout << "\n4. Delete Product";
        cout << "\n5. Display All Products";
        cout << "\n6. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            store.addProduct();  // Call function to add a new product
            break;

        case 2:
            cout << "Enter product ID to search: ";
            cin >> id;
            store.searchProduct(id);  // Call function to search for a product
            break;

        case 3:
            cout << "Enter product ID to update: ";
            cin >> id;
            store.updateProduct(id);  // Call function to update product details
            break;

        case 4:
            cout << "Enter product ID to delete: ";
            cin >> id;
            store.deleteProduct(id);  // Call function to delete a product
            break;

        case 5:
            store.displayAllProducts();  // Call function to display all products
            break;

        case 6:
            cout << "Exiting...\n";  // Exit the program
            break;

        default:
            cout << "Invalid choice! Try again.\n";  // If user enters an invalid option
        }

    } while (choice != 6);  // Loop until user selects option 6 (Exit)

    return 0;
}