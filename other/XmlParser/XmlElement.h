#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>


class XmlElement : public std::enable_shared_from_this<XmlElement>
{
public:
    XmlElement(const std::shared_ptr<XmlElement>& parent, const std::string& text) noexcept;

    std::string& getText();
    std::shared_ptr<XmlElement> getParent();
    std::shared_ptr<XmlElement> getFirstChild(const std::string& text);
    std::vector<std::shared_ptr<XmlElement>>& getChildren();

    std::shared_ptr<XmlElement> addChild(const std::string& text);

private:
    std::weak_ptr<XmlElement> _parent;
    std::string _text;
    std::vector<std::shared_ptr<XmlElement>> _children;
};

#endif // XMLELEMENT_H
