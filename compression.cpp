/*
Name: Sam Sutton
Date: 12/14/2022
Purpose: Final Project
*/
#include "compare.h"
#include "node.h"
#include <bitset>
#include <iomanip>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <sstream>

using FrequencyTable = std::unordered_map<char, int>;
using HuffmanCodes = std::unordered_map<char, std::string>;

FrequencyTable build_frequency_table(const std::string& text);
void print_queue(std::priority_queue<Node*, std::vector<Node*>, Compare> queue);
Node* make_tree(std::priority_queue<Node*, std::vector<Node*>, Compare> queue);
void assign_codes(Node*& n, std::string code, HuffmanCodes& codes);
void print_codes(Node*& n, std::string code);
void print_tree(Node* n, int level, std::ostream& os);
std::ostream& operator<<(std::ostream& os, Node* tree);
std::string binary(const std::string& text);
void decode(Node*& tree, Node* root, std::string& encoded,
            std::string& decoded);

int main() {
    try {
        std::cout << "Enter text:\n";
        std::string input;
        getline(std::cin, input);

        FrequencyTable table = build_frequency_table(input);
        std::priority_queue<Node*, std::vector<Node*>, Compare> queue;
        std::cout << "\nFrequency table:\n";
        for (auto [c, i] : table) {
            std::cout << c << ": " << i << "\n";
            queue.push(new Node{std::string{c}, i});
        }
        std::cout << "\nPriority queue:\n";
        print_queue(queue);

        Node* tree = make_tree(queue);
        std::cout << "\nHuffman encoding tree:\n" << tree << "\n";

        std::string code;
        HuffmanCodes codes;
        assign_codes(tree, code, codes);
        std::cout << "Huffman codes:\n";
        print_codes(tree, code);
        
        std::string uncompressed = binary(input);
        double uncompressed_size = uncompressed.size();
        std::cout << "\nUncompressed bit sequence:\n" << uncompressed << "\n\n";

        std::string encoded_input;
        for (char c : input) {
            encoded_input += codes[c];
        }
        double encoded_size = encoded_input.size();
        std::cout << "Encoded:\n" << encoded_input << "\n\n";

        std::string decoded;
        decode(tree, tree, encoded_input, decoded);
        std::cout << "Decoded:\n" << decoded << "\n\n";

        double compression = (encoded_size / uncompressed_size);
        int percent = compression * 100;
        std::cout << "Compressed to " << percent << "% of original size\n";
    }
    catch (std::runtime_error& error) {
        std::cout << "Error: " << error.what() << "\n";
    }
}

FrequencyTable build_frequency_table(const std::string& text) {
    FrequencyTable table;
    for (char c : text) {
        table[c] += 1;
    }
    return table;
}

void print_queue(
    std::priority_queue<Node*, std::vector<Node*>, Compare> queue) {
    while (queue.size() != 1) {
        Node* node = queue.top();
        std::cout << "(" << node->letters << "," << node->frequency << ")"
                  << " -> ";
        queue.pop();
    }
    Node* node = queue.top();
    std::cout << "(" << node->letters << "," << node->frequency << ")"
              << "\n";
}

Node* make_tree(std::priority_queue<Node*, std::vector<Node*>, Compare> queue) {
    while (queue.size() != 1) {
        Node* right = queue.top();
        queue.pop();
        Node* left = queue.top();
        queue.pop();
        // new Node parent{(right->letters + left->letters),
        //              (right->frequency + left->frequency), left, right};
        queue.push(new Node{(left->letters + right->letters),
                            (right->frequency + left->frequency), left, right});
        print_queue(queue);
    }
    return queue.top();
}

void assign_codes(Node*& n, std::string code, HuffmanCodes& codes) {
    if (n->left == nullptr) {
        char c = n->letters[0];
        codes[c] = code;
        return;
    }
    assign_codes(n->left, code + "0", codes);
    assign_codes(n->right, code + "1", codes);
}

void print_codes(Node*& n, std::string code) {
    if (n->left == nullptr) {
        std::cout << n->letters[0] << ": " << code << "\n";
        return;
    }
    print_codes(n->left, code + "0");
    print_codes(n->right, code + "1");
}

void print_tree(Node* n, int level, std::ostream& os) {
    if (n) {
        if (n->right) {
            print_tree(n->right, level + 4, os);
            os << std::setw(level + 2) << "/\n";
        }
        os << std::setw(level - 1) << "(" << n->letters << "," << n->frequency
           << ")" << '\n';
        if (n->left) {
            os << std::setw(level + 2) << "\\\n";
            print_tree(n->left, level + 4, os);
        }
    }
}

std::ostream& operator<<(std::ostream& os, Node* tree) {
    print_tree(tree, 1, os);
    return os;
}

std::string binary(const std::string& text) {
    std::stringstream ss;
    for (char c : text) {
        ss << std::bitset<8>(c);
    }
    return ss.str();
}

void decode(Node*& tree, Node* root, std::string& encoded,
            std::string& decoded) {
    if (tree->left == nullptr && tree->right == nullptr) {
        decoded += tree->letters;
        decode(root, root, encoded, decoded);
    }
    else if (encoded[0] == '0') {
        encoded.erase(0, 1);  // erase first character
        decode(tree->left, root, encoded, decoded);
    }
    else if (encoded[0] == '1') {
        encoded.erase(0, 1);  // erase first character
        decode(tree->right, root, encoded, decoded);
    }
}