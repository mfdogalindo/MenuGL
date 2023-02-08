//
//  Home.hpp
//  MenuGL
//
//  Created by Manuel Galindo on 8/02/23.
//

#ifndef Home_hpp
#define Home_hpp

#include <iostream>
#include <vector>
#include <map>

using String = std::string;

typedef struct{
    uint index;
    String contentId;
    String collectionId;
    String name;
    String image;
    String url;
    bool isMovie;
    bool isCollection;
} ContentElement;

typedef struct{
    String id;
    bool hasRef;
    String name;
    std::vector<uint> elementsIndex;
} ContainerElement;

class Home{

    private:
        String title;
        uint elementIndex;
        std::map<uint, ContentElement> elementsMap;
        std::map<uint, ContainerElement> containersMap;

    public:
        Home();
        void setTitle(String title);
        String getTitle();
    
        uint addElement(ContentElement element);
        uint8_t removeElement(uint index);
        ContentElement getElement(uint index);
        std::map<uint, ContentElement>::iterator findElement(uint index);
        uint getElementsCount();
 
        void addContainer(uint index, ContainerElement container);
    
        String toString();

};

#endif /* Home_hpp */
