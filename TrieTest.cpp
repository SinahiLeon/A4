// Author: <Sinahi Leon>
// Assignment: A4 - Trie
// Description:
//   Loads words from a file, runs queries from another file,
//   prints membership results and all prefix matches,
//   and exercises Rule-of-Three

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Trie.h"

// Helper to strip and return characters from each line
static inline void strip_cr(std::string &s)
{
    if (!s.empty() && s.back() == '\r')
        s.pop_back();
}

int main(int argc, char **argv)
{
    // ---- 1) Argument & file checks ----
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <words.txt> <queries.txt>\n";
        return 1;
    }

    const char *wordsPath = argv[1];
    const char *queriesPath = argv[2];

    std::ifstream wordsFile(wordsPath);
    if (!wordsFile)
    {
        std::cerr << "Error: could not open words file: " << wordsPath << "\n";
        return 1;
    }

    std::ifstream queriesFile(queriesPath);
    if (!queriesFile)
    {
        std::cerr << "Error: could not open queries file: " << queriesPath << "\n";
        return 1;
    }

    // ---- 2) Build the Trie from words.txt file ----
    Trie trie;
    std::string line;

    while (std::getline(wordsFile, line))
    {
        strip_cr(line); // normalize line endings
        if (!line.empty())
        {
            trie.addWord(line);
        }
    }

    // ---- 3) Process queries ----
    while (std::getline(queriesFile, line))
    {
        strip_cr(line); // normalize line endings

        // Print required header line
        std::cout << "Checking text: " << line << "\n";

        // Check membership
        bool found = trie.isWord(line);
        std::cout << (found ? "Word found\n" : "Word not found\n");

        // List all words starting with the query as prefix
        std::vector<std::string> matches = trie.allWordsStartingWithPrefix(line);

        // Print matches in one line, space-separated, ending with newline
        for (std::size_t i = 0; i < matches.size(); ++i)
        {
            if (i)
                std::cout << ' ';
            std::cout << matches[i];
        }
        std::cout << "\n";
    }

    // ---- 4) Rule-of-Three portion ----
    {
        Trie t1;
        t1.addWord("trap");
        t1.addWord("transgender");
        t1.addWord("transcontinental");

        // Copy constructor
        Trie t2 = t1;

        // Assignment operator
        Trie t3;
        t3 = t1;

        // Modify only the original trie
        t1.addWord("transparency");

        // Now test independence
        std::cout << "[RuleOfThree] t1 has 'transparency'? "
                  << (t1.isWord("transparency") ? "yes" : "no") << "\n";

        std::cout << "[RuleOfThree] t2 has 'transparency'? "
                  << (t2.isWord("transparency") ? "yes" : "no") << "\n";

        std::cout << "[RuleOfThree] t3 has 'transparency'? "
                  << (t3.isWord("transparency") ? "yes" : "no") << "\n";

    }

    return 0;
}
