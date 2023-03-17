#include "XmlElement.h"


XmlElement::XmlElement(const std::shared_ptr<XmlElement>& parent, const std::string& text) noexcept
    : _parent(parent), _text(text)
{}

std::string& XmlElement::getText()
{
    return _text;
}

std::shared_ptr<XmlElement> XmlElement::getParent()
{
    return _parent.lock();
}

std::shared_ptr<XmlElement> XmlElement::getFirstChild(const std::string& text)
{
    auto it = std::find_if(_children.begin(), _children.end(), [&text](std::shared_ptr<XmlElement>& a){
        return a->getText() == text;
    });

    if (it == _children.end())
    {
        throw std::runtime_error("can't find child with text: " + text);
    }

    return *it;
}

std::vector<std::shared_ptr<XmlElement>>& XmlElement::getChildren()
{
    return _children;
}

std::shared_ptr<XmlElement> XmlElement::addChild(const std::string& text)
{
    auto child = std::make_shared<XmlElement>(shared_from_this(), text);
    _children.emplace_back(child);

    return child;
}
