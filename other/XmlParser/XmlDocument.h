#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H

#include "XmlElement.h"

#include <fstream>


class XmlDocument
{
public:
    explicit XmlDocument(const std::string& path);

    void load();
    std::shared_ptr<XmlElement> getHead();

private:
    std::string _path;
    std::shared_ptr<XmlElement> _head;

    void parse(const std::string& line);
};

#endif // XMLDOCUMENT_H
