#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class LogNode {
public: 
    string action;   
    string timestamp; 
    LogNode* next;

    LogNode(string act) : action(act), next(nullptr) {
        time_t now = time(0);
        char* dt = ctime(&now);
        timestamp = string(dt);
        
        
        if (!timestamp.empty() && timestamp.back() == '\n') {
            timestamp.pop_back();
        } // ctime adds '\n' to end which i really hate it
    }
};

class LogManager {
private:
    LogNode* head;

public:
    LogManager() : head(nullptr) {}

    void addLog(string actionDescription) {
        LogNode* newNode = new LogNode(actionDescription);
        if (!head) {
            head = newNode;
        } else {
            
            newNode->next = head; // LIFO
            head = newNode;
        }
    }

    void displayHistory() const {
        if (!head) {
            cout << "\n[!] No operation history found." << endl;
            return;
        }

        cout << "\n--- OPERATION HISTORY ---" << endl;
        LogNode* temp = head;
        while (temp) {
            cout << "[" << temp->timestamp << "] " << temp->action << endl;
            temp = temp->next;
        }
        cout << "-------------------------" << endl;
    }

    ~LogManager() {
        while (head) {
            LogNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};