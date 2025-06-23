#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch)) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    // Search for a full word
    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch)) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfWord;
    }

    // Check if any word in the Trie starts with the given prefix
    bool startsWith(const string& prefix) const {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children.count(c))
                return false;
            node = node->children[c];
        }
        return true;
    }
};

