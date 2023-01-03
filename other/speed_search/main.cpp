#include <iostream>
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

void getLastLine(std::fstream& stream, std::string& line)
{
    stream.seekg(-2, std::ios_base::end);

    while(stream.peek() != '\n')
    {
        if (stream.tellg() < 0)
        {
            throw std::runtime_error("error searching for the last line in the file");
        }

        stream.seekg(-1, std::ios_base::cur);
    }

    stream.seekg(1, std::ios_base::cur);
    std::getline(stream, line);
}

std::filesystem::path binarySearchFile(const std::vector<std::filesystem::path>& files, int start, int end,
                                       const std::string& hash)
{
    if (start > end)
    {
        throw std::runtime_error("start > end");
    }

    int mid = (start + end) / 2;

    std::fstream stream;
    std::string line;
    std::string firstHash;
    std::string lastHash;

    stream.open( files[mid] );

    if ( !stream.is_open() )
    {
        throw std::runtime_error("file not exist");
    }

    std::getline(stream, line);
    firstHash = line.substr(line.find_first_of('\"') + 1, line.find_last_of('\t') - 2);

    getLastLine(stream, line);
    lastHash = line.substr(line.find_first_of('\"') + 1, line.find_last_of('\t') - 2);

    if (hash >= firstHash && hash <= lastHash)
    {
        return files[mid];
    }
    else if (hash < firstHash)
    {
        return binarySearchFile(files, start, mid - 1, hash);
    }
    else
    {
        return binarySearchFile(files, mid + 1, end, hash);
    }
}

std::filesystem::path searchFile(const std::filesystem::path& directory, const std::string& hash)
{
    std::vector<std::filesystem::path> files;

    for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{directory})
    {
        if ( dir_entry.is_directory() )
        {
            continue;
        }

        files.push_back( dir_entry.path() );
    }

    std::sort(files.begin(), files.end());

    return binarySearchFile(files, 0, files.size(), hash);
}

std::string binarySearchWord(std::fstream& stream, const std::vector<int>& linesIndexes, int start, int end,
                             const std::string& hash)
{
    if (start > end)
    {
        throw std::runtime_error("start > end");
    }

    int mid = (start + end) / 2;
    std::string line;

    stream.seekg(linesIndexes[mid], std::ios::beg);
    std::getline(stream, line);

    std::string curHash = line.substr(line.find_first_of('\"') + 1, line.find_last_of('\t') - 2);

    if (curHash == hash)
    {
        return line.substr(line.find_first_of('\t') + 2, line.find_last_of('\"') - (line.find_first_of('\t') + 2));
    }
    else if (curHash > hash)
    {
        return binarySearchWord(stream, linesIndexes, start, mid - 1, hash);
    }
    else
    {
        return binarySearchWord(stream, linesIndexes, mid + 1, end, hash);
    }
}

std::string searchWord(const std::filesystem::path& path, const std::string& hash)
{
    std::vector<int> linesIndexes;
    std::fstream stream;
    bool flag = true;
    char character;

    stream.open(path);

    if ( !stream.is_open() )
    {
        throw std::runtime_error("file not exist");
    }

    while ( !stream.eof() )
    {
        if (flag)
        {
            linesIndexes.push_back( stream.tellg() );
            flag = false;
        }

        character = stream.get();

        if (character == '\n')
        {
            flag = true;
        }
    }

    linesIndexes.pop_back();
    stream.clear();

    return binarySearchWord(stream, linesIndexes, 0, linesIndexes.size() - 1, hash);
}

int main()
{
    std::string path = "../passwords";
    std::string hash = "86ab5710b846338c8bd589b751767f8a";

    auto start = std::chrono::high_resolution_clock::now();

    std::string word = searchWord(searchFile(path, hash), hash);

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << word << std::endl;

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "seconds = " << duration.count() / double(1000) << std::endl;

    return 0;
}
