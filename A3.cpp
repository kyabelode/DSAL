/*skiplist */
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int value;
    vector<Node*> next;
    Node(int val, int level) : value(val), next(level + 1, nullptr) {}
};

class SkipList {
    int maxLevel;
    int currentLevel;
    Node* header;
    
    int randomLevel() {
        int level = 0;
        while (rand() % 2 && level < maxLevel)
            level++;
        return level;
    }

public:
    SkipList(int maxLvl) : maxLevel(maxLvl), currentLevel(0) {
        header = new Node(INT_MIN, maxLevel);
    }

    ~SkipList() {
        Node* node = header->next[0];
        while (node) {
            Node* temp = node;
            node = node->next[0];
            delete temp;
        }
        delete header;
    }

    void insert(int value) {
        vector<Node*> update(maxLevel + 1, header);
        Node* current = header;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->next[i] && current->next[i]->value < value)
                current = current->next[i];
            update[i] = current;
        }

        int newLevel = randomLevel();
        if (newLevel > currentLevel) {
            for (int i = currentLevel + 1; i <= newLevel; i++)
                update[i] = header;
            currentLevel = newLevel;
        }

        Node* newNode = new Node(value, newLevel);
        for (int i = 0; i <= newLevel; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }

    int findClosest(int target) {
        Node* current = header;
        Node* prev = nullptr;
        
        for (int i = currentLevel; i >= 0; i--) {
            while (current->next[i] && current->next[i]->value <= target) {
                current = current->next[i];
                prev = current;
            }
        }

        Node* next = current->next[0];
        if (!prev && !next) return INT_MIN;  // Empty list
        if (!prev) return next->value;      // Target smaller than all elements
        if (!next) return prev->value;      // Target larger than all elements

        int diffPrev = abs(prev->value - target);
        int diffNext = abs(next->value - target);
        
        if (diffPrev < diffNext) return prev->value;
        if (diffNext < diffPrev) return next->value;
        return min(prev->value, next->value);
    }
};

int main() {
    srand(time(NULL));
    vector<int> elements = {1, 3, 5, 7};
    int target = 6;

    SkipList skipList(16);
    for (int num : elements) {
        skipList.insert(num);
    }

    int closest = skipList.findClosest(target);
    cout << "Closest element to " << target << " is: " << closest << endl;

    return 0;
}
