#include <bits/stdc++.h>
using namespace std;
struct Node {
    char ch;      
    int freq;     
    Node* left;
    Node* right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

Node* buildTree(const string& text) {
    unordered_map<char,int> freq;
    for (char c : text) {
        if (isalpha(c)) freq[c]++; 
    }
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& p : freq) {
        pq.push(new Node(p.first, p.second));         
    }
    if (pq.size() == 1) {                             
        pq.push(new Node('\0', 0));
    }
    while (pq.size() > 1) {                           
        Node* l = pq.top(); pq.pop();                  
        Node* r = pq.top(); pq.pop();                  
        Node* parent = new Node('\0', l->freq + r->freq);
        parent->left  = l;
        parent->right = r;
        pq.push(parent);                               
    }
    return pq.top();                                   
}
void buildCodes(Node* root,
                const string& prefix,
                unordered_map<char,string>& code) {
    if (!root) return;
    if (root->ch != '\0') {
        code[root->ch] = prefix.empty() ? "0" : prefix; 
    } else {
        buildCodes(root->left,  prefix + '0', code);    
        buildCodes(root->right, prefix + '1', code);    
    }
}
string encode(const string& text,
              const unordered_map<char,string>& code) {
    string out;
    out.reserve(text.size() * 2);
    for (char c : text) {
        if (isalpha(c))
            out += code.at(c);                          
    }
    return out;
}

string decode(const string& bits, Node* root) {
    string out;
    Node* curr = root;
    for (char b : bits) {
        curr = (b == '0') ? curr->left : curr->right;  
        if (!curr) break;
        if (curr->ch != '\0') {                       
            out += curr->ch;
            curr = root;
        }
    }
    return out;
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    // Read message
    cout << "Enter message: "; // input : ie
    string message;
    getline(cin, message);
    Node* root = buildTree(message);                  
    unordered_map<char,string> code;
    buildCodes(root, "", code);                        // O(k) traversal :contentReference[oaicite:20]{index=20}

    // Display codes
    cout << "\nHuffman Codes:\n";
    for (auto& p : code) {
        cout << p.first << ": " << p.second << "\n";
    }

    // Compress
    string bitstring = encode(message, code);          // O(m) :contentReference[oaicite:21]{index=21}
    cout << "\nEncoded bitstring:\n" << bitstring << "\n";

    // Decompress
    string decoded = decode(bitstring, root);          // O(L) :contentReference[oaicite:22]{index=22}
    cout << "\nDecoded message:\n" << decoded << "\n";

    // Cleanup
    freeTree(root);
    return 0;
}
