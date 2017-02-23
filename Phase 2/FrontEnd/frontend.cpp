#include <iostream>
#include <array>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>

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
string paddingSpace(string line, bool isEvent);
string paddingZeros(int number, int mode);

// Structs for login information
User currentUser;
User *allUser;
Event *allEvent;

// Temporary hardcoded information, no actual files just yet
string users[] = {"admin", "buystduser", "sellstduser", "fullstduser", "user001", "user002", "user003"};
string usersType[] = {"AA", "BS", "SS", "FS", "FS", "FS", "SS"};
double usersCredits[] = {100.00, 200.00, 30.00, 66.00, 0.00, 2.00, 3.00};
int numOfUsers = sizeof(users) / sizeof(users[0]);

// Global variables
unsigned usersCount;
unsigned ticketsCount;


/*
* Main Method
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

    cout << "Please enter 'login' to begin." << endl;

    while(cin >> command){

        // Login command
        if(command == "login"){
            readFiles();
            cout << endl;
            cout << "Please enter your username: " << endl;
            cin >> userName;
            cout << "You've entered: " << userName << endl;

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
                    mainMenu();
                }
            }
            // Should only reach this print statement if username does not exist
            cout << "Username does not exist." << endl;
            login();
        } else {
            cout << "You must be logged in to perform any transactions. Please try again." << endl;
            cout << endl;
            login();
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
        }

        else if(command == "create"){
            if(currentUser.accountType == "AA"){
                cout << endl;
                create();
            } else {
                cout << "You must be an admin to create accounts." << endl;
            }
        }

        else if(command == "delete"){
            if(currentUser.accountType == "AA"){
                cout << endl;
                deleteAccount();
            } else {
                cout << "You must be an admin to delete accounts." << endl;
            }
        }

        else if(command == "sell"){
            if(currentUser.accountType == "BS"){
                cout << "Buy accounts are not allowed to access sell transactions." << endl;
            } else {
                cout << endl;
                sell();
            }
        }

        else if(command == "buy"){
            if(currentUser.accountType == "SS"){
                cout << "Sell accounts are not allowed to access buy transactions." << endl;
            } else {
                cout << endl;
                buy();
            }
        }

        else if(command == "refund"){
            if(currentUser.accountType == "AA"){
                cout << endl;
                refund();
            } else {
                cout << "You must be an admin to issue refunds." << endl;
            }
        }

        else if(command == "addCredit"){
            addCredit();
        }

        else{
            cout << "Error: Please enter a valid command." << endl;
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
    login();
}

/*
* Creates a new user with purchasing and/or selling privileges
* Only for admin accounts
*/
void create(){
    //TODO: Need to write to Daily Transaction File
    string name;
    string accountType;

    cout << "Please enter a username for the new account: ";
    cin >> name;

    // Check if the username entered is more than 15 characters
    if(name.length() > 15){
        cout << "Error: Username cannot be more than 15 characters." << endl;
        cout << endl;
        mainMenu();
    }

    // Exits to main menu if username exists
    for(int i = 0; i < usersCount; i++){
        if(allUser[i].name == name){
            cout << "Error: Username already exists." << endl;
            cout << endl;
            mainMenu();
        }
    }

    cout << "Please specify what user account type" << endl;
    cout << "(Admin(AA), Full-Standard(FS), Sell-Standard(SS), Buy-Standard(BS)): ";
    cin >> accountType;

    if((accountType == "AA") || (accountType == "FS") || (accountType == "BS") || (accountType == "SS")){
        cout << "Account creation successful, " << name << " created as a " << accountType << " account." << endl;
        cout << endl;
        writeToDTF1("01", currentUser.name, currentUser.accountType, currentUser.credit);
    } else {
        cout << "Error: Invalid input. You must specify the user account type." << endl;
        cout << endl;
        mainMenu();
    }

    mainMenu();
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
	    //TODO: read from user accounts file instead of hardcoded array
            cout << "Account deletion successful." << endl;
            cout << endl;
            writeToDTF1("02", currentUser.name, currentUser.accountType, currentUser.credit);
            mainMenu();
        }
    }

    // Only if it doesn't exist
    cout << "Error: Username does not exist." << endl;
    cout << endl;
    mainMenu();
}

