#include "CommonUtilities.h" 
#include "Authenticator.h" 
#include "DataHandle.h" 
#include "SpamFilter.h" 
#include "SubscriptionManager.h" 
#include "EmailClassifier.h" 
#include <iostream> 
#include <fstream> 
#include <string> using namespace std; 

// Initialize necessary classes 
Authenticator authenticator; 
DataHandler dataHandler; 
SpamFilter spamFilter; 
SubscriptionManager subscriptionManager; 

// Global variables 
string loggedInUser = ""; 

// Function to load sample subscriptions 
void loadSampleSubscriptions() 
{ 
	subscriptionManager.addSubscription("user@example.com", "Netflix"); 
	subscriptionManager.addSubscription("user2@example.com", "Hulu"); 
	subscriptionManager.addSubscription("user3@example.com", "Amazon Prime"); 
	subscriptionManager.addSubscription("user4@example.com", "Discord Nitro"); 
} 

// Function to display the InboxHero menu 
void inboxHeroMenu() 
{ 
	int choice; 
	string service;			// Moved declaration here 
	string emailContent;	// For case 3 
	string sender;			// For case 3 
	string confirm;			// For case 4 

	do 
	{ 
		cout << "\n===========================================\n"; 
		cout << "InboxHero Menu:\n"; 
		cout << "1. Check emails\n"; 
		cout << "2. Manage Subscriptions\n"; 
		cout << "3. Detect Spam\n"; 
		cout << "4. Sign out\n";
		cout << "===========================================\n"; 
		cout << "Enter your choice: "; 
		if (!(cin >> choice)) 
		{ 
			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			cout << "Invalid input. Please enter a number between 1 and 4.\n"; 
			continue; 
		} 
		switch (choice) 
		{ 
			case 1: 
			{ 
				cout << "Checking for new emails...\n"; 
				vector<string> emails = dataHandler.getEmails(); 
				if (emails.empty()) 
				{ 
					cout << "No new emails.\n"; 
				} 
				else 
				{ 
					cout << "You have " << emails.size() << " new emails:\n"; 
					for (const string& email : emails) 
					{ 
						cout << "- " << email << endl; 
					} 
				} 
				break; 
			} 
			case 2: subscriptionManager.listSubscriptions(); 
				cout << "Do you wish to cancel any subscription? Type 'all' or a service name: "; 
				cin >> service; 
				// Use the service variable declared earlier 
				if (service == "all") 
				{ 
					subscriptionManager.bulkUnsubscribe(); 
				} 
				else 
				{ 
					subscriptionManager.unsubscribe(service); 
				} 
			break; 
			case 3: 
			{ 
				cout << "Enter email content to check for spam: "; 
				cin.ignore(); getline(cin, emailContent); 
				// Use emailContent declared earlier 
				cout << "Enter sender address: "; 
				cin >> sender; 
				// Use sender declared earlier 
				if (spamFilter.isSpam(emailContent, sender)) 
				{ 
					cout << "This email is spam. Would you like to delete it? (Y/N): "; 
					char deleteChoice; 
					cin >> deleteChoice; 
					if (toupper(deleteChoice) == 'Y') 
					{ 
						cout << "Spam email deleted.\n"; 
					} 
				} 
				else 
				{ 
					cout << "This email is not spam.\n"; 
				} 
			break; 
			} 
			case 4: 
				cout << "Are you sure you want to sign out? (yes/no): "; 
				cin >> confirm; // Use confirm declared earlier 
				if (confirm == "yes") 
				{ 
					loggedInUser = ""; 
					return; // Exit the menu 
				} 
			break; 
			default: cout << "Invalid choice. Please select a valid option.\n"; 
		} 
	} 
	while (true); 
}

// Main function 
int main() 
{ 
	loadSampleSubscriptions(); 
	int choice; 
	do 
	{ 
		cout << "\nWelcome to InboxHero!\n"; 
		cout << "1. Sign in\n"; 
		cout << "2. Register\n"; 
		cout << "Enter your choice: "; 
		if (!(cin >> choice)) 
		{ 
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			cout << "Invalid input. Please enter 1 or 2.\n"; 
			continue; 
		} 
		if (choice == 1) 
		{ 
			cout << "Username: "; 
			string username; 
			cin >> username; 
			cout << "Password: "; 
			string password; 
			cin >> password; 
			if (authenticator.login(username, password)) 
			{ 
				cout << "Enter one of your recovery key words: "; 
				string recoveryWord; 
				cin >> recoveryWord; 
				if (authenticator.recoverAccount(username, { recoveryWord })) { loggedInUser = username; inboxHeroMenu(); 
			} 
				else 
				{ 
					cout << "Invalid recovery key.\n"; 
				} 
			} 
		} 
		if (choice == 2) 
		{ 
			// Registration process 
			cout << "Enter a username: "; 
			string username; 
			cin >> username; 
			cout << "Enter a password: "; 
			string password; 
			cin >> password; 
			cout << "Re-enter password: "; 
			string confirmPassword; 
			cin >> confirmPassword; 
			if (password == confirmPassword) 
			{ 
				authenticator.createAccount(username, password); 
				authenticator.generateRecoveryKey(username); 
				cout << "Press '1' to confirm you’ve saved your recovery key: "; 
				int confirm; 
				cin >> confirm; 
				if (confirm == 1) 
				{ 
					cout << "Account created successfully. Please sign in.\n"; 
				} 
			} 
			else 
			{ 
				cout << "Passwords do not match. Please try again.\n"; 
			} 
		} 
		else 
		{ 
			cout << "Invalid choice. Please select 1 or 2.\n"; 
		} 
	} 
	while (true); 
	return 0; 
}