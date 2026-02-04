#pragma once
#include <string> 
#include <map> 
#include <iostream> // For displaying lists or messages 

using namespace std;

class SubscriptionManager { 
public: 
	// Constructor 
	SubscriptionManager(); 
	
	// Method to add a subscription 
	void addSubscription(const string& email, const string& serviceName); 
	
	// Method to list all subscriptions 
	void listSubscriptions() const; 
	
	// Method to unsubscribe from a specific service 
	bool unsubscribe(const string& serviceName); 
	
	// Method to bulk unsubscribe from all services 
	void bulkUnsubscribe(); 

private:
	// Map of service names to corresponding email addresses 
	map<string, string> subscriptions; 

};
