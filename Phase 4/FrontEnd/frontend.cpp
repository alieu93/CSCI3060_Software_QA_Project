#include <iostream>
#include <ostream>
#include <array>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>
#include <ctype.h>
#include <cstdio>

#include "header.h"

using namespace std;

// Methods for our transactions
void login();
void logout();
void create();
void deleteAccount();
void sell();
void buy();
void refund();
void addCredit();

// Other methods
void mainMenu();
void readFiles();
void writeToDTF1(string code, string name, string accountType, int credit);
void writeToDTF2(string code, string buyer, string seller, int refund);
void writeToDTF3(string code, string event, string seller, int numTickets, int priceTickets);
string paddingSpace(string line, bool isEvent, bool isATF);
string paddingZeros(int number, int mode);
void writeToATF(bool flag, string event, string seller, int num, double price);
void writeToUAF(string user, string type, int credits);
void deleteFromUAF(string user);
void createUserUAF(string user, string type, int credits);


// Structs for login information
User currentUser;
User *allUser;
Event *allEvent;


// Global variables
unsigned usersCount;
unsigned ticketsCount;


/*
* Main Method
* Input: Takes in user input and executes the methods according to what they enter
* Also takes in text files for the user accounts and available tickets and reads them, storing them in an array
*
* Output: Outputs console text according to what transactions they've done and the daily transaction file for each one
* Also updates the user accounts and available tickets fileu
*
*/
int main(){
    cout << "Welcome to the ticket selling service." << endl;
    login();
    return 0;
}


/*
* Starts front end session
* Asks for username input from user
*/
void login(){
    string userName;
    string command;
    bool flag = false;

    cout << "Please enter 'login' to begin." << endl;

    while(cin >> command){

        // Login command
        if(command == "login"){
            readFiles();
            cout << endl;
            cout << "Please enter your username: " << endl;
            cin >> userName;
            //cout << "You've entered: " << userName << endl;

            // Checks if username exists
            for(int i = 0; i < usersCount; i++){
                //cout << allUser[i].name << endl;
                if(allUser[i].name.compare(userName) == 0){
		    //TODO: Read from user_accounts file as opposed to hardcoded array
                    currentUser.name = allUser[i].name;
                    currentUser.accountType = allUser[i].accountType;
                    currentUser.credit = allUser[i].credit;
                    currentUser.login = true;

                    cout << "Login successful." << endl;
                    cout << endl;
                    flag = true;
                    mainMenu();
                    cout << "Please enter 'login' to begin." << endl;
                    break;
                } /*else {
                    // Should only reach this print statement if username does not exist
                    cout << "Username does not exist." << endl;
                    return;
                }*/
            }

            if(flag == false){
                cout << "Username does not exist." << endl;
                return;
            }
        } else if(command == "quit"){
            exit(0);
        } else {
            cout << "You must be logged in to perform any transactions. Please try again." << endl;
            cout << endl;
            cout << "Please enter 'login' to begin." << endl;
            return;
        }

    }
}

/*
* Handles the reading of the commands the user types in
* Leads to the other functions and outputs errors if the user is not authorized to use those transactions
* Most transactions return here after they are done correctly or not
*/
void mainMenu(){

    string command;
    cout << "Please enter a command: "<< endl;

    while(cin >> command){
        if(command == "logout"){
            cout << endl;
            logout();
            return;
        }

        else if(command == "create"){
            if(currentUser.accountType == "AA"){
                cout << endl;
                create();
                cout << "Please enter a command: "<< endl;
            } else {
                cout << "You must be an admin to create accounts." << endl;
                cout << "Please enter a command: "<< endl;
            }
        }

        else if(command == "delete"){
            if(currentUser.accountType == "AA"){
                cout << endl;
                deleteAccount();
                cout << "Please enter a command: "<< endl;
            } else {
                cout << "You must be an admin to delete accounts." << endl;
                cout << "Please enter a command: "<< endl;
            }
        }

        else if(command == "sell"){
            if(currentUser.accountType == "BS"){
                cout << "Buy accounts are not allowed to access sell transactions." << endl;
                cout << "Please enter a command: "<< endl;
            } else {
                cout << endl;
                sell();
                cout << "Please enter a command: "<< endl;
            }
        }

        else if(command == "buy"){
            if(currentUser.accountType == "SS"){
                cout << "Sell accounts are not allowed to access buy transactions." << endl;
                cout << "Please enter a command: "<< endl;
            } else {
                cout << endl;
                buy();
                cout << "Please enter a command: "<< endl;
            }
        }

        else if(command == "refund"){
            if(currentUser.accountType == "AA"){
                cout << endl;
                refund();
                cout << "Please enter a command: "<< endl;
            } else {
                cout << "You must be an admin to issue refunds." << endl;
                cout << "Please enter a command: "<< endl;
            }
        }

        else if(command == "addCredit"){
            addCredit();
            cout << "Please enter a command: "<< endl;
        }

        else{
            cout << "Error: Please enter a valid command." << endl;
            cout << "Please enter a command: "<< endl;
        }
    }
}

