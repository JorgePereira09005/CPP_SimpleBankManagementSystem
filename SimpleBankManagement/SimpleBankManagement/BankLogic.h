#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <limits>
#include <sstream>  

using namespace std;
namespace fs = std::experimental::filesystem;

string concatenateAccount(string customerName, int ID, int type) {
	string fileName = customerName + "_" + std::to_string(ID) + "_" + std::to_string(type) + ".txt";
	return fileName;
}

//read the file and copy its contents to fileVector
vector<string> copyIntoVector(string& fileName, ifstream& inputFile) {

	vector<string> fileVector;
	string line;
	//inputFile must already be open 
	while (getline(inputFile, line)) {
		fileVector.push_back(line);
	}
	inputFile.close();

	return fileVector;
}

string enterCustomerName() {

	string customerName;
	string line;
	cout << "\nType 0 in any field to exit to main menu." << endl;
	cout << "Account information. Please enter the name of the customer: ";

	while (std::getline(std::cin, customerName)) {
		if (!customerName.empty()) {
			break;
		}
		else {
			cout << "Invalid name. Try again." << endl;
		}
	}

	return customerName;
}

int enterID() {
	int ID;
	string line;
	cout << "Enter customer's ID, as it appears in the ID document: ";

	while (std::getline(std::cin, line)) {
		stringstream ss(line);
		if ((ss >> ID) && ss.eof()) {
			break;
		}
		else {
			cout << "Invalid ID number. Try again." << endl;
		}
	}
	return ID;
}

int enterType() {
	int type;
	string line;

	cout << "Enter the type of the customer's account: ";

	while (std::getline(std::cin, line)) {
		stringstream ss(line);
		if ((ss >> type) && ss.eof()) {
			if (type >= 0 && type <= 4) {
				break;
			}
		}
		else {
			cout << "Invalid account type. Try again: " << endl;
		}
	}
	return type;
}

double enterCash() {
	double cash;
	string line;

	while (std::getline(std::cin, line)) {
		stringstream ss(line);
		if ((ss >> cash) && ss.eof()) {
			break;
		}
		else {
			cout << "Invalid input. Try again." << endl;
		}
	}
	return cash;
}

int enterDateMember() {
	int num;
	string line;
	while (getline(std::cin, line))
	{
		stringstream ss(line);
		if ((ss >> num) && ss.eof())
		{
			break;
		}
		else
		{
			std::cout << "Invalid input. Try again." << std::endl;
		}
	}
	return num;
}

bool validateDate(int year, int month, int day, struct tm* t) {

	//function to check if date is valid
	if (year <= 0 || month <= 0 || day <= 0) {
		return false;
	}
	if (year > (t->tm_year + 1900) || month > 12 || day > 31) {
		return false;
	}
	if ((month == 9 || month == 4 || month == 6 || month == 11) && day > 30) {
		return false;
	}
	else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31) {
		return false;
	}

	//check if year is leap
	bool isLeap = false;
	float divisibleBy4 = year % 100;
	float divisibleBy100 = year % 100;
	float divisibleBy400 = year % 400;

	if (divisibleBy4 == 0) {
		if (divisibleBy100 != 0) {
			isLeap = true;
		}
		else if (divisibleBy100 == 0 && divisibleBy400 == 0) {
			isLeap = true;
		}
	}

	if (month == 2 && day > 29 && isLeap == true) {
		return false;
	}
	else if (month == 2 && day > 28 && isLeap == false) {
		return false;
	}
	return true;
}

//check if a given customer has at least one account to his name
bool accountsExist(string& customerName, int ID, ifstream& inputFile) {
	string fileName;

	for (int accountType = 1; accountType <= 4; accountType++) {
		fileName = concatenateAccount(customerName, ID, accountType);
		inputFile.open(fileName);

		if (inputFile.is_open()) {
			inputFile.close();
			return true;
		}
	}
	return false;
}

bool accountExist(string& fileName, ifstream& inputFile) {
	inputFile.open(fileName);
	if (inputFile.is_open()) {
		inputFile.close();
		return true;
	}
	return false;
}

