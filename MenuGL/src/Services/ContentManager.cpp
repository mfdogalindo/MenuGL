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

ByteVector ContentManager::getImageBytes(String url){
    return this->apiClient->getImage(url);
}

String getImageURL(JSON input){
    String urlImage = "no_image";
    
    if(input["series"]["default"]["url"].is_string()){
        urlImage = input["series"]["default"]["url"].get<String>();
    }
    else if(input["program"]["default"]["url"].is_string()){
        urlImage = input["program"]["default"]["url"].get<String>();
    }
    else if(input["default"]["default"]["url"].is_string()){
        urlImage = input["default"]["default"]["url"].get<String>();
    }
    return urlImage;
}

ContainerVector ContentManager::setEmbeddedItems(JSON items){
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

        element.imageUrl = getImageURL(items[itemPos]["image"]["tile"]["0.71"]);
        element.imageBytes = getImageBytes(element.imageUrl);
        element.hasImage = element.imageBytes.size() > 0;
        element.url = "www.url.com";
        
        uint indexNewElement = this->home.addElement(element);
        
        vector.push_back(indexNewElement);
    }
    return vector;
}

ContainerVector ContentManager::getItemsFromAPI(String refId){
    ContainerVector vector;
    JSON refData = this->apiClient->getSet(refId);
    JSON items;
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
    std::cout << "Get home data... wait please\n";
    JSON homeJson = this->apiClient->getHome();
    JSON containers = homeJson["data"]["StandardCollection"]["containers"].get<std::vector<JSON>>();
    
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
            JSON jItems = containers[conPos]["set"]["items"].get<std::vector<JSON>>();
            container.elementsIndex = this->setEmbeddedItems(jItems);
        }
        
        this->home.addContainer(conPos, container);
    }
    
    
    this->home.setTitle("MenuFlix");

    
    std::cout <<  this->home.toString() << '\n';
    
}
