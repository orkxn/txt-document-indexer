#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include "LinkedList.h"

using namespace std;

class SearchEngine {
private:
    unordered_map<string, OccurrenceList*> invertedIndex;

    string cleanWord(string word) {
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        return word;
    }

public:
    void indexFile(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) return;

        string line;
        int lineNum = 1;
        while (getline(file, line)) {
            stringstream ss(line);
            string word;
            while (ss >> word) {
                word = cleanWord(word);
                if (!word.empty()) {
                    if (invertedIndex.find(word) == invertedIndex.end()) { // checks if the word linkedlist exists
                        invertedIndex[word] = new OccurrenceList();
                    }
                    invertedIndex[word]->addOrUpdate(fileName, lineNum);
                }
            }
            lineNum++;
        }
        file.close();
    }

    void search(string word) {
        word = cleanWord(word);
        if (invertedIndex.find(word) == invertedIndex.end()) {
            cout << "'" << word << "' not found." << endl;
            return;
        }
        cout << "\n--- '" << word << "' Analysis ---" << endl;
        invertedIndex[word]->display();
    }
    
    void searchOnlyFile(string word) {
        word = cleanWord(word);
        if (invertedIndex.find(word) == invertedIndex.end()) {
            cout << "'" << word << "' not found." << endl;
            return;
        }
        cout << "\n--- '" << word << "' Analysis ---" << endl;
        invertedIndex[word]->displayOnlyFile();
    }
    
    void displayTopN(int n=5) {
	    if (invertedIndex.empty()) return;
	
	    vector<pair<string, int>> freqList;
	    for (auto const& [word, list] : invertedIndex) {
	        int total = 0;
	        for (auto* temp = list->getHead(); temp; temp = temp->next) 
	            total += temp->count;
	        freqList.push_back({word, total}); // adds double data format ex. {the, 20}
	    }
	
	    sort(freqList.begin(), freqList.end(), [](auto& a, auto& b) {
	        return a.second > b.second;
	    });
	
	    int limit = min((int)freqList.size(), n);
	    int maxVal = freqList[0].second;
	
	    for (int i = 0; i < limit; ++i) {
	        int barWidth = (maxVal > 0) ? (freqList[i].second * 20 / maxVal) : 0;
	
	        cout << i + 1 << ". " << left << setw(12) << freqList[i].first << " [";
	        for (int j = 0; j < 20; ++j) cout << (j < barWidth ? "*" : " "); // i have no clue why it didn't allow full block char, instead i used *
	        cout << "] (" << freqList[i].second << "/" << maxVal << ")" << endl;
	    }
	}
	
	void displayTopNFromBottom(int n = 5) {
	    if (invertedIndex.empty()) return;
	
	    vector<pair<string, int>> freqList;
	    int absoluteMax = 0;
	
	    for (auto const& [word, list] : invertedIndex) {
	        int total = 0;
	        for (auto* temp = list->getHead(); temp; temp = temp->next) 
	            total += temp->count;
	        
	        freqList.push_back({word, total});
	        if (total > absoluteMax) absoluteMax = total; 
	    }
	
	    sort(freqList.begin(), freqList.end(), [](auto& a, auto& b) {
	        return a.second < b.second;
	    });
	
	    int limit = min((int)freqList.size(), n);
	
	    cout << "\n--- Least Frequent " << limit << " Words ---" << endl;
	
	    for (int i = 0; i < limit; ++i) {
	        int barWidth = (absoluteMax > 0) ? (freqList[i].second * 20 / absoluteMax) : 0;
	
	        cout << i + 1 << ". " << left << setw(12) << freqList[i].first << " [";
	        for (int j = 0; j < 20; ++j) cout << (j < barWidth ? "*" : " ");
	        cout << "] (" << freqList[i].second << "/" << absoluteMax << ")" << endl;
	    }
	}

    ~SearchEngine() {
        for (auto& pair : invertedIndex) delete pair.second;
    }
};