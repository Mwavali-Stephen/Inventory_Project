#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class Product {
private:
    int productID;
    string productName;
    int quantity;
    double price;

public:
    Product(int id, string name, int qty, double pr) : productID(id), productName(name), quantity(qty), price(pr) {}

    int getProductID() const { return productID; }
    string getProductName() const { return productName; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void displayProductInfo() const {
        cout << "ID: " << productID
             << ", Name: " << productName
             << ", Quantity: " << quantity
             << ", Price: Ksh." << fixed << setprecision(2) << price << "\n";
    }

    void updateQuantity(int amount) {
        quantity = amount;
    }

    double calculateValue() const {
        return quantity * price;
    }
};

class Inventory {
private:
    vector<Product> products;

public:
    void addProduct(int id, const string& name, int qty, double price) {
        for (const auto& product : products) {
            if (product.getProductID() == id) {
                cout << "Error: Product with ID " << id << " already exists.\n";
                return;
            }
        }
        products.emplace_back(id, name, qty, price);
        cout << "Product added successfully.\n";
    }

    void displayAllProducts() const {
        if (products.empty()) {
            cout << "No products in inventory.\n";
            return;
        }
        cout << "Product List:\n";
        for (const auto& product : products) {
            product.displayProductInfo();
        }
    }

    void updateProductQuantity(int id, int qty) {
        for (auto& product : products) {
            if (product.getProductID() == id) {
                product.updateQuantity(qty);
                cout << "Quantity updated successfully.\n";
                return;
            }
        }
        cout << "Error: Product with ID " << id << " not found.\n";
    }

    void deleteProduct(int id) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->getProductID() == id) {
                products.erase(it);
                cout << "Product deleted successfully.\n";
                return;
            }
        }
        cout << "Error: Product with ID " << id << " not found.\n";
    }

    void calculateTotalInventoryValue() const {
        double totalValue = 0;
        for (const auto& product : products) {
            totalValue += product.calculateValue();
        }
        cout << "Total Inventory Value: $" << fixed << setprecision(2) << totalValue << "\n";
    }
};

void showMenu() {
    cout << "\nInventory Management System\n";
    cout << "1. Add New Product\n";
    cout << "2. Display All Products\n";
    cout << "3. Update Product Quantity\n";
    cout << "4. Delete a Product\n";
    cout << "5. Calculate Total Inventory Value\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Inventory inventory;
    int choice;

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        int id, qty;
        string name;
        double price;

        switch (choice) {
            case 1:
                cout << "Enter Product ID: ";
                cin >> id;
                cout << "Enter Product Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Quantity: ";
                cin >> qty;
                cout << "Enter Price: ";
                cin >> price;
                inventory.addProduct(id, name, qty, price);
                break;

            case 2:
                inventory.displayAllProducts();
                break;

            case 3:
                cout << "Enter Product ID to update quantity: ";
                cin >> id;
                cout << "Enter new Quantity: ";
                cin >> qty;
                inventory.updateProductQuantity(id, qty);
                break;

            case 4:
                cout << "Enter Product ID to delete: ";
                cin >> id;
                inventory.deleteProduct(id);
                break;

            case 5:
                inventory.calculateTotalInventoryValue();
                break;

            case 6:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
