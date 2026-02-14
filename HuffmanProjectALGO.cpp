#include<iostream>
#include <fstream>
#include <queue>
#include <map>
#include <string>
using namespace std;

class Node {
public:
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f){
        ch=c;
        freq=f;
        left=nullptr;
        right=nullptr;
    }
};

struct cmp {
    bool operator()(Node *a, Node *b) {
         if(a->freq>b->freq) return true; 
         else return false;
        }
};

// Generate Huffman codes
void generateCodes(Node *root, string code, map<char, string> &codes) {
    if (!root) return;
    if (!root->left && !root->right)
        codes[root->ch] = code;
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

// Decode Huffman encoded string
string decodeText(Node *root, const string &encoded) {
    string decoded = "";
    Node *ptr = root;
    for (char bit : encoded) {
        if (bit == '0') ptr = ptr->left;
        else ptr = ptr->right;

        if (!ptr->left && !ptr->right) {
            decoded += ptr->ch;
            ptr = root;
        }
    }
    return decoded;
}

// Write binary string into file
void writeBinFile(const string &bits, const string &Fname) {
    ofstream out(Fname, ios::binary);
    if (!out) {
        cerr << "Failed to open the File!!!\n";
        return;
    }
    unsigned char buff = 0;
    int count = 0;
    for (char bit : bits) {
        buff = buff<<1;
        if (bit == '1') buff= buff|1;
        count++;
        if (count == 8) {
            out.put(buff);
            buff = 0;
            count = 0;
        }
    }
    // Padding if not multiple of 8
    if (count > 0) {
        buff = buff<<(8 - count);
        out.put(buff);
    }
    out.close();
}

// Read binary file back into a bit string
string readBinFile(const string &Fname) {
    ifstream in(Fname, ios::binary);
    if (!in) {
        cerr << "Failed to open the File!\n";
        return "";
    }
    string bits = "";
    unsigned char byte;
    while (in.read((char*)&byte, 1)) {
        for (int i = 7; i >= 0; i--) {
            bits += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    in.close();
    return bits;
}

int main() {
    string text;
    ifstream infile("sampletextFileForFileHandling.txt"); // input file
    if (!infile) {
        cerr << "File Not Found!!!\n";
        return -1;
    }
    char c;
    while(infile.get(c)){
        text+=c;
    }
    infile.close();

    // Count frequency
    map<char, int> freq;
    for (char c : text) freq[c]++;

    // Build Huffman tree
    priority_queue<Node*, vector<Node*>, cmp> pq;
    for (auto p : freq) pq.push(new Node(p.first, p.second));
    while (pq.size() > 1) {
        Node *a = pq.top(); pq.pop();
        Node *b = pq.top(); pq.pop();
        Node *parent = new Node('\0', a->freq + b->freq);
        parent->left = a; parent->right = b;
        pq.push(parent);
    }
    Node *root = pq.top();

    // Generate codes
    map<char, string> codes;
    generateCodes(root, "", codes);

    // Encode text
    string encoded = "";
    for (char c : text) encoded += codes[c];

    // Print codes
    cout << "Codes:\n";
    for (auto p : codes) {
        if (p.first == '\n') cout << "\\n";
        else if (p.first == ' ') cout << "' '";
        else cout << p.first;
        cout << " : " << p.second << "\n";
    }

    // Write compressed bits to file
    writeBinFile(encoded, "encoded.bin");
    cout << "\nCompressed data will be written to encoded.bin\n";

    // Read compressed bits back
    string encodedFromFile = readBinFile("encoded.bin");

    // Decode immediately (note: might include padded extra bits at end)
    string decoded = decodeText(root, encodedFromFile);
    ofstream outfile("decoded.txt");
    outfile << decoded;
    outfile.close();
    cout << "\nDecoded text has been written to decoded.txt\n";
    cout<<"\nThe Huffman Coding will add some more extra characters in the end as a byproduct of padding the last remaining bits-in order to make a full 8 bit byte.";
    return 0;
}