/*
* Ends a front end session
*/
void logout(){
    currentUser.login = false;
    cout << "Logging out, thank you for using the ticketing service system." << endl;
    cout << endl;
    writeToDTF1("00", currentUser.name, currentUser.accountType, currentUser.credit);
    return;
}

/*
* Creates a new user with purchasing and/or selling privileges
* Only for admin accounts
*/
void create(){
    string name;
    string accountType;
    bool an_flag = true;

    cout << "Please enter a username for the new account: ";
    cin >> name;

    // Check if the username entered is more than 15 characters
    if(name.length() > 15){
        cout << "Error: Username cannot be more than 15 characters." << endl;
        cout << endl;
        return;
    }

    // Check if the username entered is alphanumeric
    for(int i = 0; i < name.length(); i++){
        if(!isalnum(name[i])){
            cout << "Error: Username must have alphanumeric characters only." << endl;
            cout << endl;
            //mainMenu();
            return;
        }
    }

    // Exits to main menu if username exists
    for(int i = 0; i < usersCount; i++){
        if(allUser[i].name == name){
            cout << "Error: Username already exists." << endl;
            cout << endl;
            //mainMenu();
            return;
        }
    }

    cout << "Please specify what user account type" << endl;
    cout << "(Admin(AA), Full-Standard(FS), Sell-Standard(SS), Buy-Standard(BS)): ";
    cin >> accountType;

    if((accountType == "AA") || (accountType == "FS") || (accountType == "BS") || (accountType == "SS")){
        cout << "Account creation successful, " << name << " created as a " << accountType << " account." << endl;
        cout << endl;
        writeToDTF1("01", currentUser.name, currentUser.accountType, currentUser.credit);
        createUserUAF(name, accountType, 0);
    } else {
        cout << "Error: Invalid input. You must specify the user account type." << endl;
        cout << endl;
        //mainMenu();
        return;
    }

    //mainMenu();
    return;
}


/*
* Cancel any outstanding tickets for purchase or sale and remove the user account
* Only for admin accounts
*/
void deleteAccount(){
    string name;

    cout << "Please enter the name of the account you wish to delete: ";
    cin >> name;


    // Checks if username exists, deletes it if it does and returns to main menu
    for(int i = 0; i < usersCount; i++){
        if(allUser[i].name == name){
            cout << "Account deletion successful." << endl;
            cout << endl;
            writeToDTF1("02", currentUser.name, currentUser.accountType, currentUser.credit);
            deleteFromUAF(name);
            //mainMenu();
            return;
        }
    }

    // Only if it doesn't exist
    cout << "Error: Username does not exist." << endl;
    cout << endl;
    //mainMenu();
    return;
}

