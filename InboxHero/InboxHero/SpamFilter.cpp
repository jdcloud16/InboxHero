#include "SpamFilter.h"
#include <sstream> // For stringstream 
#include <algorithm> // For transform 
#include <cctype> // For ::tolower 

// Constructor 
SpamFilter::SpamFilter() { 
	initializeSpamKeywords(); 
} 

// Determines if an email is spam 
bool SpamFilter::isSpam(const string& emailContent, const string& sender) { 
	// Check if the sender is blocked 
	if (blockedSenders.find(sender) != blockedSenders.end()) { 
		return true; 
	} 
	
	// Tokenize email content 
	vector<string> tokens; 
	stringstream ss(emailContent); // Ensure stringstream is properly included 
	string word; 
	while (ss >> word) { // Extract words from the email content 
		// Convert word to lowercase for uniformity 
		transform(word.begin(), word.end(), word.begin(), ::tolower); 
		
		// Ensure <algorithm> and <cctype> are included 
		tokens.push_back(word); 
	} 
	
	// Check for spam keywords 
	for (const string& token : tokens) { 
		if (spamKeywords.find(token) != spamKeywords.end()) {
			return true; 
		} 
	} 
	return false; // Not spam 
} 

// Block a sender 
void SpamFilter::blockSender(const string& sender) { 
	blockedSenders.insert(sender); 
	cout << "Blocked sender: " << sender << endl; 
} 

// Unblock a sender 
void SpamFilter::unblockSender(const string& sender) {
	if (blockedSenders.erase(sender)) { 
		cout << "Unblocked sender: " << sender << endl; 
	} else { 
		cout << "Sender " << sender << " not found in blocked list." << endl; 
	} 
}

// List all blocked senders
void SpamFilter::listBlockedSenders() const { 
	if (blockedSenders.empty()) { 
		cout << "No blocked senders." << endl; 
		return; 
	} 
	cout << "Blocked Senders:" << endl; 
	for (const string& sender : blockedSenders) {
		cout << "- " << sender << endl; 
	} 
} 

// Helper: Initialize default spam keywords 
void SpamFilter::initializeSpamKeywords() { 
	spamKeywords = { "free", "win", "money", "urgent", "prize", 
		"click", "offer", "buy now", "limited time", "congratulations" }; 
}