void writeFile(string& fileName, ofstream& outputFile, vector<string>& vec) {
	outputFile.open(fileName, ios::trunc);
	//overwrites the existing file with the new values
	if (outputFile.is_open()) {
		for (auto line : vec) {
			outputFile << line << endl;
		}
	}
	outputFile.close();
	vec.clear();
}

int displayMainMenu() {

	int operationID;
	string line;

	cout << "\nSimple Banking Account Management System\n" << endl;
	cout << "Please choose the operation to execute" << endl;
	cout << " 1.Create new account\n 2.Update info of existing account\n 3.Transactions\n 4.View account info\n 5.Remove existing accounts\n 6.View list of accounts\n 0.Exit\n" << endl;

	cout << "Enter operation: ";
	while (std::getline(std::cin, line)) {
		//keep asking which operation is to be performed. Stop only if user types 0 or one of the 6 operations.
		stringstream ss(line);
		if ((ss >> operationID) && ss.eof())
		{
			if (operationID >= 0 && operationID < 7) {
				break;
			}
		}
		else
		{
			std::cout << "Invalid input. Try again." << std::endl;
		}
	}
	return operationID;
}

void createAccount() {

	ofstream outputFile;
	string fileName;
	string customerName;
	short dateOfBirthD = 0, dateOfBirthM = 0, dateOfBirthY = 0;
	int idNumber = 0; //unique number associated with every person, as shown in their identification document
	string country, city, street; //address
	int phoneNumber = 0, zipCode = 0;
	int type;

	time_t t = time(NULL);
	tm timeTM;
	localtime_s(&timeTM, &t);

	cout << "\nPlease enter the customer's information." << endl;

	customerName = enterCustomerName();
	if (customerName == "0") {
		return;
	}

	idNumber = enterID();
	if (idNumber == 0) {
		return;
	}

	while (true) {

		cout << "Enter customer's year of birth in the format YYYY: ";
		dateOfBirthY = enterDateMember();
		cout << "Enter customer's month of birth in the format MM: ";
		dateOfBirthM = enterDateMember();
		cout << "Enter customer's day of birth in the format DD: ";
		dateOfBirthD = enterDateMember();

		if (dateOfBirthY == 0 || dateOfBirthM == 0 || dateOfBirthD == 0) {
			return;
		}
		else if (!validateDate(dateOfBirthY, dateOfBirthM, dateOfBirthD, &timeTM)) { //validates the date
			cout << "Date is invalid. Please type the date again" << endl;
		}
		else {
			break;
		}
	}

	cout << "Enter customer's phone number: ";
	cin >> phoneNumber;

	while (cin.fail()) { 
		cin.clear();
		cin.ignore();
		cout << "Not a valid number. Please reenter: ";
		cin >> phoneNumber;
	}

	if (phoneNumber == 0) {
		return;
	}

	cout << "Enter customer's country of residence. ";
	while (true) {

		getline(cin, country);

		if (country == "0") {
			return;
		}
		else if (country.empty()) {
			cout << "Please enter a valid country name." << endl;
		}
		else {
			break;
		}
	}

	cout << "Enter customer's city of residence. ";
	while (true) {
		getline(cin, city);

		if (city == "0") {
			return;
		}
		else if (city.empty()) {
			cout << "Please enter a valid city name." << endl;
		}
		else {
			break;
		}
	}

	cout << "Enter customer's street of residence. ";
	while (true) {
		getline(cin, street);

		if (street == "0") {
			return;
		}
		else if (street.empty()) {
			cout << "Please enter a valid street name." << endl;
		}
		else {
			break;
		}
	}

	cout << "Please enter customer's zipcode: ";
	cin >> zipCode;

	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Not a valid number. Please reenter: ";
		cin >> zipCode;
	}

	if (zipCode == 0) {
		return;
	}

	while (true) {
		cout << "Please enter the type of the account to create. The types are:\n (1) Savings\n (2) Checking\n (3) 1 year Certificate of Deposit\n (4) 2 years Certificate of Deposit" << endl;
		cin >> type;

		if (type < 1 || type > 4) {
			cout << "Please enter a valid number associated with an account type." << endl;
		}
		else {
			break;
		}
	}

	fileName = concatenateAccount(customerName, idNumber, type);
	outputFile.open(fileName);

	//write the pre-defined header that holds the account info
	if (outputFile.is_open()) {
		outputFile << "Name: " << customerName << endl;
		outputFile << "ID: " << idNumber << endl;
		outputFile << "Date of birth: " << dateOfBirthD << "/" << dateOfBirthM << "/" << dateOfBirthY << endl;
		outputFile << "Phone number: " << phoneNumber << endl;
		outputFile << "Country: " << country << endl;
		outputFile << "City: " << city << endl;
		outputFile << "Street: " << street << endl;
		outputFile << "Zip code: " << zipCode << endl;

		switch (type) {
			case 1:
				outputFile << "Account type: Savings" << endl;
				break;
			case 2:
				outputFile << "Account type: Checking" << endl;
				break;
			case 3:
				outputFile << "Account type: Fixed 1 Year" << endl;
				break;
			case 4:
				outputFile << "Account type: Fixed 2 Years" << endl;
				break;
		}
		outputFile << "Balance: 0" << endl; //balance starts at 0 for any new account
		outputFile << "Account creation date: " << timeTM.tm_mday << "/" << timeTM.tm_mon + 1 << "/" << timeTM.tm_year + 1900 << endl;
		outputFile << "#" << endl; // might be useful later to detect the end of the header
		outputFile.close();

		cout << "Account successfully created" << endl;
	}
	else {
		cout << "Could not create account file." << endl;
	}
}

