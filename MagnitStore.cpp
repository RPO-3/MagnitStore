#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

//STRUCTURES
struct Client {
    int id;
    char lastName[50];
    char firstName[50];
    char phoneNumber[20];
    char email[100];
};

struct LoyaltyCard {
    char cardId[20];
    int clientId;
    int bonusPoints;
    bool isActive;
};

struct Product {
    char code[20];
    char name[100];
    char category[50];
    double price;
    int inStock;
};

//GLOBAL DATA
vector<Client> clients;
vector<LoyaltyCard> cards;
vector<Product> products;

//FILE OPERATIONS
void saveClientsToFile() {
    ofstream file("clients.dat", ios::binary);
    if (file) {
        for (const auto& client : clients) {
            file.write((char*)&client, sizeof(client));
        }
    }
}

void loadClientsFromFile() {
    clients.clear();
    ifstream file("clients.dat", ios::binary);
    if (file) {
        Client client;
        while (file.read((char*)&client, sizeof(client))) {
            clients.push_back(client);
        }
    }
}

void saveCardsToFile() {
    ofstream file("cards.dat", ios::binary);
    if (file) {
        for (const auto& card : cards) {
            file.write((char*)&card, sizeof(card));
        }
    }
}

void loadCardsFromFile() {
    cards.clear();
    ifstream file("cards.dat", ios::binary);
    if (file) {
        LoyaltyCard card;
        while (file.read((char*)&card, sizeof(card))) {
            cards.push_back(card);
        }
    }
}

void saveProductsToFile() {
    ofstream file("products.dat", ios::binary);
    if (file) {
        for (const auto& product : products) {
            file.write((char*)&product, sizeof(product));
        }
    }
}

void loadProductsFromFile() {
    products.clear();
    ifstream file("products.dat", ios::binary);
    if (file) {
        Product product;
        while (file.read((char*)&product, sizeof(product))) {
            products.push_back(product);
        }
    }
}

//DISPLAY FUNCTIONS
void displayAllClients() {
    cout << "\n=== ALL CLIENTS ===\n";
    cout << "ID | Last Name | First Name | Phone | Email\n";
    cout << "--------------------------------------------\n";
    for (const auto& client : clients) {
        cout << client.id << " | " << client.lastName << " | "
            << client.firstName << " | " << client.phoneNumber
            << " | " << client.email << endl;
    }
}

void displayAllCards() {
    cout << "\n=== ALL LOYALTY CARDS ===\n";
    cout << "Card ID | Client ID | Points | Status\n";
    cout << "--------------------------------------\n";
    for (const auto& card : cards) {
        cout << card.cardId << " | " << card.clientId << " | "
            << card.bonusPoints << " | " << (card.isActive ? "Active" : "Inactive") << endl;
    }
}

void displayAllProducts() {
    cout << "\n=== ALL PRODUCTS ===\n";
    cout << "Code | Name | Category | Price | Stock\n";
    cout << "--------------------------------------\n";
    for (const auto& product : products) {
        cout << product.code << " | " << product.name << " | "
            << product.category << " | " << product.price
            << " | " << product.inStock << endl;
    }
}

//ADD FUNCTIONS
void addClient() {
    Client newClient;
    cout << "\n=== ADD NEW CLIENT ===\n";
    cout << "Enter ID: "; cin >> newClient.id;
    cout << "Enter Last Name: "; cin >> newClient.lastName;
    cout << "Enter First Name: "; cin >> newClient.firstName;
    cout << "Enter Phone: "; cin >> newClient.phoneNumber;
    cout << "Enter Email: "; cin >> newClient.email;

    clients.push_back(newClient);
    saveClientsToFile();
    cout << "Client added successfully!\n";
}

void addCard() {
    LoyaltyCard newCard;
    cout << "\n=== ADD NEW LOYALTY CARD ===\n";
    cout << "Enter Card ID: "; cin >> newCard.cardId;
    cout << "Enter Client ID: "; cin >> newCard.clientId;
    cout << "Enter Bonus Points: "; cin >> newCard.bonusPoints;
    cout << "Is active? (1-Yes, 0-No): "; cin >> newCard.isActive;

    cards.push_back(newCard);
    saveCardsToFile();
    cout << "Card added successfully!\n";
}

void addProduct() {
    Product newProduct;
    cout << "\n=== ADD NEW PRODUCT ===\n";
    cout << "Enter Code: "; cin >> newProduct.code;
    cout << "Enter Name: "; cin >> newProduct.name;
    cout << "Enter Category: "; cin >> newProduct.category;
    cout << "Enter Price: "; cin >> newProduct.price;
    cout << "Enter Stock Quantity: "; cin >> newProduct.inStock;

    products.push_back(newProduct);
    saveProductsToFile();
    cout << "Product added successfully!\n";
}

//SEARCH FUNCTIONS
void searchClientsByName() {
    char searchName[50];
    cout << "Enter last name to search: "; cin >> searchName;

    cout << "\n=== SEARCH RESULTS ===\n";
    bool found = false;
    for (const auto& client : clients) {
        if (strstr(client.lastName, searchName)) {
            cout << "ID: " << client.id << ", Name: " << client.lastName
                << " " << client.firstName << ", Phone: " << client.phoneNumber << endl;
            found = true;
        }
    }
    if (!found) cout << "No clients found.\n";
}