/*
* Sell a ticket or tickets to an event
* Ask for event title, sale price, number of tickets
* All accounts except for buy can access this function
*/
void sell(){
	string eventName;
	string sellerName =  currentUser.name;
	double ticketPrice;
	int numOfTickets;

	cout << "Please enter an event title: " << endl;
	cin >> eventName;

    // Check for event name length
	if(eventName.length() > 19){
        cout << "Error: Event name cannot be more than 19 characters." << endl;
        cout << endl;
        //mainMenu();
        return;
	}

    // check if event doesn't already exist
    for(int i = 0; i < ticketsCount; i++){
        if(allEvent[i].event == eventName){
            cout << "Error: Event name already exists." << endl;
            cout << endl;
            //mainMenu();
            return;
        }
    }

	cout << "Please enter a sale price for each ticket: " << endl;
	cin >> ticketPrice;

    // Check for valid price input
    if(ticketPrice <= 0){
        cout << "Error: Ticket price must be a positive number." << endl;
        cout << endl;
        //mainMenu();
        return;
    } else if(ticketPrice > 999.99){
        cout << "Error: Ticket price cannot be over 999.99." << endl;
        cout << endl;
        //mainMenu();
        return;
    }


	cout << "Please enter the number of tickets for sale: ";
	cin >> numOfTickets;

	// Check for valid input, cannot be less than 0 or more than 100
	if(numOfTickets <= 0){
        cout << "Error: Number of tickets must be more than zero." << endl;
        cout << endl;
        //mainMenu();
        return;
    // more than 100
	} else if (numOfTickets > 100) {
	    cout << "Error: Number of tickets cannot be more than 100." << endl;
	    cout << endl;
	    //mainMenu();
	    return;
	}


	cout << "Sell transaction successful. Event created." << endl;
	cout << endl;

	writeToDTF3("03", eventName, sellerName, numOfTickets, ticketPrice);
	writeToATF(true, eventName, sellerName, numOfTickets, ticketPrice);
	//mainMenu();
	return;
}

/*
* Purchase a ticket or tickets to an event
* Ask for event title, number of tickets, and seller's username
* display cost per ticket and total cost and ask for confirmation (y/n)
* subtract number of tickets from seller's inventory
* All accounts except for sell accounts can access this function
*/
void buy(){
	string eventName;
	string sellerName;
	string confirmation;

	int numOfTickets;
	double priceOfTicket;
	double total;
	bool eventExists;
	bool existsFlag;
	bool adminFlag;

	Event currentEvent;

	cout << "Please enter the name of the event: ";
	cin >> eventName;

    // Check if event entered exceeds 25 characters
	if(eventName.length() > 25){
        cout << "Error: Event name cannot be more than 25 characters." << endl;
        cout << endl;
        //mainMenu();
        return;
	}

	// Check if event exists
	for(int i = 0; i < ticketsCount; i++){
        if(allEvent[i].event == eventName){
            eventExists = true;
            currentEvent.event = allEvent[i].event;
            currentEvent.numOfTickets = allEvent[i].numOfTickets;
            currentEvent.priceOfTickets = allEvent[i].priceOfTickets;
            currentEvent.seller = allEvent[i].seller;
            break;
        }
    }
    // Goes back to main menu if event does not exist
    if(eventExists != true){
        cout << "Error: Event does not exist." << endl;
        cout << endl;
        //mainMenu();
        return;
    }

    cout << "Please specify the amount of tickets to buy." << endl;
    cin >> numOfTickets;

    // Check for valid input, depending on user account type
    if(currentUser.accountType == "AA"){
        adminFlag = true;
    } else {
        adminFlag = false;
    }

    //cout << currentEvent.numOfTickets << endl;
    // Check if event has enough tickets
    if(numOfTickets > currentEvent.numOfTickets){
        cout << "Error: Event does not have enough tickets available." << endl;
        cout << endl;
        //mainMenu();
        return;
    }

    // If admin account
    if(adminFlag == true){
        if(numOfTickets <= 0){
            cout << "Error: Specified ticket amount must be positive." << endl;
            cout << endl;
            //mainMenu();
            return;
        }
    // If standard account
    } else {
        if(numOfTickets <= 0){
            cout << "Error: Specified ticket amount must be positive." << endl;
            cout << endl;
            //mainMenu();
            return;
        } else if (numOfTickets > 4){
            cout << "Error: Cannot buy more than 4 tickets unless you have an admin account." << endl;
            cout << endl;
            //mainMenu();
            return;
        }
    }

	cout << "Please enter the seller's username: ";
	cin >> sellerName;

	// Check if selelr's username exists
    if(sellerName != currentEvent.seller){
        cout << "Error: The specified username does not exist." << endl;
        cout << endl;
        //mainMenu();
        return;
    }

    int sellerCredits;
    for(int i = 0; i < usersCount; i++){
        if(allUser[i].name == sellerName){
            sellerCredits = allUser[i].credit;
        }
    }

    int totalPrice = numOfTickets * currentEvent.priceOfTickets;

    cout << "The cost of one ticket is " << currentEvent.priceOfTickets << " and the total cost is " << totalPrice << endl;
    cout << "Do you wish to continue? (y/n)";
    while(cin >> confirmation != "y" || cin >> confirmation != "n"){
        if(confirmation == "y"){
            break;
        } else if(confirmation == "n"){
            cout << "Buy transaction cancelled." << endl;
            cout << endl;
            mainMenu();
        } else {
            cout << "Error: You must enter 'y' or 'n' to continue." << endl;
            cin >> confirmation;
        }
    }

    // Check if user has enough money to make the purchase
    if(currentUser.credit < totalPrice){
        cout << "Error: You do not have enough credits to make this purchase." << endl;
        cout << endl;
        //mainMenu();
        return;
    }

    // Subtracts from user's total credits
    currentUser.credit -= totalPrice;
    currentEvent.numOfTickets -= numOfTickets;

	cout << "Buy transaction successful." << endl;
	cout << endl;
	writeToDTF3("04", eventName, sellerName, currentEvent.numOfTickets, currentEvent.priceOfTickets);
	writeToUAF(currentUser.name, currentUser.accountType, currentUser.credit);
	writeToUAF(sellerName, "SS", sellerCredits + totalPrice);
	writeToATF(false, eventName, sellerName, currentEvent.numOfTickets, currentEvent.priceOfTickets);
	//mainMenu();
	return;
}

