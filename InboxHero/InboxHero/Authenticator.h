#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <random>

using namespace std;

class Authenticator
{
public:
	// Constructor
	Authenticator(); 
	
	// Method to create a new account 
	bool createAccount(const string& username, const string& password); 
	
	// Method to log in a user 
	bool login(const string& username, const string& password); 
	
	// Method to recover an account using the 20-word recovery key 
	bool recoverAccount(const string& username, const vector<string>& recoveryKey);
	
	// Method to generate and display a 20-word recovery key 
	void generateRecoveryKey(const string& username); 
	
	// Method to enable two-factor authentication 
	void enable2FA(const string& username); 

private: 
		
	// Map of usernames to hashed passwords 
	map<string, string> userCredentials; 
	
	// Map of usernames to their 20-word recovery keys 
	map<string, vector<string>> recoveryKeys; 
	
	// Set of users with 2FA enabled 
	set<string> twoFactorEnabledUsers; 
	
	// Helper function to hash passwords 
	string hashPassword(const string& password); 
	
	// Helper function to generate random words 
	vector<string> generateRandomWords(int wordCount);
};

