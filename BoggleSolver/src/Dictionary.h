#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>
#include <algorithm>

#include "lunchbox/lunchbox.h"

namespace Dict
{

    std::vector<std::string> words;
    int minWordSize;

    void loadWords(std::string filePath)
    {
        minWordSize = lbConfig::file("data/config.txt").get<int>("min_word_size");

        words = lbFile::getFileContents(filePath);

        std::sort(words.begin(), words.end());

        for (int i = 0; i < (int)words.size(); i++)
        {
            lbString::trim(words[i]);
            lbString::toUpper(words[i]);
        }

        INFO("Loaded " << words.size() << " words");

    }

    bool isValid(std::string query)
    {
        lbString::trim(query);
        lbString::toUpper(query);

        if ((int)query.size() < minWordSize)
        {
            return false;
        }

        // Search loaded words.
        return std::binary_search(words.begin(), words.end(), query);

    }

    int longestWord()
    {
        // Work out the length of the longest word
        int max = -1;
        for (int i = 0; i < (int)words.size(); i++)
        {
            max = (int)words[i].size() > max ? (int)words[i].size() : max;
        }

        return max;
    }

}

#endif // DICTIONARY_H