/*
* Issue a credit to a buyer's account from a seller's account
* Ask for buyer's username, seller's username, amount of credit to transfer
* Should transfer specified amount from seller's credit balance to buyer's credit balance
* Only admins may access this function
*/
void refund(){
	int amount;
	double buyerCredits;
	double sellerCredits;
	string buyerName;
	string sellerName;
    bool buyerExists;
    bool sellerExists;

	cout << "Please enter the buyer's username: ";
	cin >> buyerName;

	// Check if buyer account exists
    for(int i = 0; i < usersCount; i++){
        if(allUser[i].name == buyerName && allUser[i].accountType == "BS"){
            buyerExists = true;
            buyerCredits = allUser[i].credit;
            break;
        }
    }
    // Send back to main menu and output error if account does not exist
    if(!buyerExists){
        cout << "Error: Buyer Account does not exist." << endl;
        cout << endl;
        //mainMenu();
        return;
    }

	cout << "Please enter the seller's username: ";
	cin >> sellerName;

    // Check if seller account exists
    for(int i = 0; i < usersCount; i++){
        if(allUser[i].name == sellerName && allUser[i].accountType == "SS"){
            sellerExists = true;
            sellerCredits = allUser[i].credit;
            break;
        }
    }
    // Send back to main menu and output error if seller account does not exist
    if(!sellerExists){
        cout << "Error: Seller Account does not exist." << endl;
        cout << endl;
        //mainMenu();
        return;
    }

	cout << "Please enter the amount of credits to be refunded: ";
	cin >> amount;

    if(amount <= 0){
        cout << "Error: Amount must be positive." << endl;
        cout << endl;
        //mainMenu();
        return;
    }

    if(sellerCredits < amount){
        cout << "Error: Seller does not have enough credits for this refund." << endl;
        cout << endl;
        //mainMenu();
        return;
    }

	cout << "Refund transaction successful." << endl;
	cout << endl;

    // Write to Daily Transaction file
	writeToDTF2("05", buyerName, sellerName, amount);
	writeToUAF(sellerName, "SS", sellerCredits - amount);
	writeToUAF(buyerName, "BS", buyerCredits + amount);
	//mainMenu();
	return;
}


/*
* Add credit into the system for the purchase of accounts
* Ask for amount to add and username of the account (Admin)
* Ask for amount of credits (Standard accounts)
*/
void addCredit(){
	string userName;
	string userNameType;
	int userNameCredits;
	double credits;
	bool userExists;
    bool adminFlag = false;

    if(currentUser.accountType == "AA"){
        adminFlag = true;
    }
    if(adminFlag == true){
        cout << "Please enter the account that the credits will be added to: ";
        cin >> userName;

        // Check if username exists
        for(int i = 0; i < usersCount; i++){
            if(allUser[i].name == userName){
                userExists = true;
                userNameType = allUser[i].accountType;
                userNameCredits = allUser[i].credit;
                break;
            }
        }

        // Goes back to main menu if username does not exist
        if(userExists != true){
            cout << "Error: Username does not exist." << endl;
            cout << endl;
            //mainMenu();
            return;
        }
    } else {
        userName = currentUser.name;
    }
	//cout << userName;
	cout << "Please enter the amount of credits to be added: ";
	cin >> credits;

	// Check if credits entered is valid, goes back to mainMenu and outputs error if not valid
	if(credits > 1000){
        cout << "Error: Amount cannot be more than $1000." << endl;
        cout << endl;
        //mainMenu();
        return;
	} else if (credits <= 0){
	    cout << "Error: Amount must be positive." << endl;
	    cout << endl;
	    //mainMenu();
	    return;
	}


	cout << "Credits added to account successful." << endl;
	cout << endl;

    if(currentUser.name == userName){
        currentUser.credit += credits;
	//cout << currentUser.credit << endl;
        writeToUAF(currentUser.name, currentUser.accountType, currentUser.credit);
        writeToDTF1("06", currentUser.name, currentUser.accountType, currentUser.credit);
    } else {
        writeToUAF(userName, userNameType, userNameCredits + credits);
        writeToDTF1("06", currentUser.name, currentUser.accountType, currentUser.credit);
    }


	//mainMenu();
	return;
}

