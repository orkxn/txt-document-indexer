#include <iostream>
#include <string>

using namespace std;

class OccurrenceNode {
public:
    string fileName;
    int lineNumber;
    int count; 
    OccurrenceNode* next;

    OccurrenceNode(string file, int line): fileName(file), lineNumber(line), count(1), next(nullptr) {}
};

class OccurrenceList {
private:
    OccurrenceNode* head;

public:
    OccurrenceList() : head(nullptr) {}
	
	OccurrenceNode* getHead() {
		return head;
	}
	
    void addOrUpdate(string file, int line) {
        if (head == nullptr) {
            head = new OccurrenceNode(file, line);
            return;
        }

        OccurrenceNode* temp = head;
        OccurrenceNode* prev = nullptr;

        while (temp != nullptr) {
            if (temp->fileName == file && temp->lineNumber == line) {
                temp->count++; // if already exists, add 1 to the count
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        prev->next = new OccurrenceNode(file, line);
    }

    void display() const {
        OccurrenceNode* temp = head;
        int totalInAllFiles = 0;

        while (temp != nullptr) {
            cout << "  -> Document: " << temp->fileName 
                 << " | Line: " << temp->lineNumber 
                 << " | Number of this word in this line: " << temp->count << endl;
            totalInAllFiles += temp->count;
            temp = temp->next;
        }
        cout << "\n[!] This word appears a total of " << totalInAllFiles << " times in all the files. " << endl << endl;
    }
    
    void displayOnlyFile() const {
        OccurrenceNode* temp = head;
        int totalInAllFiles = 0;

        while (temp != nullptr) {
            cout << "  -> Document: " << temp->fileName << endl;
            totalInAllFiles += temp->count;
            temp = temp->next;
        }
        cout << "\n[!] This word appears a total of " << totalInAllFiles << " times in all the files. " << endl << endl;
    }

    ~OccurrenceList() {
        OccurrenceNode* current = head;
        while (current != nullptr) {
            OccurrenceNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};