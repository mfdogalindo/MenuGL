//
//  ContentManager.cpp
//  MenuGL
//
//  Created by Manuel Galindo on 8/02/23.
//

#include "ContentManager.hpp"
#include <stdio.h>
#include <thread>


ContentManager::ContentManager(AppConfiguration* appConfig){
    this->apiConfig = appConfig;
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

ContainerVector setEmbeddedItems(Home* home, JSON items){
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
        element.imageBytes = APIClient("").getImage(element.imageUrl);
        element.hasImage = element.imageBytes.size() > 0;
        element.url = "www.url.com";
        
        uint indexNewElement = home->addElement(element);
        
        vector.push_back(indexNewElement);
    }
    return vector;
}

ContainerVector getItemsFromAPI(Home* home, String url, String refId){
    ContainerVector vector;
    JSON refData = APIClient(url).getSet(refId);
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
    return setEmbeddedItems(home, items);
}

void getContainers(Home* home, String url, int containerIndex, JSON jContainers ){
    ContainerElement container;
    container.hasRef = jContainers[containerIndex]["set"]["refId"].is_string();

    container.name = jContainers[containerIndex]["set"]["text"]["title"]["full"]["set"]["default"]["content"].get<String>();
    
    if(container.hasRef){
        container.id = jContainers[containerIndex]["set"]["refId"].get<String>();
        container.elementsIndex = getItemsFromAPI(home, url, container.id);
    }
    else{
        container.id = jContainers[containerIndex]["set"]["setId"].get<String>();
        JSON jItems = jContainers[containerIndex]["set"]["items"].get<std::vector<JSON>>();
        container.elementsIndex = setEmbeddedItems(home, jItems);
    }
    
    home->addContainer(containerIndex, container);
}


void ContentManager::getHome(){
    std::cout << "Get home data... wait please\n";
    JSON homeJson = APIClient(this->apiConfig->getApiUrl()).getHome();
    JSON containers = homeJson["data"]["StandardCollection"]["containers"].get<std::vector<JSON>>();
    
    std::vector<std::thread> threads;
    
    for(uint conPos = 0; conPos < containers.size(); conPos++){
        threads.emplace_back(std::thread(getContainers,&this->home, this->apiConfig->getApiUrl(), conPos, containers));
    }
    
    for (auto& th : threads)
        th.join();
    
    this->home.setTitle("MenuFlix");
    
    std::cout <<  this->home.toString() << '\n';
    
}