/*
* Used to handle the reading of the available tickets file
* and current users file
*/
void readFiles(){
    int counter = 0;
    // Text files
    string UAF = "user_accounts.txt";
    string ATF = "available_tickets.txt";

    // Input streams
    ifstream numOfUsersStream(UAF);
    ifstream numOfTicketsStream(ATF);
    ifstream userStream(UAF);
    ifstream ticketStream(ATF);

    // Storing each line in text file for both text files
    string userLine;
    string ticketLine;

    numOfUsersStream.unsetf(ios_base::skipws);
    numOfTicketsStream.unsetf(ios_base::skipws);

	// Each line equals to 1 user and 1 event, counts the amount for each
	// Amount is used throughout the program
    if(numOfUsersStream.is_open() && numOfTicketsStream.is_open()){
        usersCount = count(istream_iterator<char>(numOfUsersStream), istream_iterator<char>(), '\n') + 1;
        ticketsCount = count(istream_iterator<char>(numOfTicketsStream), istream_iterator<char>(), '\n') + 1;
    }
    numOfUsersStream.close();
    numOfTicketsStream.close();
    //cout << "Users Count: " << usersCount << endl;
    //cout << "tickets Count: " << ticketsCount << endl;
    allUser = new User[usersCount];
    allEvent = new Event[ticketsCount];

    // For user account file
    while(getline(userStream, userLine)){
        // Format: UUUUUUUUUUUUUUU_TT_CCCCCCCCC
        User tempUser;
        // We know that Username takes 15 characters and always the first 15
        tempUser.name = userLine.substr(0, 15);
        // str.erase (std::remove(str.begin(), str.end(), chars[i]), str.end());
        tempUser.name.erase(remove(tempUser.name.begin(), tempUser.name.end(), '_'), tempUser.name.end());
        // Account Type
        tempUser.accountType = userLine.substr(16, 2);
        // Credits for the account
        // Convert to double
        tempUser.credit = atoi((userLine.substr(19).c_str()));
        // Initialize Login state
        tempUser.login = false;
        allUser[counter] = tempUser;
        counter++;

    }

    userStream.close();



    counter = 0;
    // For the ticket file
    while(getline(ticketStream, ticketLine)){
        // Format: EEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP
        Event tempEvent;
        // Know that Event name is 19 characters long
        tempEvent.event = ticketLine.substr(0, 19);
        tempEvent.event.erase(remove(tempEvent.event.begin(), tempEvent.event.end(), '_'), tempEvent.event.end());
        // Seller username
        tempEvent.seller = ticketLine.substr(20,14);
        tempEvent.seller.erase(remove(tempEvent.seller.begin(), tempEvent.seller.end(), '_'), tempEvent.seller.end());
        // Number of tickets
        tempEvent.numOfTickets = atoi((ticketLine.substr(34, 3)).c_str());
        //cout << ticketLine << endl;
        //cout << tempEvent.numOfTickets << endl;
        // Ticket price
        tempEvent.priceOfTickets = atoi((ticketLine.substr(39)).c_str());
        allEvent[counter] = tempEvent;
        counter++;

    }
    ticketStream.close();
    return;
}

