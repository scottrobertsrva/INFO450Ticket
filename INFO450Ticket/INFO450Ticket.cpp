// INFO450Ticket.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

enum TicketType {SERVER, APPLICATION, ACCESS};
enum PriorityLevel {LOW, MEDIUM, HIGH};
enum TicketStatus {OPEN, CLOSED};



class TechSupportTicket {
private:
	static int idGenerator;
	int id;
	string callerName;
	int category;
	int priority;
	string description;
	int usersImpacted;
	int status;
	string categories;
	static string priorityStrings[];
	static string categoryStrings[];
	static string statusStrings[];

public:
	TechSupportTicket();
	void CaptureTicket();
	void ShowTicket();
	void ShowTicketId();
	void CloseTicket();
	void SetPriority();
	int GetCategory();
	int GetPriority();
};

// Static variables and constants initialize
int TechSupportTicket::idGenerator = 1001;
string TechSupportTicket::priorityStrings[3] = { "LOW","MEDIUM","HIGH" };
string TechSupportTicket::categoryStrings[3] = { "SERVICE","APPLICAITON","ACCESS" };
string TechSupportTicket::statusStrings[2] = { "OPEN" , "CLOSED" };

// Function to display the ticket id
void TechSupportTicket::ShowTicketId() {
	cout << endl << "Your ticket id is: " << id << endl;
}


TechSupportTicket::TechSupportTicket() {
	id = idGenerator++;
	status = OPEN;
}

int TechSupportTicket::GetCategory() {
	return category;
}

int TechSupportTicket::GetPriority() {
	return priority;
}

void TechSupportTicket::ShowTicket() {
	cout << "------------------------------" << endl;
	cout << "Ticket ID: " << id << " Type: " << categoryStrings[category] << endl;
	cout << "Status: " << statusStrings[status] << endl;
	cout << "Description: " << description << endl;
	cout << "User: " << callerName << endl;
	cout << "Users Impacted: " << usersImpacted << endl;
	cout << "Priority: " << priorityStrings[priority] << endl;
	cout << "------------------------------" << endl << endl;
}

void TechSupportTicket::SetPriority() {
	if (usersImpacted < 10)
		priority = LOW;
	if (usersImpacted >= 10 && usersImpacted < 50)
		priority = MEDIUM;
	if (usersImpacted >= 50)
		priority = HIGH;
}