void filterCardsByStatus() {
    int status;
    cout << "Filter by status (1-Active, 0-Inactive): "; cin >> status;

    cout << "\n=== FILTERED CARDS ===\n";
    bool found = false;
    for (const auto& card : cards) {
        if (card.isActive == (status == 1)) {
            cout << "Card ID: " << card.cardId << ", Client ID: " << card.clientId
                << ", Points: " << card.bonusPoints << endl;
            found = true;
        }
    }
    if (!found) cout << "No cards found.\n";
}

void searchProductsByCategory() {
    char category[50];
    cout << "Enter category to search: "; cin >> category;

    cout << "\n=== PRODUCTS IN CATEGORY ===\n";
    bool found = false;
    for (const auto& product : products) {
        if (strstr(product.category, category)) {
            cout << "Code: " << product.code << ", Name: " << product.name
                << ", Price: " << product.price << ", Stock: " << product.inStock << endl;
            found = true;
        }
    }
    if (!found) cout << "No products found.\n";
}

//STATISTICS
void showStatistics() {
    cout << "\n=== SYSTEM STATISTICS ===\n";
    cout << "Total Clients: " << clients.size() << endl;

    int totalPoints = 0;
    int activeCards = 0;
    for (const auto& card : cards) {
        totalPoints += card.bonusPoints;
        if (card.isActive) activeCards++;
    }
    cout << "Total Bonus Points: " << totalPoints << endl;
    cout << "Active Cards: " << activeCards << endl;

    double totalValue = 0;
    for (const auto& product : products) {
        totalValue += product.price * product.inStock;
    }
    cout << "Total Inventory Value: $" << totalValue << endl;
}

//SORTING
bool compareClientsByName(const Client& a, const Client& b) {
    return strcmp(a.lastName, b.lastName) < 0;
}

bool compareCardsByPoints(const LoyaltyCard& a, const LoyaltyCard& b) {
    return a.bonusPoints > b.bonusPoints;
}

bool compareProductsByPrice(const Product& a, const Product& b) {
    return a.price < b.price;
}

void sortClients() {
    sort(clients.begin(), clients.end(), compareClientsByName);
    saveClientsToFile();
    cout << "Clients sorted by last name.\n";
}

void sortCards() {
    sort(cards.begin(), cards.end(), compareCardsByPoints);
    saveCardsToFile();
    cout << "Cards sorted by points (highest first).\n";
}

void sortProducts() {
    sort(products.begin(), products.end(), compareProductsByPrice);
    saveProductsToFile();
    cout << "Products sorted by price (lowest first).\n";
}

//MAIN MENU
void showMainMenu() {
    cout << "\n=================================";
    cout << "\n      MAGNIT STORE SYSTEM";
    cout << "\n=================================";
    cout << "\n1. Manage Clients";
    cout << "\n2. Manage Loyalty Cards";
    cout << "\n3. Manage Products";
    cout << "\n4. Search & Filter";
    cout << "\n5. Statistics";
    cout << "\n6. Sorting";
    cout << "\n0. Exit";
    cout << "\n=================================";
    cout << "\nSelect option: ";
}

void clientMenu() {
    int choice;
    do {
        cout << "\n=== CLIENT MANAGEMENT ===";
        cout << "\n1. Add New Client";
        cout << "\n2. View All Clients";
        cout << "\n0. Back";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: addClient(); break;
        case 2: displayAllClients(); break;
        }
    } while (choice != 0);
}

void cardMenu() {
    int choice;
    do {
        cout << "\n=== CARD MANAGEMENT ===";
        cout << "\n1. Add New Card";
        cout << "\n2. View All Cards";
        cout << "\n0. Back";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: addCard(); break;
        case 2: displayAllCards(); break;
        }
    } while (choice != 0);
}

void productMenu() {
    int choice;
    do {
        cout << "\n=== PRODUCT MANAGEMENT ===";
        cout << "\n1. Add New Product";
        cout << "\n2. View All Products";
        cout << "\n0. Back";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: addProduct(); break;
        case 2: displayAllProducts(); break;
        }
    } while (choice != 0);
}

void searchMenu() {
    int choice;
    do {
        cout << "\n=== SEARCH & FILTER ===";
        cout << "\n1. Search Clients by Name";
        cout << "\n2. Filter Cards by Status";
        cout << "\n3. Search Products by Category";
        cout << "\n0. Back";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: searchClientsByName(); break;
        case 2: filterCardsByStatus(); break;
        case 3: searchProductsByCategory(); break;
        }
    } while (choice != 0);
}

void sortMenu() {
    int choice;
    do {
        cout << "\n=== SORTING ===";
        cout << "\n1. Sort Clients by Name";
        cout << "\n2. Sort Cards by Points";
        cout << "\n3. Sort Products by Price";
        cout << "\n0. Back";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: sortClients(); break;
        case 2: sortCards(); break;
        case 3: sortProducts(); break;
        }
    } while (choice != 0);
}

//MAIN FUNCTION
int main() {
    loadClientsFromFile();
    loadCardsFromFile();
    loadProductsFromFile();

    int mainChoice;

    do {
        showMainMenu();
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: clientMenu(); break;
        case 2: cardMenu(); break;
        case 3: productMenu(); break;
        case 4: searchMenu(); break;
        case 5: showStatistics(); break;
        case 6: sortMenu(); break;
        case 0:
            cout << "\nSaving data and exiting...\n";
            break;
        default:
            cout << "\nInvalid option!\n";
        }

        if (mainChoice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (mainChoice != 0);

    return 0;
}