#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "password";

class stack {
	public:
		int productID;
		string productName;
		int price;
		int quantity;
		stack *next;
		stack(int id, string name, int price,int quantity) {
			productID= id;
			productName=name;
			this->price=price;
			this->quantity=	quantity;
			next = NULL;
		}
};
class customer {

	public:
		string c;
		int totalpay;
		customer *next;

		customer(string c, int total) {
			this->c =c;
			totalpay=total;
			next = NULL;
		}
};

class CustomerList {
	public:
		customer* head;
		customer* top;
		int count;

		CustomerList() {
			head = NULL;
			top = NULL;
			count = 0;
		}


		void pushh(string c, int total) {
			customer* newCustomer = new customer(c, total);
			if (head == NULL) {
				head = newCustomer;
				top = newCustomer;
			} else {
				customer* temp = head;
				while (temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = newCustomer;
				top = newCustomer;
			}
			count++;
		}

		void pop() {
			if (head == NULL) {
				cout << "The list is empty." << endl;
				return;
			}

			if (head == top) {
				delete head;
				head = NULL;
				top = NULL;
			} else {
				customer* temp = head;
				while (temp->next != top) {
					temp = temp->next;
				}
				delete top;
				temp->next = NULL;
				top = temp;
			}
			count--;
		}
		void display() {
			if (head == NULL) {
				cout << "No customers to display." << endl;
				return;
			}

			customer* current = head;
			cout << "List of Customers:\n";
			cout << "Name\t\tTotal Payment\n";
			cout << "=================================\n";
			while (current != NULL) {
				cout << current->c << "\t\t$" << current->totalpay << "\n";
				current = current->next;
			}
			cout << "\nTotal customers: " << count << "\n\n";
		}
};

class stackProduct {

	public:
		stack* head;
		stack* top;

		int count;
		stackProduct() {
			head=NULL;
			count=0;
		}

		bool idExists(int id) {
			stack* temp = head;
			while (temp != NULL) {
				if (temp->productID == id) {
					return true;
				}
				temp = temp->next;
			}
			return false;
		}
		stack* findProductById(int id) {
			stack* current = head;
			while (current != NULL) {
				if (current->productID == id) {
					return current; // Return the pointer to the product
				}
				current = current->next;
			}
			return nullptr; // Product ID not found
		}

		void push(int id, string name, int price, int quantity) {
			if (!idExists(id)) {
				stack* pushing = new stack(id, name, price, quantity);
				if (head == NULL) {
					head = pushing;
					head->next = NULL;
					top = head;
				} else {
					top->next = pushing;
					top = pushing;
				}
				count++;
			} else {
				cout << "Product ID already exists. Product not added.\n";
			}
		}

		void popById(int id) {
			if (head == NULL) {
				cout << "The list is empty." << endl;
				return;
			}

			if (head->productID == id) {
				stack* toDelete = head;
				head = head->next;
				delete toDelete;
				if (head == NULL) {
					top = NULL;
				}
				count--;
				return;
			}

			stack* temp = head;
			while (temp->next != NULL && temp->next->productID != id) {
				temp = temp->next;
			}

			if (temp->next != NULL) {
				stack* toDelete = temp->next;
				temp->next = temp->next->next;
				if (temp->next == NULL) {
					top = temp;
				}
				delete toDelete;
				count--;
			} else {
				cout << "Product with ID " << id << " not found.\n";
			}
		}

