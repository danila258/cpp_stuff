#include "XmlDocument.h"

XmlDocument::XmlDocument(const std::string& path) : _path(path)
{}

void XmlDocument::load()
{
    std::ios_base::sync_with_stdio(false);
    std::ifstream file(_path);

    if ( !file.is_open() )
    {
        throw std::runtime_error("failed open file on the path: " + _path);
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();

    std::string buffer(size, ' ');

    file.seekg(0);
    file.read(&buffer[0], size);

    parse(buffer);
}

void XmlDocument::parse(const std::string& line)
{
    int lineNum = 1;

    bool tagStart = false;
    bool tagClose = false;
    bool tagTextStart = false;

    bool valueTextStart = false;

    std::stack<std::shared_ptr<XmlElement>> stack;
    std::string curValue;
    std::string curTag;

    _head = std::make_shared<XmlElement>(nullptr, "head");
    stack.push(_head);

    for (auto it = line.begin(); it != line.end(); ++it)
    {
        if (*it == '\n')
        {
            ++lineNum;
        }
        else if (*it == '<')
        {
            if (tagStart)
            {
                throw std::runtime_error("incorrect '<' in the line: " + std::to_string(lineNum));
            }

            tagStart = true;
            tagClose = false;
            tagTextStart = false;
            valueTextStart = false;
        }
        else if (*it == '>')
        {            
            if (tagClose)
            {
                if (stack.top()->getText() == curTag)
                {
                    auto cur = stack.top();
                    cur->addChild(curValue);
                    stack.pop();
                    auto arr = stack.top()->getChildren();
                    arr.emplace_back(cur);
                }
                else
                {
                    throw std::runtime_error("diffefent tags in line: " + std::to_string(lineNum));
                }
            }
            else
            {
                if ( !curValue.empty() )
                {
                    throw std::runtime_error("value without tag in line: " + std::to_string(lineNum));
                }

                if (*(it - 1) == '/')
                {
                    stack.top()->addChild(curTag)->addChild("");
                }
                else
                {
                    auto cur = stack.top()->addChild(curTag);
                    stack.push(cur);
                }
            }

            tagStart = false;
            tagTextStart = false;
            tagClose = false;

            curValue.clear();
            curTag.clear();
        }
        else if (*it == '/')
        {
            if (tagStart && tagTextStart && *(it + 1) != '>' || tagClose)
            {
                throw std::runtime_error("incorrect '/' in the line: " + std::to_string(lineNum));
            }

            if ( !tagStart )
            {
                curValue += *it;
                valueTextStart = true;
            }

            if (*(it + 1) != '>')
            {
                tagClose = true;
            }
        }
        else if (*it == ' ')
        {
            if (tagStart)
            {
                throw std::runtime_error("incorrect space after '<' in the line: " + std::to_string(lineNum));
            }

            if (valueTextStart)
            {
                curValue += *it;
            }
        }
        else if ( !std::isspace(*it) )
        {
            if (tagStart)
            {
                tagTextStart = true;
                curTag += *it;
            }
            else
            {
                valueTextStart = true;
                curValue += *it;
            }
        }

        if ( stack.empty() )
        {
            throw std::runtime_error("wrong tag in line: " + std::to_string(lineNum));
        }
    }
}

std::shared_ptr<XmlElement> XmlDocument::getHead()
{
    return _head;
}