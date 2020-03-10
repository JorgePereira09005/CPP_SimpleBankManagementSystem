// SimpleBankManagement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "BankLogic.h"

int main() 
{
	string customerName, destinationName;
	string line;
	int ID, destinationID;
	int transaction;
	double cash;
	int type, destinationType;

	while (true) {

		int choice = displayMainMenu();

		switch (choice) {
			case 1:
				createAccount();
				break;
			case 2:
				customerName = enterCustomerName();
				ID = enterID();

				if (customerName == "0" || ID == 0) {
					break;
				}

				editAccounts(customerName, ID);
				break;
			case 3:
				customerName = enterCustomerName();
				ID = enterID();
				type = enterType();

				if (customerName == "0" || ID == 0 || type == 0) {
					break;
				}

				cout << "Please select the transaction number:\n (1) Deposit funds\n (2) Withdraw funds\n (3) Transfer funds\n (0) Exit to main menu  " << endl;
				
				while (getline(std::cin, line)) {
					stringstream ss(line);
					if ((ss >> transaction) && ss.eof()) {
						if (transaction >= 0 && transaction < 4) {
							break;
						}
					}
					else {
						cout << "Not a valid transaction number. Please reenter: ";
					}
				}

				switch (transaction) {
					case 1:					
						cout << "Enter amount of cash to deposit: ";
						cash = enterCash();
						depositFunds(customerName, ID, type, cash);
						break;
					case 2:
						cout << "Enter amount of cash to withdraw: ";
						cash = enterCash();
						withdrawFunds(customerName, ID, type, cash);
						break;
					case 3:
						cout << "Please enter the information of the destination account: " << endl;
						destinationName = enterCustomerName();
						destinationID = enterID();
						destinationType = enterType();

						if (destinationName.empty() || destinationID == 0 || destinationType == 0) {
							break;
						}

						cout << "Enter amount of cash to transfer: ";
						cash = enterCash();

						transferFunds(customerName, ID, type, destinationName, destinationID, destinationType, cash);
						break;
				}
				break;
			
			case 4:
				customerName = enterCustomerName();
				ID = enterID();

				if (customerName == "0" || ID == 0) {
					break;
				}
				viewAccounts(customerName, ID);
				break;
			case 5:
				customerName = enterCustomerName();
				ID = enterID();
				type = enterType();

				if (customerName == "0" || ID == 0 || type == 0) {
					break;
				}

				closeAccount(customerName, ID, type);
				break;
			case 6:
				displayAllAccounts();
				break;
			case 0:
				return 0;
		}
	}
}


