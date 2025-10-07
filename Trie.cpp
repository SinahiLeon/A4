// Author: <Sinahi Leon>
// Assignment: A4 - Trie
// Description:
//   Full implementation of Trie class. Here you will find all the logic for addings a word,
//   checking if a string is stored, and collecting all words based on a prefix. We are using 
//   an array of pointers in each node.

#include <string>
#include <vector>
#include <cctype>  // std::islower checks for lowercase letters, this #include is required.
#include <utility> // required for std::swap
#include "Trie.h"

// Construct a node, where each has a Node* array and a wordFlag boolean variable
Trie::Node::Node() : wordFlag(false)
{
    for (int i = 0; i < 26; ++i)
        letters[i] = nullptr;
}

Trie::Node::~Node()
{
    for (int i = 0; i < 26; ++i)
        delete letters[i];
}

Trie::Node::Node(const Trie::Node &other) : wordFlag(other.wordFlag)
{
    for (int i = 0; i < 26; ++i)
    {
        letters[i] = other.letters[i] ? new Node(*other.letters[i]) : nullptr;
    }
}

Trie::Trie() : root(new Node()) {}

Trie::~Trie()
{
    delete root;
}

Trie::Trie(const Trie &other) : root(new Node(*other.root))
{
}

Trie &Trie::operator=(Trie other)
{
    std::swap(root, other.root);
    return *this;
}

void Trie::addWord(const std::string &wordToAdd)
{
    if (wordToAdd.empty())
        return;

    Node *thisRoot = root;
    for (char c : wordToAdd)
    {
        if (!std::islower(c))
            return;

        int indexOfChar = c - 'a'; // For example : 'b' - 'a' = 1 → letters[1]

        if (!thisRoot->letters[indexOfChar]) // if null, create a child
            thisRoot->letters[indexOfChar] = new Node();

        thisRoot = thisRoot->letters[indexOfChar]; // move to child
    }
    thisRoot->wordFlag = true; // <-- assignment (fixed)
}

bool Trie::isWord(const std::string &wordToCheck)
{
    if (wordToCheck.empty())
        return false; // empty string is not a word

    const Node *thisRoot = root;
    for (char c : wordToCheck)
    {
        if (!std::islower(c))
            return false; // invalid char → immediate false

        int index = c - 'a';
        if (!thisRoot->letters[index])
            return false; // path breaks → not found

        thisRoot = thisRoot->letters[index];
    }
    return thisRoot->wordFlag;
}

std::vector<std::string> Trie::allWordsStartingWithPrefix(const std::string &prefix)
{
    std::vector<std::string> out;

    // Go through the trie to reach the node that matches the the prefix.
    const Node *start = root;
    for (char c : prefix)
    {
        // If any character is not lowercase, return empty
        if (!std::islower(c))
            return out;

        int index = c - 'a';

        // If the path for this char doesn't exist, no words start with this prefix
        if (!start->letters[index])
            return out;

        // Move down one level to the child node.
        start = start->letters[index];
    }

    // Collect all words that keep going after the prefix has completed

    // Use a stack - each entry holds a pointer to a node, the string built so far to that node
    std::vector<std::pair<const Node *, std::string>> stack;
    stack.emplace_back(start, prefix);

    while (!stack.empty())
    {
        // Get the top element from the stack.
        auto currentFrame = stack.back();
        stack.pop_back();

        const Node *currentNode = currentFrame.first;
        std::string currentWord = std::move(currentFrame.second);

        // If this node marks the end of a word, push back
        if (currentNode->wordFlag)
            out.push_back(currentWord);

        // Now push all children of this node onto the stack.
        for (int childIndex = 25; childIndex >= 0; --childIndex)
        {
            if (currentNode->letters[childIndex])
            {
                // Extend the current word with the child character.
                std::string nextWord = currentWord;
                nextWord.push_back(static_cast<char>('a' + childIndex));

                // Add the child node and the extended word to the stack.
                stack.emplace_back(currentNode->letters[childIndex], std::move(nextWord));
            }
        }
    }

    // Return the complete vector of all the words.
    return out;
}