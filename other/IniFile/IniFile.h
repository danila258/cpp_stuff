#ifndef IniFile_H
#define IniFile_H

#include <string>
#include <map>
#include <vector>
#include <cassert>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <iostream>


class IniFile
{
public:
	IniFile(const std::string& path);
	
	void save() const;

    /**
     * Считывает из секции section
     * значение ключа key
     * Если не удалось считать - возвращает default value
     *
     * Определить для std::string, int, float, bool
     */
	template<typename T>
	T read(const std::string& section, const std::string& key, T defaultValue = T{}) const;

    /**
     * В ключ key из секции section
     * записывает значение value
     *
     * Определить для std::string, int, float, bool
     */
	template<typename T>
	void write(const std::string& section, const std::string& key, T value);

    /**
     * Проверяет, существует ли секция section
     */
    bool sectionExists(const std::string& section) const;

    /**
     * Проверяет, существует ли ключ key в секции section
     */
    bool keyExists(const std::string& section, const std::string& key) const;

    /**
     * Возвращает существующие секции
     */
    std::vector<std::string> sections() const;

    /**
     * Возвращает существующие ключи в секции section
     */
    std::vector<std::string> keys(const std::string& section) const;

private:
    std::string _path;
    std::map<std::string, std::map<std::string, std::string>> _data;

    std::vector<std::string> _alias = {"true", "True", "TRUE", "on", "On", "ON", "yes", "Yes", "YES", "y", "Y", "1"};
};


IniFile::IniFile(const std::string& path) : _path(path)
{
    std::fstream file;
    file.open(path);

    if ( !file.is_open() )
    {
        throw std::runtime_error("file not exist");
    }

    std::string line;
    std::string curKey;
    std::string subKey;
    std::string value;

    while ( getline(file, line) )
    {
        if ( line.empty() )
        {
            continue;
        }

        if (line.find('[') != std::string::npos)
        {
            curKey = line.substr(line.find_first_of('[') + 1, line.find_last_of(']') - line.find_first_of('[') - 1);
            _data[curKey];
            continue;
        }

        std::stringstream stream(line);

        if ( !getline(stream, subKey, '=') )
        {
            continue;
            //throw std::runtime_error("not = in line");
        }

        if ( !getline(stream, value) )
        {
            continue;
            //throw std::runtime_error("not value in line");
        }


        bool flag = false;
        std::string key;

        for (auto&& item : subKey)
        {
            if (item != ' ')
            {
                flag = true;
            }

            if (flag)
            {
                key.push_back(item);
            }
        }

        if ( !key.empty() && key[0] != ' ')
        {
            _data[curKey].insert( {key, value} );
        }
    }
}

void IniFile::save() const
{
    std::fstream file;
    file.open(_path, std::ios::out);

    if ( !file.is_open() )
    {
        throw std::runtime_error("can't write file");
    }

    for (auto&& item : _data)
    {
        file << '[' << item.first << ']' << std::endl;

        for (auto&& pair : item.second)
        {
            file << pair.first << '=' << pair.second << std::endl;
        }

        file << std::endl;
    }
}

template<typename T>
T IniFile::read(const std::string& section, const std::string& key, T defaultValue) const
{
    if ( !keyExists(section, key) )
    {
        return defaultValue;
    }

    T var;
    std::istringstream stream( _data.at(section).at(key) );
    stream >> var;

    return var;
}

template<>
bool IniFile::read(const std::string& section, const std::string& key, bool defaultValue) const
{
    if ( !keyExists(section, key) )
    {
        return defaultValue;
    }

    if (std::find(_alias.begin(), _alias.end(), _data.at(section).at(key)) != _alias.end())
    {
        return true;
    }

    return false;
}

template<>
std::string IniFile::read(const std::string& section, const std::string& key, std::string defaultValue) const
{
    if ( !keyExists(section, key) )
    {
        return defaultValue;
    }

    return _data.at(section).at(key);
}

template<typename T>
void IniFile::write(const std::string& section, const std::string& key, T value)
{
    _data[section][key] = std::to_string(value);
}

template<>
void IniFile::write(const std::string& section, const std::string& key, bool value)
{
    if (value)
    {
        _data[section][key] = "true";
    }
    else
    {
        _data[section][key] = "false";
    }
}

template<>
void IniFile::write(const std::string& section, const std::string& key, std::string value)
{
        _data[section][key] = value;
}

bool IniFile::sectionExists(const std::string& section) const
{
    if (_data.find(section) != _data.end())
    {
        return true;
    }

    return false;
}

bool IniFile::keyExists(const std::string& section, const std::string& key) const
{
    if (sectionExists(section) && _data.at(section).find(key) != _data.at(section).end())
    {
        return true;
    }

    return false;
}

std::vector<std::string> IniFile::sections() const
{
    std::vector<std::string> sections;

    for (auto&& item : _data)
    {
        sections.push_back(item.first);
    }

    return sections;
}

std::vector<std::string> IniFile::keys(const std::string& section) const
{
    std::vector<std::string> keys;

    if ( !sectionExists(section) )
    {
        return keys;
    }

    for (auto&& pair : _data.at(section))
    {
        keys.push_back(pair.first);
    }

    return keys;
}


/** config.ini - input
[general]
windowWidth=1080
windowHeight=720
fullscreen=Yes

[player]
x=100
y=200
name=John Doe
**/


/** config.ini - output
[general]
windowWidth=1080
windowHeight=720
fullscreen=Yes

[player]
x=100
y=200
name=Ivan Petrov Vasilevishcyhhsh
bool=true

[newSection]
value=137
**/


#endif  //IniFile_H