/*
* Sell a ticket or tickets to an event
* Ask for event title, sale price, number of tickets
* All accounts except for buy can access this function
*/
void sell(){
	string eventName;
	string sellerName;
	double ticketPrice;
	int numOfTickets;

	cout << "Please enter an event title: " << endl;
	cin >> eventName;

    // Check for event name length
	if(eventName.length() > 19){
        cout << "Error: Event name cannot be more than 19 characters." << endl;
        cout << endl;
        mainMenu();
	}

    // check if event doesn't already exist
    for(int i = 0; i < ticketsCount; i++){
        if(allEvent[i].event == eventName){
            cout << "Error: Event name already exists." << endl;
            cout << endl;
            mainMenu();
        }
    }

	cout << "Please enter a sale price for each ticket: " << endl;
	cin >> ticketPrice;

    // Check for valid price input
    if(ticketPrice <= 0){
        cout << "Error: Ticket price must be a positive number." << endl;
        cout << endl;
        mainMenu();
    } else if(ticketPrice > 999.99){
        cout << "Error: Ticket price cannot be over 999.99." << endl;
        cout << endl;
        mainMenu();
    }


	cout << "Please enter the number of tickets for sale: ";
	cin >> numOfTickets;

	// Check for valid input, cannot be less than 0 or more than 100
	if(numOfTickets <= 0){
        cout << "Error: Number of tickets must be more than zero." << endl;
        cout << endl;
        mainMenu();
    // more than 100
	} else if (numOfTickets > 100) {
	    cout << "Error: Number of tickets cannot be more than 100." << endl;
	    cout << endl;
	    mainMenu();
	}


	cout << "Sell transaction successful. Event created." << endl;
	cout << endl;

	writeToDTF3("03", eventName, sellerName, numOfTickets, ticketPrice);
	mainMenu();
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
        mainMenu();
    }

    cout << "Please specify the amount of tickets to buy." << endl;
    cin >> numOfTickets;

    // Check for valid input, depending on user account type
    if(currentUser.accountType == "AA"){
        adminFlag = true;
    } else {
        adminFlag = false;
    }

    // Check if event has enough tickets
    if(numOfTickets < currentEvent.numOfTickets){
        cout << "Error: Event does not have enough tickets available." << endl;
        cout << endl;
        mainMenu();
    }

    // If admin account
    if(adminFlag == true){
        if(numOfTickets <= 0){
            cout << "Error: Specified ticket amount must be positive." << endl;
            cout << endl;
            mainMenu();
        }
    // If standard account
    } else {
        if(numOfTickets <= 0){
            cout << "Error: Specified ticket amount must be positive." << endl;
            cout << endl;
            mainMenu();
        } else if (numOfTickets > 4){
            cout << "Error: Cannot buy more than 4 tickets unless you have an admin account." << endl;
            cout << endl;
            mainMenu();
        }
    }

	cout << "Please enter the seller's username: ";
	cin >> sellerName;

	// Check if selelr's username exists
    if(sellerName != currentEvent.seller){
        cout << "Error: The specified username does not exist." << endl;
        cout << endl;
        mainMenu();
    }

    cout << "The cost of one ticket is " << currentEvent.priceOfTickets << " and the total cost is " << numOfTickets * currentEvent.priceOfTickets << endl;
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



	cout << "Buy transaction successful." << endl;
	cout << endl;
	writeToDTF3("04", eventName, sellerName, currentEvent.numOfTickets, currentEvent.priceOfTickets);
	mainMenu();
}

