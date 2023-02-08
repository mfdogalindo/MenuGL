//
//  Home.cpp
//  MenuGL
//
//  Created by Manuel Galindo on 8/02/23.
//

#include "Home.hpp"

Home::Home()
{
    this->elementIndex = 0;
}

void Home::setTitle(String title)
{
    this->title = title;
}

String Home::getTitle()
{
    return this->title;
}

uint Home::addElement(ContentElement element)
{
    uint insertIndex = this->elementIndex;
    this->elementsMap.insert(std::pair<uint, ContentElement>(insertIndex, element));
    this->elementIndex++;
    return insertIndex;
}

uint8_t Home::removeElement(uint index)
{
    return this->elementsMap.erase(index);
}

ContentElement Home::getElement(uint index)
{
    return this->elementsMap[index];
}

std::map<uint, ContentElement>::iterator Home::findElement(uint index)
{
    return this->elementsMap.find(index);
}

uint Home::getElementsCount()
{
    return (uint)this->elementsMap.size();
}

void Home::addContainer(uint index, ContainerElement container)
{
    this->containersMap.insert(std::pair<uint, ContainerElement>(index, container));
}

String Home::toString()
{

    String descriptor;
    descriptor += String{"Title: "} + this->title + '\n';

    for (std::map<uint, ContainerElement>::iterator it = this->containersMap.begin(); it != this->containersMap.end(); ++it)
    {
        descriptor += "Container [" + it->second.id + "]: " + it->second.name + " - Has related content: ";
        descriptor += (it->second.hasRef) ? "yes\n" : "no\n";

        for (std::vector<uint>::iterator it2 = it->second.elementsIndex.begin(); it2 != it->second.elementsIndex.end(); ++it2)
        {
            ContentElement element = this->getElement(*it2);
            descriptor += "\tContent [" + element.name + "] - Is a Movie : ";
            descriptor += (element.isMovie) ? "yes\n" : "no\n";
        }
    }

    return descriptor;
}