/*
* Used to write to the Daily Transaction File for
* 01-create, 02-delete, 06-addcredit, 00-end of session
*/
void writeToDTF1(string code, string name, string accountType, int credit){
    stringstream ss;

    // Padding applied to name and credits to fit the format
    name = paddingSpace(name, false ,false);
    string str_credit = paddingZeros(credit, 1);

    // Store all of it into a stringstream

    ss << code << "_" << name << "_" << accountType << "_" << str_credit << "\n";
    string completeTransaction = ss.str();

    //cout << completeTransaction << endl;

    // Open text file and write to it
    ofstream DTF;
    DTF.open("daily_transaction_file.txt", ios::app | ios::ate);
    DTF << completeTransaction;
    DTF.close();
    return;
}

/*
* Used to write to the daily transaction file for
* 05-refund
*/
void writeToDTF2(string code, string buyer, string seller, int refund){
    stringstream ss;

    buyer = paddingSpace(buyer, false, false);
    seller = paddingSpace(seller, false, false);

    string str_refund = paddingZeros(refund, 1);

    ss << code << "_" << buyer << "_" << seller << "_" << str_refund << "\n";

    string completeTransaction = ss.str();

    //cout << completeTransaction << endl;

    ofstream DTF;
    DTF.open("daily_transaction_file.txt", ios::app | ios::ate);
    DTF << completeTransaction;
    DTF.close();
    return;
}

/*
* Used to write to the daily transaction file for
* 03-sell, 04-buy
*/
void writeToDTF3(string code, string event, string seller, int numTickets, int priceTickets){
    stringstream ss;

    event = paddingSpace(event, true, false);
    seller = paddingSpace(seller, false, false);
    string str_num = paddingZeros(numTickets, 2);
    string str_price = paddingZeros(priceTickets, 3);

    ss << code << "_" << event << "_" << seller << "_" << str_num << "_" << str_price << "\n";

    string completeTransaction = ss.str();

    //cout << completeTransaction << endl;

    ofstream DTF;
    DTF.open("daily_transaction_file.txt", ios::app | ios::ate);
    DTF << completeTransaction;
    DTF.close();
    return;
}

/*
* Used to pad out strings like usernames or event names
* isEvent indicates whether or not it is an event string
*/
string paddingSpace(string line, bool isEvent, bool isATF){
    // 19 characters for events
    // 15 characters for usernames
    // bool to indicate if event or not
    if(isEvent == true){
        if(line.length() < 19){
            while(line.length() < 19){
                line.append("_");
            }
        }
    } else {
    //TODO: Change this later for whether or not we just use 13 or 15, not both
        if(!isATF){
            if(line.length() < 15){
                while(line.length() < 15){
                    line.append("_");
                }
            }
        } else {
            if(line.length() < 15){
                while(line.length() < 15){
                    line.append("_");
                }
            }
        }


    }
    return line;
}

/*
* Used to pad zeroes on numeric values
* Mode represents what kind of input it is (credits, number of tickets, price of tickets)
* Credits = 1, number of tickets = 2, price of tickets = 3
*/
string paddingZeros(int number, int mode){
    stringstream ss;
    ss << number;
    string str = ss.str();

    // Credits - 9 characters
    if(mode == 1){
        if(str.length() < 9){
            while(str.length() < 9){
                str.insert(str.begin(), '0');
            }
        }
    }
    // Number of tickets - 3 characters
    if(mode == 2){
        if(str.length() < 3){
            while(str.length() < 3){
                str.insert(str.begin(), '0');
            }
        }
    }
    // Price of tickets - 6 characters
    if(mode == 3){
        if(str.length() < 6){
            while(str.length() < 6){
                str.insert(str.begin(), '0');
            }
        }
    }
    return str;
}
void writeToATF(bool flag, string event, string seller, int num, double price){

    //If sell
    if(flag == true){
        stringstream ss;

        event = paddingSpace(event, true, false);
        seller = paddingSpace(seller, false, true);
        string str_num = paddingZeros(num, 2);
        string str_price = paddingZeros(price, 3);

        ss << "\n" <<event << "_" << seller << "_" << str_num << "_" << str_price;

        string completeTransaction = ss.str();


        ofstream ATF;
        ATF.open("available_tickets.txt", ios::app | ios::ate);
        ATF << completeTransaction;
        ATF.close();
    } else {
        string completeTransaction;
        ofstream outFile("available_tickets.txt");


        for(int i = 0; i < ticketsCount; i++){
            if(allEvent[i].event == event){
                allEvent[i].event = event;
                allEvent[i].seller = seller;
                allEvent[i].numOfTickets = num;
                allEvent[i].priceOfTickets = price;

            }

            stringstream ss;
            string tempEvent = paddingSpace(allEvent[i].event, true, false);
            string tempSeller = paddingSpace(allEvent[i].seller, false, true);
            string str_num = paddingZeros(allEvent[i].numOfTickets, 2);
            string str_price = paddingZeros(allEvent[i].priceOfTickets, 3);

            if(i == ticketsCount - 1){
                ss << tempEvent << "_" << tempSeller << "_" << str_num << "_" << str_price;
            } else {
                ss << tempEvent << "_" << tempSeller << "_" << str_num << "_" << str_price << "\n";
            }
            completeTransaction += ss.str();

        }

        outFile << completeTransaction;
        outFile.close();
    }
    return;
}

