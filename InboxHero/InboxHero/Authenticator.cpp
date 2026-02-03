#include "Authenticator.h"
#include <functional> // For std::hash 
#include <random> // For random word generation 

// Constructor 
Authenticator::Authenticator() { 
	
	// Initialize user data structures if needed 
} 

// Creates a new account 
bool Authenticator::createAccount(const string& username, const string& password) { 
	if (userCredentials.find(username) != userCredentials.end()) { 
		cout << "Error: Username already exists!" << endl; return false; 
	} 
	
	// Hash the password and store it 
	userCredentials[username] = hashPassword(password); 
	cout << "Account created successfully for username: " << username << endl; 
	return true; 

} 

// Logs in a user 
bool Authenticator::login(const string& username, const string& password) { 
	auto it = userCredentials.find(username); 
	if (it == userCredentials.end()) { 
		cout << "Error: Username not found!" << endl; 
		return false; 
	} 
	
// Verify password hash 
if (it->second == hashPassword(password)) { 
	cout << "Login successful!" << endl; return true; 
}	
else { 
	cout << "Error: Incorrect password!" << endl; return false; 
	} 
} 
// Recovers an account using the 20-word recovery key 
bool Authenticator::recoverAccount(const string& username, const vector<string>& recoveryKey) { 
	auto it = recoveryKeys.find(username); // Match keys for the provided username 
	if (it != recoveryKeys.end() && find(it->second.begin(), 
		it->second.end(), recoveryKey[0]) != it->second.end()) { 
		return true; // Key matches 
	} 
	return false; // Invalid key 
} 

// Generates and displays a 20-word recovery key 
void Authenticator::generateRecoveryKey(const string& username) { 
	if (userCredentials.find(username) == userCredentials.end()) { 
		cout << "Error: Username not found!" << endl; 
		return; 
	} 
	vector<string> recoveryKey = generateRandomWords(20); 
	recoveryKeys[username] = recoveryKey; 
	cout << "Your 20-word recovery key (write this down!):" << endl; 
	for (const string& word : recoveryKey) { 
		cout << word << " "; 
	} 
	cout << endl; 
} 
// Enables two-factor authentication 
void Authenticator::enable2FA(const string& username) { 
	if (userCredentials.find(username) == userCredentials.end()) { 
		cout << "Error: Username not found!" << endl; 
		return; 
	} 
	twoFactorEnabledUsers.insert(username); 
	cout << "Two-factor authentication enabled for username: " << username << endl; 
} 

// Hashes a password for secure storage 
string Authenticator::hashPassword(const string& password) { 
	hash<string> hasher; return to_string(hasher(password)); 
} 

// Generates a list of random words 
vector<string> Authenticator::generateRandomWords(int wordCount) { 
	vector<string> wordPool = { "orange", "radio", "pineapple", "bridge", "cloud", 
		"river", "mountain", "train", "rocket", "star", "forest", "planet", 
		"computer", "window", "ocean", "castle", "key", "paper", "lamp", "shield" 
	}; 
	vector<string> recoveryKey; random_device rd; // Random seed 
	mt19937 gen(rd()); // Random number generator 
	uniform_int_distribution<> dist(0, wordPool.size() - 1); 
	for (int i = 0; i < wordCount; ++i) { 
		recoveryKey.push_back(wordPool[dist(gen)]); 
	} 
	return recoveryKey;
}