void TechSupportTicket::CaptureTicket() {
	bool validEntry = false;
	char issueType;
	
	// GET THE CALLER NAME
	cout << "Enter the Caller's Name:" << endl;
	getline(cin, callerName);
	
	// GET THE ISSUE TYPE
	while (!validEntry) {
		cout << "Issue Type? S=Server, A=Application, C=aCcess" << endl;
		cin >> issueType;
		cin.clear();
		cin.ignore(10000, '\n');
		if (issueType == 's' || issueType == 'S' || issueType == 'a' || issueType == 'A' || issueType == 'c' || issueType == 'C')
			validEntry = true;
	}
	if (issueType == 's' || issueType == 'S') {
		category = SERVER;
	}
	else if (issueType == 'A' || issueType == 'a') {
		category = APPLICATION;
	}
	else if (issueType == 'c' || issueType == 'C') {
		category = ACCESS;
	}

	// GET THE DESCRIPTION
	cout << "Enter the issue description:" << endl;
	getline(cin, description);

	// GET THE NUMBER OF USERS IMPACTED
	while (1) {
		cout << "Number of users impacted?" << endl;
		cin >> usersImpacted;
		if (cin.good()) {
			break;
		}
		else {
			cout << "Invalid input." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
	
	// SET THE PRIORITY
	SetPriority();

	// SHOW THE TICKET NUMBER
	ShowTicketId();

}

void TechSupportTicket::CloseTicket() {
	status = CLOSED;
}


// Class with static method to display extra credit data
class ExtraCreditDisplay {
public:
	static void DisplayExtraCreditData(TechSupportTicket tix[], int);
private:
	ExtraCreditDisplay(); // Private Constructor - Only want access to the static method.
};

void ExtraCreditDisplay::DisplayExtraCreditData(TechSupportTicket tix[], int numTickets){
	
	// 2D Array to hold the count totals
	int issueCounts[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };

	// Use enum values to index the issue count array and increment the count for each category
	for (int i = 0; i < numTickets; i++) {
		if (tix[i].GetCategory() == SERVER) {
			if (tix[i].GetPriority() == LOW) {
				issueCounts[SERVER][LOW]++;
			}
			if (tix[i].GetPriority() == MEDIUM) {
				issueCounts[SERVER][MEDIUM]++;
			}
			if (tix[i].GetPriority() == HIGH) {
				issueCounts[SERVER][HIGH]++;
			}
		}
		if (tix[i].GetCategory() == APPLICATION) {
			if (tix[i].GetPriority() == LOW) {
				issueCounts[APPLICATION][LOW]++;
			}
			if (tix[i].GetPriority() == MEDIUM) {
				issueCounts[APPLICATION][MEDIUM]++;
			}
			if (tix[i].GetPriority() == HIGH) {
				issueCounts[APPLICATION][HIGH]++;
			}
		}
		if (tix[i].GetCategory() == ACCESS) {
			if (tix[i].GetPriority() == LOW) {
				issueCounts[ACCESS][LOW]++;
			}
			if (tix[i].GetPriority() == MEDIUM) {
				issueCounts[ACCESS][MEDIUM]++;
			}
			if (tix[i].GetPriority() == HIGH) {
				issueCounts[ACCESS][HIGH]++;
			}
		}
	} // END FOR LOOP
	cout << "-------------------------------" << endl;
	cout << "Issue Summary by Type and Priority" << endl << endl;
	cout << "\t\tLOW\tMED\tHIGH" << endl;
	cout << "SERVER     \t" << issueCounts[SERVER][LOW] << "\t" << issueCounts[SERVER][MEDIUM] << "\t" << issueCounts[SERVER][HIGH] << endl;
	cout << "APPLICATION\t" << issueCounts[APPLICATION][LOW] << "\t" << issueCounts[APPLICATION][MEDIUM] << "\t" << issueCounts[APPLICATION][HIGH] << endl;
	cout << "ACCESS     \t" << issueCounts[ACCESS][LOW] << "\t" << issueCounts[ACCESS][MEDIUM] << "\t" << issueCounts[ACCESS][HIGH] << endl << endl;
} // END EXTRACREDIT DISPLAY


// MAIN ENTRY POINT
int main()
{
	TechSupportTicket tickets[100];
	char anotherTicket = 'y';
	bool validInput;
	int ticketIndex = 0;

	while (anotherTicket == 'y' || anotherTicket == 'Y') {
		validInput = false;
		while (!validInput) {
			cout << "Enter a Ticket (y or n)" << endl;
			cin >> anotherTicket;
			cin.clear();
			cin.ignore(10000, '\n');
			if (anotherTicket == 'y' || anotherTicket == 'Y' || anotherTicket == 'n' || anotherTicket == 'N') {
				validInput = true;
			}
			else {
				cout << endl << "Please enter 'y' to enter another ticket or 'n' if there are no more tickets." << endl << endl;
			}
		}
		if (anotherTicket == 'y' || anotherTicket == 'Y') {
			tickets[ticketIndex] = TechSupportTicket();
			tickets[ticketIndex].CaptureTicket();
			ticketIndex++;
		}
		else {
			ExtraCreditDisplay::DisplayExtraCreditData(tickets, ticketIndex);
			cout << "------------------------------" << endl;
			cout << "Ticket Listing:" << endl;
			
			for (int i = 0; i < ticketIndex; i++) {
				tickets[i].ShowTicket();
			}
		}
	}
    return 0;
}

