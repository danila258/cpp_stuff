#include <iostream>
#include <vector>
#include <fstream>

struct Bracket
{
    char symbol;
    int pos;
    bool checked;
};

int isBalanced(const std::string line)
{
    std::vector<Bracket*> tokens;
    int pos = 0;

    for (auto&& item : line)
    {
        ++pos;

        if (item == '(' || item == ')' || item == '[' || item == ']' || item == '{' || item == '}')
        {
            tokens.push_back(new Bracket{item, pos, false});
        }
    }

    for (std::vector<Bracket*>::iterator curElem = tokens.begin(); curElem != tokens.end(); ++curElem)
    {
        char mirrorItem;
        int countClose = 0;
        int countOpen = 0;

        if ( (*curElem)->symbol == '(' )
        {
            mirrorItem = ')';
        }
        else if ( (*curElem)->symbol == '[' )
        {
            mirrorItem = ']';
        }
        else if ( (*curElem)->symbol == '{' )
        {
            mirrorItem = '}';
        }
        else
        {
            continue;
        }

        for (std::vector<Bracket*>::iterator pairElem = curElem; pairElem != tokens.end(); ++pairElem)
        {
            if ( (*pairElem)->symbol == '(' || (*pairElem)->symbol == '[' || (*pairElem)->symbol == '{' )
            {
                ++countOpen;
            }

            if ( (*pairElem)->symbol == ')' || (*pairElem)->symbol == ']' || (*pairElem)->symbol == '}' )
            {
                ++countClose;
            }

            if ( (*pairElem)->symbol == mirrorItem && !(*pairElem)->checked)
            {
                if (countClose != countOpen)
                {
                    continue;
                }

                (*pairElem)->checked = true;
                (*curElem)->checked = true;

                break;
            }
        }
    }

    for (std::vector<Bracket*>::iterator curElem = tokens.begin(); curElem != tokens.end(); ++curElem)
    {
        if ( !(*curElem)->checked )
        {
            if ( (*curElem)->symbol == '(' || (*curElem)->symbol == '[' || (*curElem)->symbol == '{' )
            {
                for (std::vector<Bracket*>::iterator pairElem = curElem; pairElem != tokens.end(); ++pairElem)
                {
                    if ( (*pairElem)->symbol == ')' || (*pairElem)->symbol == '}' || (*pairElem)->symbol == '{' )
                    {
                        return (*pairElem)->pos;
                    }
                }

                ++curElem;

                if (curElem != tokens.end())
                {
                    return (*curElem)->pos;
                }

                --curElem;

                return (*curElem)->pos;
            }
            else
            {
                return (*curElem)->pos;
            }
        }
    }

    return 0;
}

int main() {
    std::string line;
    std::fstream stream;

    stream.open("../input.txt", std::ios::in);

    if ( stream.is_open() )
    {
        getline(stream, line);
    }

    int result = isBalanced(line);

    if (result == 0)
    {
        std::cout << "Success";
    }
    else
    {
        std::cout << result;
    }

    return 0;
}