#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        //return 2;
    }

    //std::string fileD = argv[1];
    //std::string fileW = argv[2];

    std::string fileD = "dictionary.txt";
    std::string fileW = "words.txt";

    std::fstream streamDictionary;
    std::fstream streamWords ;

    streamDictionary.open("../" + fileD, std::ios::in);
    streamWords.open("../" + fileW, std::ios::in);

    if ( !streamDictionary.is_open() )
    {
        return 3;
    }

    if ( !streamWords.is_open() )
    {
        return 3;
    }

    std::map<std::string, int> dictionary;
    std::vector<std::vector<std::string>> words;
    std::vector<std::pair<std::vector<std::string>, int>> result;
    std::string line;

    while ( getline(streamDictionary, line) )
    {
        std::string word;
        std::string num;

        std::istringstream streamLine(line);

        if ( !std::getline(streamLine, word, ',') )
        {
            continue;
        }

        if ( !std::getline(streamLine, num, ' ') )
        {
            continue;
        }

        if ( !std::getline(streamLine, num, ' ') )
        {
            continue;
        }

        try
        {
            dictionary.insert( {word, std::stoi(num)} );
        }
        catch (...)
        {}
    }

    while ( getline(streamWords, line) )
    {
        if ( line.empty() )
        {
            continue;
        }

        std::istringstream streamLine(line);
        std::string word;

        words.resize(words.size() + 1);

        while ( getline(streamLine, word, ' ') )
        {
            words[words.size() - 1].push_back(word);
        }
    }

    for (auto&& wordsLine : words)
    {
        std::vector<std::vector<std::pair<std::string, int>>> oneLine;
        oneLine.resize( wordsLine.size() );
        int count = 0;

        for (auto&& randomWord : wordsLine)
        {
            bool flag = true;

            for (auto&& pair : dictionary)
            {
                if (std::is_permutation(randomWord.cbegin(), randomWord.cend(), pair.first.begin()))
                {
                    oneLine[count].push_back({pair.first, pair.second});
                    flag = false;
                }
            }

            if (flag)
            {
                return 5;
            }

            ++count;
        }

        std::vector<int> indexes( oneLine.size() );
        int step = -1;

        while (true)
        {
            bool end = true;
            int sum = 0;

            result.resize(result.size() + 1);

            for (int i = 0; i < oneLine.size(); ++i)
            {
                result[result.size() - 1].first.push_back(oneLine[i][indexes[i]].first);
                sum += oneLine[i][indexes[i]].second;

                if (i == oneLine.size() - 1)
                {
                    result[result.size() - 1].second = sum;
                }
            }

            for (int j = 0; j < indexes.size(); ++j)
            {
                if (indexes[j] < oneLine[j].size() - 1 && j != step)
                {
                    ++indexes[j];
                    step = j;
                    end = false;
                }
            }

            if (end)
            {
                break;
            }
        }
    }

    std::sort(result.begin(), result.end(), [](std::pair<std::vector<std::string>, int> a,
                                               std::pair<std::vector<std::string>, int> b){
        return a.second > b.second;
    });

    for (auto&& pair : result)
    {
        std::vector<std::string> line = pair.first;
        std::sort(line.begin(), line.end());

        while ( std::next_permutation(line.begin(), line.end()) )
        {
            for (auto&& word: line)
            {
                std::cout << word << ' ';
            }

            std::cout << pair.second << std::endl;
        }
    }

    return 0;
}
