#include <iostream>
using namespace std;

#define SIZE 10

struct Entry {
    int key;
    int value;
    bool occupied;
};

class HashTable {
    Entry table[SIZE];  // internally a fixed list of entries

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            table[i].occupied = false;
        }
    }

    int hash(int key) {
        return key % SIZE;
    }

    void insert(int key, int value) {
        int index = hash(key);
        for (int i = 0; i < SIZE; i++) {
            int idx = (index + i) % SIZE;
            if (!table[idx].occupied || table[idx].key == key) {
                table[idx].key = key;
                table[idx].value = value;
                table[idx].occupied = true;
                cout << "Inserted (" << key << ", " << value << ") at index " << idx << endl;
                return;
            }
        }
        cout << "Table full! Cannot insert.\n";
    }

    void search(int key) {
        int index = hash(key);
        for (int i = 0; i < SIZE; i++) {
            int idx = (index + i) % SIZE;
            if (table[idx].occupied && table[idx].key == key) {
                cout << "Found key " << key << " with value " << table[idx].value << " at index " << idx << endl;
                return;
            }
        }
        cout << "Key " << key << " not found.\n";
    }

    void remove(int key) {
        int index = hash(key);
        for (int i = 0; i < SIZE; i++) {
            int idx = (index + i) % SIZE;
            if (table[idx].occupied && table[idx].key == key) {
                table[idx].occupied = false;
                cout << "Removed key " << key << " from index " << idx << endl;
                return;
            }
        }
        cout << "Key " << key << " not found for deletion.\n";
    }

    void display() {
        for (int i = 0; i < SIZE; i++) {
            if (table[i].occupied) {
                cout << i << ": (" << table[i].key << ", " << table[i].value << ")\n";
            } else {
                cout << i << ": Empty\n";
            }
        }
    }
};

int main() {
    HashTable ht;
    ht.insert(5, 50);
    ht.insert(15, 150);
    ht.insert(25, 250);

    ht.display();
    ht.search(15);
    ht.remove(15);
    ht.search(15);
    ht.display();

    return 0;
}