		void display() {
			if (head == NULL) {
				cout << "No products to display." << endl;
				return;
			}

			stack* current = head;
			cout << "Existing products are:\n";
			cout << "ID\tProduct Name\t\t\tPrice\tQuantity\n";
			cout << "======================================================\n";
			while (current != NULL) {
				cout << current->productID << "\t" << current->productName;
				// Adjusting space based on the length of the product name
				for (int i = 0; i < 30 - current->productName.length(); ++i) {
					cout << " ";
				}
				cout << "$" << current->price << "\t" << current->quantity << "\n";
				current = current->next;
			}
			cout << "\nTotal products in our store: " << count << "\n\n";
		}








};

void sortProducts(stackProduct* productStack, bool ascending) {
   
    bool swapped;
    do {
        swapped = false;
        stack* current = productStack->head;
        while (current != NULL && current->next != NULL) {
            if ((ascending && current->price > current->next->price) || (!ascending && current->price < current->next->price)) {
                
                swap(current->productID, current->next->productID);
                swap(current->productName, current->next->productName);
                swap(current->price, current->next->price);
                swap(current->quantity, current->next->quantity);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    
}



customer* customerbuy(stackProduct *productStack) {
	vector<string> product;
	int pay = 0, total;
	vector<int> cart;
	vector<int> quantity;
	customer * custo;

	system("cls");
	system("color F1");
	cout << "Here is your trolley" << endl << endl;
	cout << "                  ___" << endl;
	cout << "                 /  |" << endl;
	cout << "  ______________/   --" << endl;
	cout << " |___/__ /___/_|     " << endl;
	cout << " |__/___/___/__|     " << endl;
	cout << " |_/___/___/___|     " << endl;
	cout << "    _______/         " << endl;
	cout << "     O   O           " << endl;
	
	
	
sort:	int sortChoice;
    cout << "Do you want to display products by price (1 - High to Low, 2 - Low to High, 0 - No sorting)? ";
    if (!(cin >> sortChoice) || sortChoice < 0 || sortChoice > 2) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice. Please try again.\n\n\n";
        system("pause");
        
        goto sort;
    }

    if (sortChoice == 1) {
        sortProducts(productStack, false); 
        cout<<"Sorted from high to low successfully!\n\n";
        system("pause");
        system("cls");
    } else if (sortChoice == 2) {
        sortProducts(productStack, true); 
        cout<<"Sorted from low to high successfully!\n\n";
        system("pause");
        system("cls");
    }
    else{
    	system("pause");
	}
	
loop:
	cout << "\t\t\tScroll down to input the product you need\n\n";
	productStack->display();



	while (true) {
loop2:		cout << "\n\n\t\tHow many items do you want to buy (0 to finish shopping): ";
		int number;
		if (!(cin >> number) || number < 0 || number > 20 || number > productStack->count) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input. Please enter a number between 0 and " << (productStack->count < 20 ? productStack->count : 20) << "." << endl;
			continue;
		}

		if (number == 0) {
			break; // Exit shopping loop
		}

		for (int i = 0; i < number; i++) {
			cout << "\n\tEnter the ID of the item you want to buy (Enter -1 to abort the process): ";
			
			int id;
			
			if (!(cin >> id) || id < 1 || !productStack->idExists(id)) {
				if(id==-1)
				{
					goto loop2;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid ID. Please try again." << endl;
				i--;
				continue;
			}

			stack* temp = productStack->head;
			bool found = false;

			while (temp != NULL && temp->productID != id) {
				temp = temp->next;
			}

			if (temp != NULL) {
				found = true;
				int quant;
				cout << "\nHow many quantities you want: ";
				if (!(cin >> quant) || quant < 1 || quant > temp->quantity) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid quantity. Please try again." << endl;
					continue;
				}

				product.push_back(temp->productName);
				cart.push_back(id);
				quantity.push_back(quant);
				pay += temp->price * quant;
				temp->quantity -= quant;
			}

			if (!found) {
				cout << "Product with ID " << id << " not found." << endl;
				i--; // Prompt for the item again
			}
		}
	}

	// Display the cart and allow the customer to remove items
	while (true) {
		system("cls");
		cout << "\nYour Cart:\n";
		cout << "ID\tProduct Name\t\t\tPrice\t\t\ Quantity\n";
		cout << "=================================================================\n";

		for (int i = 0; i < cart.size(); i++) {
			int id = cart[i];
			stack* temp = productStack->head;

			while (temp != NULL && temp->productID != id) {
				temp = temp->next;
			}

			if (temp != NULL) {
				cout << temp->productID << "\t" << temp->productName;
				for (int j = 0; j < 30 - temp->productName.length(); ++j) {
					cout << " ";
				}
				cout << "$" << temp->price << "\t\t"<<quantity[i]<<"\n";
			}
		}

		cout << "\nTotal cost: $" << pay << endl;
		cout << "\nOptions:\n";
		cout << "1. Remove an item from the cart\n";
		cout << "2. Checkout\n";
		cout<<"3.  Keep shopping to add Products\n";
		cout << "4. Return to the main menu\n";

		cout << "Enter your choice: ";

		int choice;
		cin >> choice;

		if (choice == 1) {
			cout << "Enter the ID of the item you want to remove: ";
			int id;
			if (!(cin >> id)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid ID. Please try again." << endl;
				continue;
			}

			// Manual search for the item in the cart
			int indexToRemove = -1;
			for (int i = 0; i < cart.size(); i++) {
				if (cart[i] == id) {
					indexToRemove = i;
					break;
				}
			}

			if (indexToRemove != -1) {
				stack* temp = productStack->head;

				while (temp != NULL && temp->productID != id) {
					temp = temp->next;
				}

				if (temp != NULL) {
					pay -= temp->price*quantity[indexToRemove];
					temp->quantity += quantity[indexToRemove]; // Increase the quantity of the removed item in the store.
					cart.erase(cart.begin() + indexToRemove);
					quantity.erase(quantity.begin()+indexToRemove);
					product.erase(product.begin() + indexToRemove);
					cout << "Item removed from the cart." << endl;
				}
			} else {
				cout << "Item with ID " << id << " not found in the cart." << endl;
			}
		} else if (choice == 2) {
			string customerr;
			cout << "\nEnter Your Name: ";
			cin >> customerr;
			system("cls");

			cout << "\n\n\n\n\t\t\tYou have bought: \n";
			for (const auto& p : product) {
				cout <<"\t"<< p << "\n";
			}
			total = pay; // Total cost
			custo = new customer(customerr,total);
			cout << "\n\nTotal cost: $" << total << "\nThank you for shopping, " << customerr << "!\n";
			cout << "\nWe look forward to welcoming you with love for another wonderful shopping experience!\n\n\n" << endl;
			break;
		} else if (choice == 3) {
			cout<<"Returning to product list to keep shopping\n\n";
			goto sort;

		} else if(choice==4) {

			cout << "Returning to the main menu." << endl;
			return NULL;
		} else {
			cout << "Invalid choice. Please try again." << endl;
		}
	}
	return custo;
}

bool login() {

	int attempts = 0;
	string username, password;


	do {
		system("cls");
		cout<<"\t\t\t\t----------WELCOME TO SHOPPING PORTAL------------\n\n";

		cout << "\n  *********  LOGIN FORM FOR ADMINISTRATOR ACCESS *********  ";
		cout << "\n\n\nENTER USERNAME:-\n";
		cin >> username;
		cout << "\nENTER PASSWORD:-\n";
		cin >> password;

		if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
			cout << "  \n\n\n       WELCOME !!!! LOGIN IS SUCCESSFUL\n";
			system("pause");
			break;
		}
		else if(username != ADMIN_USERNAME && password != ADMIN_PASSWORD){
			cout << "\n        SORRY !!!!  CREDENTIALS ARE INVALID\nPRESS ENTER TO TRY AGAIN";
			attempts++;
			cin.ignore(); 
			cin.get();
		}
		 else if(username!=ADMIN_USERNAME) {
			cout << "\n        SORRY !!!!  USERNAME DOESN'T MATCH'\nPRESS ENTER TO TRY AGAIN";
			attempts++;
			cin.ignore(); 
			cin.get(); 
		}
		else if(password!=ADMIN_PASSWORD){
			cout << "\n        SORRY !!!!  PASSWORD DOESN'T MATCH'\nPRESS ENTER TO TRY AGAIN";
			attempts++;
			cin.ignore(); 
			cin.get(); 
		}
	} while (attempts <= 2);

	if (attempts > 2) {
		cout << "\nSorry, you have entered the wrong username and password three times!!!";
		cin.get();

		return false;
	}

	system("cls");
	return username == ADMIN_USERNAME && password == ADMIN_PASSWORD;
}
void administrator(stackProduct* productStack, CustomerList* custr) {
	int choice;
loop:	do {

		system("cls");
		cout << "\n\t\t|--------<Admin Menu>-----------|";
		cout << "\n\n";
		cout << "\t\t 1) Add Product\n";
		cout << "\t\t 2) Delete Product\n";
		cout << "\t\t 3) Modify Product\n";
		cout << "\t\t 4) View Customer List\n";
		cout << "\t\t 5) Exit Admin Menu\n";
		cout << "\n What is your choice? ";
		cin >> choice;

		switch (choice) {
			case 1: {
				// Add Product
				int id=0, price, quantity;
				string name;
				cout << "Enter Product ID: ";
				if(!(cin >> id)){
					cin.clear();
					cin.ignore(10000, '\n');
					cout<<"\nInvalid ID\n";
					system("pause");
					goto loop;
				}
				
				if (productStack->idExists(id)) {
					cout << "Product ID already exists. Product not added.\n\n\n";

					system("pause");
					goto loop;
				}
				cout << "Enter Product Name: ";
				cin.ignore();
				getline(cin, name);
				cout << "Enter Price: ";
				if(!(cin >> price)){
					cin.clear();
					cin.ignore(10000, '\n');
					cout<<"\nInvalid Price\n";
					system("pause");
					goto loop;
				}
				cout << "Enter Quantity: ";
				if(!(cin >> quantity)){
					cin.clear();
					cin.ignore(10000, '\n');
					cout<<"\nInvalid Quantity\n";
					system("pause");
					goto loop;
				}
				productStack->push(id, name, price, quantity);
				cout << "Product added successfully.\n";
				break;
			}
			case 2: {
				
			int id=0;
				cout << "Enter Product ID to delete: ";
				if(!(cin >> id)){
					cin.clear();
					cin.ignore(10000, '\n');
					cout<<"\nInvalid ID\n";
					system("pause");
					goto loop;
				}
				if (!productStack->idExists(id)) {
					cout << "Product ID not found.\n";
					system("pause");
					goto loop;
				}
				productStack->popById(id);
				cout << "Product deleted successfully.\n";
				system("pause");
				break;
			}
			case 3: {
				
		loop3:		int id=0;
				cout << "Enter Product ID to modify: ";
				if(!(cin >> id)){
					cin.clear();
					cin.ignore(10000, '\n');
					cout<<"Invalid ID\n";
					system("pause");
					goto loop3;
				}
				if (!productStack->idExists(id)) {
					cout << "Product ID not found.\n";
					system("pause");
					goto loop3;
				}

				
				stack* product = productStack->findProductById(id);
				if (product) {
					string newName;
					int newPrice, newQuantity;
					cout << "Enter New Product Name: ";
					cin.ignore();
					getline(cin, newName);
					cout << "Enter New Price: ";
					
					if(!(cin >> newPrice)){
						cin.clear();
						cin.ignore(10000, '\n');
						cout<<endl;
					cout<<"Invalid Price\n";
					system("pause");
					goto loop3;
				}
					cout << "Enter New Quantity: ";
					;
					if(!(cin >> newQuantity)){
						cin.clear();
						cin.ignore(10000, '\n');
					cout<<"\nInvalid Quantity\n";
					system("pause");
					goto loop3;
				}
					
					product->productName = newName;
					product->price = newPrice;
					product->quantity = newQuantity;
					cout << "Product modified successfully.\n";
					
				} else {
					cout << "Error: Product not found.\n";
				}
				system("pause");
				break;
			}
			case 4:
				
				custr->display();
				system("pause");
				break;

			case 5:
				
				system("pause");
				return;

			default:
				cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 5);
}




void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
	system("color F1");
	CustomerList  custr;
	stackProduct productStack;
	productStack.push(1, "Smartphone Stand", 50, 10);
	productStack.push(2, "Electric Toothbrush", 30, 15);
	productStack.push(3, "Bluetooth Earbuds", 80, 20);
	productStack.push(4, "Wireless Charger", 15, 12);
	productStack.push(5, "Home Security Camera", 90, 8);
	productStack.push(6, "Fitness Tracker", 60, 17);
	productStack.push(7, "Portable Bluetooth Speaker", 40, 9);
	productStack.push(8, "Coffee Machine", 70, 11);
	productStack.push(9, "Smart LED Bulbs", 25, 14);
	productStack.push(10, "Robot Vacuum Cleaner", 200, 7);
	productStack.push(11, "Gaming Mouse", 35, 19);
	productStack.push(12, "Yoga Mat", 20, 13);
	productStack.push(13, "Reusable Water Bottle", 10, 6);
	productStack.push(14, "Laptop Backpack", 45, 16);
	productStack.push(15, "Wireless Headphones", 70, 22);
	productStack.push(16, "Mini Fridge", 110, 10);
	productStack.push(17, "Digital Camera", 120, 8);
	productStack.push(18, "Blender", 55, 12);
	productStack.push(19, "Smartwatch", 90, 14);
	productStack.push(20, "Standing Desk Converter", 150, 18);
	productStack.push(21, "Electric Scooter", 180, 7);
	productStack.push(22, "Coffee Grinder", 30, 21);
	productStack.push(23, "Virtual Reality Headset", 250, 9);
	productStack.push(24, "Air Purifier", 95, 13);
	productStack.push(25, "Desk Lamp", 40, 15);
	productStack.push(26, "Smart Doorbell", 120, 11);
	productStack.push(27, "Wireless Earphones", 70, 19);
	productStack.push(28, "Travel Suitcase", 75, 6);
	productStack.push(29, "Wireless Charging Pad", 20, 8);
	productStack.push(30, "Noise-Canceling Headphones", 150, 12);
	productStack.push(31, "Portable Power Bank", 30, 14);
	productStack.push(32, "Indoor Plants", 25, 17);
	productStack.push(33, "Water Filter Pitcher", 40, 20);
	productStack.push(34, "Smart Lock", 70, 9);
	productStack.push(35, "Rechargeable Flashlight", 15, 7);
	productStack.push(36, "Aromatherapy Diffuser", 35, 22);
	productStack.push(37, "Espresso Machine", 120, 10);
	productStack.push(38, "Wireless Keyboard and Mouse", 40, 11);
	productStack.push(39, "Mini Drone", 200, 13);
	productStack.push(40, "Wireless Charging Stand", 25, 15);
	productStack.push(41, "Folding Bike", 300, 16);
	productStack.push(42, "Smart Picture Frame", 50, 8);
	productStack.push(43, "Bluetooth Karaoke Microphone", 60, 6);
	productStack.push(44, "Bamboo Bed Sheets", 80, 19);
	productStack.push(45, "Solar-Powered Phone Charger", 40, 17);
	productStack.push(46, "UV-C Sterilizer Wand", 45, 12);
	productStack.push(47, "Adjustable Standing Desk", 250, 14);
	productStack.push(48, "Robotic Lawn Mower", 300, 9);
	productStack.push(49, "Wireless Video Doorbell", 180, 21);
	productStack.push(50, "Smart Mirror", 150, 7);
	productStack.push(51, "Automatic Pet Feeder", 70, 20);
	productStack.push(52, "Portable Hammock", 35, 16);
	productStack.push(53, "Solar-Powered Garden Lights", 30, 11);
	productStack.push(54, "Digital Drawing Tablet", 80, 15);
	productStack.push(55, "Wireless Charging Alarm Clock", 35, 13);
	productStack.push(56, "Mini Projector", 100, 18);
	productStack.push(57, "Electric Wine Opener", 25, 22);
	productStack.push(58, "Handheld Vacuum Cleaner", 50, 8);
	productStack.push(59, "Home Theater Soundbar", 90, 14);
	productStack.push(60, "Smart Thermostat", 80, 7);
	productStack.push(61, "Bike Helmet", 40, 19);
	productStack.push(62, "Smart Water Bottle", 20, 9);
	productStack.push(63, "Wireless Surround Sound System", 180, 12);
	productStack.push(64, "Garden Watering System", 30, 16);
	productStack.push(65, "Outdoor Security Camera", 100, 21);
	productStack.push(66, "Bluetooth Meat Thermometer", 25, 11);
	productStack.push(67, "Wireless Car Charger Mount", 30, 13);
	productStack.push(68, "Air Purifier Necklace", 35, 6);
	productStack.push(69, "Sweat-Proof Earbuds", 50, 15);
	productStack.push(70, "Bluetooth Turntable", 80, 18);
	productStack.push(71, "Smart Door Lock", 120, 10);
	productStack.push(72, "Robotic Pool Cleaner", 250, 14);
	productStack.push(73, "Wireless Gaming Headset", 60, 17);
	productStack.push(74, "Outdoor Fountain", 200, 20);
	productStack.push(75, "GPS Tracker", 30, 8);
	productStack.push(76, "Portable Monitor", 150, 15);
	productStack.push(77, "Wireless Security Camera", 75, 22);
	productStack.push(78, "Smart Toothbrush", 40, 10);
	productStack.push(79, "Wireless Mouse", 20, 11);
	productStack.push(80, "Smart Alarm Clock", 30, 13);
	productStack.push(81, "Cordless Vacuum Cleaner", 80, 9);
	productStack.push(82, "Smart Mirror", 150, 21);
	productStack.push(83, "Plant-Based Protein Powder", 25, 7);
	productStack.push(84, "Wireless Bike Lock", 50, 18);
	productStack.push(85, "Fingerprint Padlock", 35, 16);
	productStack.push(86, "Portable Solar Charger", 40, 12);
	productStack.push(87, "Digital Drawing Pen", 30, 14);
	productStack.push(88, "Smart Refrigerator", 500, 9);
	productStack.push(89, "Self-Watering Plant Pot", 20, 11);
	productStack.push(90, "Solar-Powered Backpack", 45, 13);
	productStack.push(91, "Electric Scooter", 300, 6);
	productStack.push(92, "Solar Garden Fountain", 80, 15);
	productStack.push(93, "Wireless BBQ Thermometer", 25, 8);
	productStack.push(94, "Indoor Security Camera", 70, 14);
	productStack.push(95, "Smart Umbrella", 40, 7);
	productStack.push(96, "Foldable Drone", 250, 19);
	productStack.push(97, "Bluetooth Shower Speaker", 30, 22);
	productStack.push(98, "Wireless Charging Hub", 20, 10);
	productStack.push(99, "Portable Espresso Maker", 50, 12);
	productStack.push(100, "Smart Glasses", 80, 18);




	gotoxy(17,5);
	cout << "--------------------------------------------------" << endl;
	gotoxy(17,7);
	cout << "||            Shopping Cart Using Linked List              ||" << endl;
	gotoxy(17,9);
	cout << "--------------------------------------------------" << endl;
	gotoxy(17,13);
	cout << ">>>----Project Implemented By-----<<<" << endl;
	gotoxy(22,15);
	cout << "Ali Jaffry  22K-4430" << endl;
	gotoxy(22,17);
	cout << "Zain Haider 22K-4281" << endl << endl;
	system("pause");
	system("cls");

	int choice;

	do {
		system("color Fc");
		cout << "\n\t\t|--------<Main Menu>-----------|";
		cout << "\n\n";
		cout << "\t\t 1)Customer\n";
		cout << "\t\t 2)Access Admin\n";
		cout << "\t\t 3)Exit\n";


		cout << "\n What is your choice?\n";
		cin >> choice;

		switch (choice) {

			case 1:
				customer* temp;
				temp= customerbuy(&productStack);
				if(temp!=NULL) {
					custr.pushh(temp->c,temp->totalpay);
				}

				break;
			case 2: {

				bool log= login();
				if(log==false) {
					return 1;
				} else if(log==true) {
//					system("pause");
					administrator(&productStack,&custr);

				}
				break;
			}
			case 3:


				cout << "\n\n\n\t\t\t\tThank you\n\n\n\n\n";
				return 1;
				break;

				break;
				


			default:
				cout << "\n\nYou entered an invalid choice, please try again\n\n";

		}

		system("pause");
		system("cls");
	} while (true);

	return 0;
}
