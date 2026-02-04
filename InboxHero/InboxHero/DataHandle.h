#pragma once
#include <string> 
#include <vector> 
#include <fstream> 
#include <iostream> 

using namespace std; 

class DataHandler { 
public: 
	// Constructor 
	DataHandler(); 
	
	// Method to load emails from a file 
	bool loadEmailsFromFile(const string& filePath); 
	
	// Method to retrieve the loaded emails 
	vector<string> getEmails() const; 
	
	// Method to save data to a file
	bool saveDataToFile(const string& filePath); 

private: 
	// Vector to store loaded emails 
	vector<string> emails;
	// Default file path 
	string defaultFilePath; 
};