//function to fetch and display the info of every account associated to the specified user
void viewAccounts(string customerName, int ID) {

	ifstream inputFile;
	string fileName;
	int accountType = 1;
	string line;
	bool noAccounts = true;

	//loop will parse the files. If an account with that type exists, display the file line by line
	for (accountType; accountType <= 4; accountType++) {
		fileName = concatenateAccount(customerName, ID, accountType);
		inputFile.open(fileName);

		if (inputFile.is_open()) {
			noAccounts = false;

			while (getline(inputFile, line)) {
				cout << line << endl;
			}
			inputFile.close();
			cout << '\n';
		}
	}

	if (noAccounts) {
		cout << "No accounts found for the given customer name and ID." << endl;
	}
}

//changes a customer's address, phone number and zipcode and applies that change to all their accounts
void editAccounts(string customerName, int ID) {

	ifstream inputFile;
	ofstream outputFile;
	string fileName;
	//string line;
	string country, city, street;
	//int accountType;
	int phoneNumber = 0, zipCode = 0;

	//first check if customer has any account
	if (!accountsExist(customerName, ID, inputFile)) {
		cout << "Could not find any account associated with the specified name" << endl;
		return;
	}
	//start of input of the new values
	cout << "\nEnter customer's new phone number: ";
	cin >> phoneNumber;

	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Not a valid number. Please reenter: ";
		cin >> phoneNumber;
	}

	cout << "Enter customer's new country of residence: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (true) {

		getline(cin, country);

		if (country.empty()) {
			cout << "Please enter a valid country name." << endl;
		}
		else {
			break;
		}
	}

	cout << "Enter customer's new city of residence: ";
	while (true) {
		getline(cin, city);

		if (city.empty()) {
			cout << "Please enter a valid city name." << endl;
		}
		else {
			break;
		}
	}

	cout << "Enter customer's new street of residence: ";
	while (true) {
		getline(cin, street);

		if (street.empty()) {
			cout << "Please enter a valid street name." << endl;
		}
		else {
			break;
		}
	}

	cout << "Please enter customer's new zipcode: ";
	cin >> zipCode;

	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Not a valid number. Please reenter. ";
		cin >> zipCode;
	}

	vector<string> placeholder;

	//modify the fields in every account in the customer's name
	for (int accountType = 1; accountType <= 4; accountType++) {
		fileName = concatenateAccount(customerName, ID, accountType);
		inputFile.open(fileName);
		//put every line of the file in a vector. Since we can't directly replace lines, we will replace them once they're in a vector
		if (inputFile.is_open()) {
			placeholder = copyIntoVector(fileName, inputFile);
		}
		else {
			cout << "Could not find account of type (" << accountType << ")" << endl;
			continue;
		}

		//modify phone number, address and zipcode, which are lines 3 through 7
		placeholder[3] = "Phone number: " + to_string(phoneNumber);
		placeholder[4] = "Country: " + country;
		placeholder[5] = "City: " + city;
		placeholder[6] = "Street: " + street;
		placeholder[7] = "Zip code: " + to_string(zipCode);

		//overwrite file contents with the new values
		writeFile(fileName, outputFile, placeholder);
	}

	cout << "\nAccounts successfully edited." << endl;
}

