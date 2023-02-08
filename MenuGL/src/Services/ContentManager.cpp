//
//  ContentManager.cpp
//  MenuGL
//
//  Created by Manuel Galindo on 8/02/23.
//

#include "ContentManager.hpp"
#include <stdio.h>


ContentManager::ContentManager(AppConfiguration* appConfig){
    this->apiConfig = appConfig;
    this->apiClient = new APIClient(this->apiConfig->getApiUrl());
}

ContainerVector ContentManager::setEmbeddedItems(json items){
    ContainerVector vector;
    for(uint itemPos = 0; itemPos < items.size(); itemPos++){
        ContentElement element;
        element.isMovie = items[itemPos]["type"].get<String>().compare("DmcVideo") == 0;
        if(items[itemPos]["contentId"].is_string()){
            element.contentId = items[itemPos]["contentId"].get<String>();
            String movieNamePath = element.isMovie ? "program" : "series";
            element.name = items[itemPos]["text"]["title"]["full"][movieNamePath]["default"]["content"].get<String>();
        }
        element.isCollection =items[itemPos]["collectionId"].is_string();
        if(element.isCollection){
            element.collectionId = items[itemPos]["collectionId"].get<String>();
            element.name = items[itemPos]["text"]["title"]["full"]["collection"]["default"]["content"].get<String>();
        }

        element.image = "video";
        element.url = "http://www.google.com";
        
        uint indexNewElement = this->home.addElement(element);
        
        vector.push_back(indexNewElement);
    }
    return vector;
}

ContainerVector ContentManager::getItemsFromAPI(String refId){
    ContainerVector vector;
    json refData = this->apiClient->getSet(refId);
    json items;
    if(refData["data"]["CuratedSet"]["items"].size()){
        items = refData["data"]["CuratedSet"]["items"];
    }
    else if(refData["data"]["PersonalizedCuratedSet"]["items"].size()){
        items = refData["data"]["PersonalizedCuratedSet"]["items"];
    }
    else if(refData["data"]["TrendingSet"]["items"].size()){
        items = refData["data"]["TrendingSet"]["items"];
    }
    return this->setEmbeddedItems(items);
}


void ContentManager::getHome(){
    json homeJson = this->apiClient->getHome();
    json containers = homeJson["data"]["StandardCollection"]["containers"].get<std::vector<json>>();
    
    for(uint conPos = 0; conPos < containers.size(); conPos++){
        
        ContainerElement container;
        container.hasRef = containers[conPos]["set"]["refId"].is_string();

        container.name = containers[conPos]["set"]["text"]["title"]["full"]["set"]["default"]["content"].get<String>();
        
        if(container.hasRef){
            container.id = containers[conPos]["set"]["refId"].get<String>();
            container.elementsIndex = this->getItemsFromAPI(container.id);
        }
        else{
            container.id = containers[conPos]["set"]["setId"].get<String>();
            json jItems = containers[conPos]["set"]["items"].get<std::vector<json>>();
            container.elementsIndex = this->setEmbeddedItems(jItems);
        }
        
        this->home.addContainer(conPos, container);
    }
    
    
    this->home.setTitle("MenuFlix");

    
    std::cout <<  this->home.toString() << '\n';
    
}
