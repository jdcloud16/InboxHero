#pragma once
#include <string> 
#include <set> 
#include <vector> 
#include <iostream> // For listing blocked senders 

using namespace std; 

class SpamFilter { 
public: 
	// Constructor 
	SpamFilter(); 
	
	// Method to determine if an email is spam 
	bool isSpam(const string& emailContent, const string& sender); 
	
	// Method to block a sender 
	void blockSender(const string& sender); 
	
	// Method to unblock a sender 
	void unblockSender(const string& sender); 
	
	// Method to list all blocked senders 
	void listBlockedSenders() const; 

private: 
		// Set of blocked email addresses or domains 
		set<string> blockedSenders; 
		// Set of common spam keywords 
		set<string> spamKeywords; 
		// Helper function to initialize default spam keywords 
		void initializeSpamKeywords(); 
};