void depositFunds(string customerName, int ID, int type, double cash) {
	//This function could easily be modified to accommodate both depositting and withdrawing funds (get the negative of cash,
	//add it to balance, create a check to make sure balance can't be negative and there is enough $$), but I find the separation 
	//of these operations to be more intuitive

	if (type > 2) {
		cout << "Cannot transfer funds from or into the specified accounts." << endl;
		return;
	}

	ifstream inputFile;
	ofstream outputFile;
	string fileName = customerName + "_" + to_string(ID) + "_" + to_string(type) + ".txt";
	vector<string> placeholder;

	time_t t = time(NULL);
	tm timeTM;
	localtime_s(&timeTM, &t);

	if (!accountExist(fileName, inputFile)) {
		cout << "Could not find any account associated with the specified name." << endl;
		return;
	}

	inputFile.open(fileName);
	//parse the file and put it in a vector
	placeholder = copyIntoVector(fileName, inputFile);
	//find the first space in the balance line ("Balance: -balance here-") and copy every char until the end of the string. That is the balance value.
	string token = placeholder[9].substr(placeholder[9].find(" ") + 1);
	double balance = stod(token) + cash;

	placeholder[9] = "Balance: " + to_string(balance);
	placeholder.push_back(to_string(timeTM.tm_year + 1900) + "/" + to_string(timeTM.tm_mon + 1) + "/" + to_string(timeTM.tm_mday) + ": successful deposit of " + to_string(cash));

	writeFile(fileName, outputFile, placeholder);

	cout << "Deposit operation successfully performed." << endl;

}

bool withdrawFunds(string customerName, int ID, int type, double cash) {

	if (type > 2 ) {
		cout << "Cannot transfer funds from or into the specified accounts." << endl;
		return false;
	}

	ifstream inputFile;
	ofstream outputFile;
	string fileName = customerName + "_" + to_string(ID) + "_" + to_string(type) + ".txt";
	vector<string> placeholder;

	time_t t = time(NULL);
	tm timeTM;
	localtime_s(&timeTM, &t);

	if (!accountExist(fileName, inputFile)) {
		cout << "Could not find any account associated with the specified name." << endl;
		return false;
	}

	inputFile.open(fileName);
	placeholder = copyIntoVector(fileName, inputFile);
	string token = placeholder[9].substr(placeholder[9].find(" ") + 1);
	double balance = stod(token) - cash;

	if (balance < 0) {
		cout << "Not enough funds to perform operation." << endl;
		return false;
	}
	else {
		placeholder[9] = "Balance: " + to_string(balance);
		placeholder.push_back(to_string(timeTM.tm_year + 1900) + "/" + to_string(timeTM.tm_mon + 1) + "/" + to_string(timeTM.tm_mday) + ": successful withdrawal of " + to_string(cash));
		writeFile(fileName, outputFile, placeholder);
		cout << "Withdrawal operation successfully performed." << endl;
		return true;
	}
}

//transfer funds from customer1 to customer2
void transferFunds(string customer1, int ID1, int type1, string customer2, int ID2, int type2, double cash) {

	if (withdrawFunds(customer1, ID1, type1, cash)) {
		depositFunds(customer2, ID2, type2, cash);
	}
}

void displayAllAccounts() {
	
	cout << "\nAccounts currently active:" << endl;
	string ext(".txt");
	fs::path cwd = fs::current_path();

	for (auto& p : fs::recursive_directory_iterator(cwd))
	{
		if (p.path().extension() == ext)
			cout << p << '\n';
	}
}

void closeAccount(string customerName, int ID, int type) {

	string temp = concatenateAccount(customerName, ID, type);
	const char* fileName = temp.c_str();

	if (remove(fileName) != 0) {
		perror("Error closing account");
	}
	else {
		cout << "Account successfully closed." << endl;
	}
}
