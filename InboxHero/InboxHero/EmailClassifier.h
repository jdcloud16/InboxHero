#pragma once
#include <string> 
#include <vector> 
#include <map> 
#include <set> 
#include <iostream> 

// Optional, for debug purposes if needed 

using namespace std; 

class EmailClassifier { 
public: 
	// Constructor 
	EmailClassifier(); 
	
	// Method to train the classifier with labeled data 
	void train(const vector<string>& data, const vector<string>& labels); 
	
	// Method to predict the class of a new email 
	string predict(const string& email); 
private: 
		// Tracks the number of emails per class (e.g., spam, important) 
		map<string, int> classCounts; 
		
		// Tracks the word counts for each class 
		map<string, map<string, int>> wordCounts; 
		
		// Total number of emails in the training data 
		int totalEmails; 
		
		// Unique words across all emails 
		set<string> vocabulary; 
		
		// Helper function to tokenize email content into words 
		vector<string> tokenize(const string& content); 
};