/*
* Issue a credit to a buyer's account from a seller's account
* Ask for buyer's username, seller's username, amount of credit to transfer
* Should transfer specified amount from seller's credit balance to buyer's credit balance
* Only admins may access this function
*/
void refund(){
	double amount;
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
            break;
        }
    }
    // Send back to main menu and output error if account does not exist
    if(!buyerExists){
        cout << "Error: Buyer Account does not exist." << endl;
        cout << endl;
        mainMenu();
    }

	cout << "Please enter the seller's username: ";
	cin >> sellerName;

    // Check if seller account exists
    for(int i = 0; i < usersCount; i++){
        if(allUser[i].name == sellerName && allUser[i].accountType == "SS"){
            sellerExists = true;
            break;
        }
    }
    // Send back to main menu and output error if seller account does not exist
    if(!sellerExists){
        cout << "Error: Seller Account does not exist." << endl;
        cout << endl;
        mainMenu();
    }

	cout << "Please enter the amount of credits to be refunded: ";
	cin >> amount;

	//TODO: Verify if buyer and seller username is valid, if amount is valid and modify user information accordingly

	cout << "Refund transaction successful." << endl;
	cout << endl;

    // Write to Daily Transaction file
	writeToDTF2("05", buyerName, sellerName, amount);
	mainMenu();
}


/*
* Add credit into the system for the purchase of accounts
* Ask for amount to add and username of the account (Admin)
* Ask for amount of credits (Standard accounts)
*/
void addCredit(){
	string userName;
	double credits;
	bool userExists;

	cout << "Please enter the account that the credits will be added to: ";
	cin >> userName;

    // Check if username exists
    for(int i = 0; i < usersCount; i++){
        if(allUser[i].name == userName){
            userExists = true;
            break;
        }
    }

    // Goes back to main menu if username does not exist
    if(userExists != true){
        cout << "Error: Username does not exist." << endl;
        cout << endl;
        mainMenu();
    }

	cout << "Please enter the amount of credits to be added: ";
	cin >> credits;

	// Check if credits entered is valid, goes back to mainMenu and outputs error if not valid
	if(credits > 1000){
        cout << "Error: Amount cannot be more than $1000." << endl;
        cout << endl;
        mainMenu();
	} else if (credits <= 0){
	    cout << "Error: Amount must be positive." << endl;
	    cout << endl;
	    mainMenu();
	}


	cout << "Credits added to account successful." << endl;
	cout << endl;

	writeToDTF1("06", currentUser.name, currentUser.accountType, currentUser.credit);

	mainMenu();
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
        tempEvent.numOfTickets = atoi((ticketLine.substr(35, 3)).c_str());
        // Ticket price
        tempEvent.priceOfTickets = atoi((ticketLine.substr(39)).c_str());
        allEvent[counter] = tempEvent;
        counter++;

    }
    ticketStream.close();

}

/*
* Used to write to the Daily Transaction File for
* 01-create, 02-delete, 06-addcredit, 00-end of session
*/
void writeToDTF1(string code, string name, string accountType, int credit){
    stringstream ss;

    // Padding applied to name and credits to fit the format
    name = paddingSpace(name, false);
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
}

/*
* Used to write to the daily transaction file for
* 05-refund
*/
void writeToDTF2(string code, string buyer, string seller, int refund){
    stringstream ss;

    buyer = paddingSpace(buyer, false);
    seller = paddingSpace(seller, false);

    string str_refund = paddingZeros(refund, 1);

    ss << code << "_" << buyer << "_" << seller << "_" << str_refund << "\n";

    string completeTransaction = ss.str();

    //cout << completeTransaction << endl;

    ofstream DTF;
    DTF.open("daily_transaction_file.txt", ios::app | ios::ate);
    DTF << completeTransaction;
    DTF.close();
}

/*
* Used to write to the daily transaction file for
* 03-sell, 04-buy
*/
void writeToDTF3(string code, string event, string seller, int numTickets, int priceTickets){
    stringstream ss;

    event = paddingSpace(event, true);
    seller = paddingSpace(seller, false);
    string str_num = paddingZeros(numTickets, 2);
    string str_price = paddingZeros(priceTickets, 3);

    ss << code << "_" << event << "_" << seller << "_" << str_num << "_" << str_price << "\n";

    string completeTransaction = ss.str();

    //cout << completeTransaction << endl;

    ofstream DTF;
    DTF.open("daily_transaction_file.txt", ios::app | ios::ate);
    DTF << completeTransaction;
    DTF.close();
}

/*
* Used to pad out strings like usernames or event names
* isEvent indicates whether or not it is an event string
*/
string paddingSpace(string line, bool isEvent){
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
        if(line.length() < 15){
            while(line.length() < 15){
                line.append("_");
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
