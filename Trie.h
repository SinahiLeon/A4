// Author: <Sinahi Leon>
// Assignment: A4 - Trie
// Description:
//   Declaration of Trie class, class stores all lowercase letters using a tree structure. 
//   First you will see the Rule Of Three methdos implemented, as well as methods to add 
//   words, check the validity of them, and list all words with a specified prefix.

#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <vector>
#include <cctype> // std::islower checks for lowercase letters, this #include is required.

class Trie
{
public:
    Trie();                      // constructor
    ~Trie();                     // destructor
    Trie(const Trie &other);     // copy constructor
    Trie &operator=(Trie other); // assign operator

    void addWord(const std::string &wordToAdd);
    bool isWord(const std::string &wordToCheck);
    std::vector<std::string> allWordsStartingWithPrefix(const std::string &prefix);

private:
    struct Node
    {
        Node *letters[26];
        bool wordFlag;

        Node();
        ~Node();
        Node(const Node &other);
    };

    Node *root;
};

#endif