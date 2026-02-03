#include <string> 
#include <vector> 
#include <regex> 
#include <iostream> 
#include <fstream> 

using namespace std; 

namespace CommonUtilities { 
	
	// Tokenizes a string based on delimiters 
	vector<string> tokenize(const string& text, const string& delimiters = " "); 
	
	// Validates the format of an email address 
	bool isValidEmail(const string& email); 
	
	// Logs a message to the console or a file 
	void log(const string& message, const string& logFile = "default.log"); 
	
	// Enumeration for email categories 
	enum EmailCategory { 
		SPAM, 
		SUBSCRIPTION, 
		IMPORTANT, 
		UNKNOWN 
	}; 
	
	// Predefined constants 
	const string DEFAULT_LOG_FILE = "inboxhero.log"; 

}

