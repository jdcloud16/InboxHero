#include "EmailClassifier.h"
#include <sstream>
#include <algorithm>
#include <cctype>

// Constructor
EmailClassifier::EmailClassifier() {
    totalEmails = 0;
}

// Train the classifier with labeled data
void EmailClassifier::train(const vector<string>& data, const vector<string>& labels) {
    if (data.size() != labels.size()) {
        cout << "Error: Training data and labels size mismatch." << endl;
        return;
    }

    for (size_t i = 0; i < data.size(); i++) {
        string label = labels[i];
        classCounts[label]++;
        totalEmails++;

        vector<string> words = tokenize(data[i]);

        for (const string& word : words) {
            wordCounts[label][word]++;
            vocabulary.insert(word);
        }
    }
}

// Predict the class of a new email
string EmailClassifier::predict(const string& email) {
    if (totalEmails == 0) {
        return "UNKNOWN";
    }

    vector<string> words = tokenize(email);
    double bestScore = -1e9;
    string bestClass = "UNKNOWN";

    for (const auto& classPair : classCounts) {
        const string& label = classPair.first;
        int classCount = classPair.second;

        // Start with log prior probability
        double score = log(static_cast<double>(classCount) / totalEmails);

        for (const string& word : words) {
            int wordFrequency = 0;

            if (wordCounts[label].count(word)) {
                wordFrequency = wordCounts[label][word];
            }

            // Laplace smoothing
            double probability =
                static_cast<double>(wordFrequency + 1) /
                (classCount + vocabulary.size());

            score += log(probability);
        }

        if (score > bestScore) {
            bestScore = score;
            bestClass = label;
        }
    }

    return bestClass;
}

// Helper function to tokenize email content into words
vector<string> EmailClassifier::tokenize(const string& content) {
    vector<string> tokens;
    string word;
    stringstream ss(content);

    while (ss >> word) {
        // Convert to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Remove punctuation
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

        if (!word.empty()) {
            tokens.push_back(word);
        }
    }

    return tokens;
}