void writeToUAF(string user, string type, int credits){

    string completeTransaction;

    //user = paddingSpace(user, false, false);
    //string str_credit = paddingZeros(credits, 1);

    ofstream outFile("user_accounts.txt");

    for(int i = 0; i < usersCount; i++){
        if(allUser[i].name == user){
            allUser[i].name = user;
            allUser[i].accountType = type;
            allUser[i].credit = credits;
        }
        stringstream ss;

        string tempUser = paddingSpace(allUser[i].name, false, false);
        string tempType = allUser[i].accountType;
        string str_credit = paddingZeros(allUser[i].credit, 1);

	//cout << tempUser << endl;

        if(i == usersCount - 1){
            //ss << "\n" << tempUser << "_" << tempType << "_" << str_credit;
	    completeTransaction += ss.str();
        } else if (i == 0) {
            ss << tempUser << "_" << tempType << "_" << str_credit;
	    completeTransaction += ss.str();
        } else {
	    ss << "\n" << tempUser << "_" << tempType << "_" << str_credit;
	    completeTransaction += ss.str();
	}

	//ss << "\n" << tempUser << "_" << tempType << "_" << str_credit;
        //completeTransaction += ss.str();



    }
    outFile << completeTransaction;
    outFile.close();
    return;

}

void deleteFromUAF(string user){
    string completeTransaction;
    bool flag;

    //user = paddingSpace(user, false, false);
    //string str_credit = paddingZeros(credits, 1);

    ofstream outFile("user_accounts.txt");

    for(int i = 0; i < usersCount; i++){
        if(allUser[i].name == user){
            //allUser[i].name = "";
            //allUser[i].accountType = "";
            //allUser[i].credit = 0;
            flag = true;
        } else {
	    flag = false;
	    stringstream ss;

            string tempUser = paddingSpace(allUser[i].name, false, false);
            string tempType = allUser[i].accountType;
            string str_credit = paddingZeros(allUser[i].credit, 1);

            if(i == usersCount - 1){
                /*ss << "\n" << tempUser << "_" << tempType << "_" << str_credit;
		cout << tempUser << endl;
		completeTransaction += ss.str();*/
	    } else if (i == 0) {
            	ss << tempUser << "_" << tempType << "_" << str_credit;
	        completeTransaction += ss.str();
            } else {
                ss << "\n" << tempUser << "_" << tempType << "_" << str_credit;
                completeTransaction += ss.str();
            }

	}
        /*if(flag == false){
            stringstream ss;

            string tempUser = paddingSpace(allUser[i].name, false, false);
            string tempType = allUser[i].accountType;
            string str_credit = paddingZeros(allUser[i].credit, 1);

            if(i == usersCount - 1 || i == 0){
                ss << tempUser << "_" << tempType << "_" << str_credit;
            } else {
                ss << "\n" << tempUser << "_" << tempType << "_" << str_credit;
            }
            completeTransaction += ss.str();
        }*/

    }
    outFile << completeTransaction;
    outFile.close();
    return;

}

void createUserUAF(string user, string type, int credits){
        stringstream ss;

        string tempUser = paddingSpace(user, false, false);
        string tempType = type;
        string str_credit = paddingZeros(credits, 1);
        //cout << tempUser;
        // May or may not break in Linux, may cause an extra line
        ss << "\n" << tempUser << "_" << tempType << "_" << str_credit;

        string completeTransaction = ss.str();


        ofstream UAF;
        UAF.open("user_accounts.txt", ios::ate | ios::app);
        UAF << completeTransaction;
        UAF.close();
        return;
}
