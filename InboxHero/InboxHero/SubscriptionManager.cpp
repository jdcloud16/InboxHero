#include "SubscriptionManager.h"

// Constructor 
SubscriptionManager::SubscriptionManager() { 
	// Initialize subscriptions map if necessary 
} 

// Add a subscription 
void SubscriptionManager::addSubscription(const string& email, 
										const string& serviceName) 
{
	if (subscriptions.find(serviceName) == subscriptions.end()) 
	{ 
		subscriptions[serviceName] = email; 
		cout << "Added subscription: " << serviceName << " (" << email << ")" << endl; 
	} 
	else {
		cout << "Subscription for " << serviceName << " already exists!" << endl; 
	} 
} 


// List all subscriptions 
void SubscriptionManager::listSubscriptions() const 
{ 
	if (subscriptions.empty()) 
	{ 
		cout << "No subscriptions found." << endl; return; 
	} 
	cout << "Current Subscriptions:" << endl; 
	for (const auto& pair : subscriptions) 
	{ 
		cout << "- " << pair.first << " (" << pair.second << ")" << endl; 
	} 
} 

// Unsubscribe from a specific service 
bool SubscriptionManager::unsubscribe(const string& serviceName) 
{
	auto it = subscriptions.find(serviceName); 
	if (it != subscriptions.end()) 
	{ 
		subscriptions.erase(it); 
		cout << "Unsubscribed from " << serviceName << "." << endl; 
		return true; 
	} 
	else 
	{ 
		cout << "Subscription for " << serviceName << " not found." << endl; 
		return false; 
	} 
} 


// Bulk unsubscribe from all services 
void SubscriptionManager::bulkUnsubscribe() 
{ 
	if (subscriptions.empty()) 
	{ 
		cout << "No subscriptions to unsubscribe from." << endl; 
		return; 
	} 
	subscriptions.clear();
	cout << "Successfully unsubscribed from all services." << endl; 
}