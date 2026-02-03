#include "CommonUtilities.h" 
#include <sstream> // For stringstream 
#include <regex> // For email validation 

namespace CommonUtilities { 
	// Tokenizes a string based on delimiters 
	vector<string> tokenize(const string& text, const string& delimiters) { 
		vector<string> tokens; 
		size_t start = 0; 
		size_t end = text.find_first_of(delimiters);
		
		while (end != string::npos) { 
			if (end > start) { 
				// Avoid empty tokens 
				tokens.push_back(text.substr(start, end - start)); 
			} 
			start = end + 1; 
			end = text.find_first_of(delimiters, start); 
		} 
		if (start < text.size()) {
			tokens.push_back(text.substr(start)); 
		} 
		return tokens; 
	} 
	
	// Validates the format of an email address 
	bool isValidEmail(const string& email) {
		
		// Define a simple regex pattern for validating email format 
		const regex pattern(R"((\w+)(\.\w+)*@(\w+)\.(\w+))"); 
		return regex_match(email, pattern); 
	} 
	// Logs a message to the console or a file 
	void log(const string& message, const string& logFile) { 
		// Append the message to the log file 
		ofstream outFile(logFile, ios::app); 
		if (outFile.is_open()) { 
			outFile << message << endl; 
			outFile.close(); 
		} 
		else { 
			cerr << "Error: Could not open log file: " << logFile << endl; 
		} 
		// Print to console as well 
		cout << message << endl; 
	} 
}