#include "DataHandle.h"
// Constructor 
DataHandler::DataHandler() : defaultFilePath("emails.txt") { 
	// Optionally initialize other variables if needed 
	} 

// Loads emails from a file 
bool DataHandler::loadEmailsFromFile(const string& filePath) { 
	ifstream inputFile(filePath); 
	if (!inputFile.is_open()) { 
		cerr << "Error: Could not open file " << filePath << endl; return false; 
	} 
	emails.clear(); 
	// Clear any previously loaded emails 
	string line; 
	while (getline(inputFile, line)) { 
	// Skip empty lines 
		if (!line.empty()) { 
		emails.push_back(line); 
		} 
	} 
	inputFile.close(); 
	cout << "Successfully loaded emails from " << filePath << endl; 
	return true; 
} 

// Retrieves the loaded emails 
vector<string> DataHandler::getEmails() const {
	return emails; 
} 

// Saves data to a file 
bool DataHandler::saveDataToFile(const string& filePath) {
	ofstream outputFile(filePath);
	if (!outputFile.is_open()) {
		cerr << "Error: Could not open file " << filePath << endl;
		return false;
	}
	for (const string& email : emails) {
		outputFile << email << endl;
	}
	outputFile.close();
	cout << "Successfully saved emails to " << filePath << endl;
	return true;
}