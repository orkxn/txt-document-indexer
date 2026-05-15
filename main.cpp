#include <iostream>
#include <chrono>
#include "SearchEngine.h"
#include "LogManager.h"

using namespace std;

int main() {
    SearchEngine engine;
	LogManager logger;

	string folderPath = "AllDocs\\";
	
    int documentCount = 0;
    int i = 1;

    cout << "--- Documents are being indexed ---" << endl;

    auto startTime = chrono::high_resolution_clock::now();

    while (true) {
        string fullPath = folderPath + to_string(i) + ".txt";
        
        ifstream fileCheck(fullPath);
        if (!fileCheck.is_open()) {
            break;
        }
        fileCheck.close();

        cout << "[+] " << fullPath << " reading..." << endl;
        engine.indexFile(fullPath);
        documentCount++;
        i++;
    }

    if (documentCount == 0) {
        cout << "Error: There is no .txt file found. Please make sure if any .txt file exists." << endl;
        return 1;
    }

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;
    cout << "\n" << documentCount << " files scanned and all words are indexed to the list." << endl;
    cout << "Indexing completed in " << elapsed.count() << " seconds." << endl << endl;

    string query;
    int cont;
    
    while(true) {
		cout << "Menu Options" << endl;
		cout << "----------------------------------------------------------------------" << endl;
		cout << "Simple Document Retrieval System" << endl << endl;
		cout << "1. Enter a Single Keyword to List The Document(s) (File Names)" << endl;
		cout << "2. Display the Top N Words that Appeared Most Frequently" << endl;
		cout << "3. Display the Top N Words that Appeared Least Frequently" << endl;
		cout << "4. Display Word Frequency With Line Numbers" << endl;
		cout << "5. Display Operation History" << endl;
		cout << "6. Exit" << endl;
		cout << "----------------------------------------------------------------------" << endl;
		cout << "Selection(1, 2, 3, 4, 5, 6): ";
		cin  >> cont;
		if (cont == 1) {
			cout << "Enter the word for scan: ";
       		cin >> query;
       		
       		engine.searchOnlyFile(query);
			logger.addLog("1. Instruction => Searched for keyword only for files: " + query);
		} else if (cont == 2) {
			engine.displayTopN();
			logger.addLog("2. Instructions => Displayed Top 5 frequent words.");
		} else if (cont== 3) {
			engine.displayTopNFromBottom();
			logger.addLog("3. Instructions => Displayed Least 5 frequent words.");
		}
		else if (cont == 4) {
			cout << "Enter the word for scan: ";
       		cin >> query;
       		
       		engine.search(query);
			logger.addLog("1. Instruction => Searched for keyword: " + query);
		} else if (cont == 5) {
			logger.displayHistory();
		} 
		else if (cont == 6) {
			cout << "\nExiting program, freeing the memory...";
			return 0;
		}
		
	}
    
    return 0;
}