#include <iostream>
using namespace std;

struct Node {
    string name;
    int priority;
    Node* next;

    Node(string n, int p) {
        name = n;
        priority = p;
        next = nullptr;
    }
};

class HospitalQueue {
private:
    Node* front;

public:
    HospitalQueue() {
        front = nullptr;
    }

    void addPatient(string name, int priority) {
        Node* newNode = new Node(name, priority);

        // Case: empty list or new node has higher priority
        if (front == nullptr || priority < front->priority) {
            newNode->next = front;
            front = newNode;
        } else {
            Node* current = front;

            // Traverse until the correct position based on priority
            while (current->next != nullptr && current->next->priority <= priority) {
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;
        }

        cout << "Patient added: " << name << " (Priority " << priority << ")\n";
    }

    void servePatient() {
        if (front == nullptr) {
            cout << "No patients in queue.\n";
            return;
        }

        Node* temp = front;
        cout << "Serving patient: " << temp->name << " (Priority " << temp->priority << ")\n";
        front = front->next;
        delete temp;
    }

    void displayQueue() {
        if (front == nullptr) {
            cout << "No patients in queue.\n";
            return;
        }

        cout << "\n--- Patient Queue ---\n";
        Node* current = front;
        while (current != nullptr) {
            cout << current->name << " (Priority " << current->priority << ")\n";
            current = current->next;
        }
    }

    ~HospitalQueue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main() {
    HospitalQueue hq;

    hq.addPatient("John", 3);      // General
    hq.addPatient("Alice", 1);     // Serious
    hq.addPatient("Bob", 2);       // Non-serious
    hq.addPatient("Zara", 1);      // Serious

    hq.displayQueue();

    hq.servePatient();
    hq.servePatient();

    hq.displayQueue();

    return 0;
}
