//
//  AppConfiguration.cpp
//  MenuGL
//
//  Created by Manuel Galindo on 8/02/23.
//

#include "AppConfiguration.hpp"

void AppConfiguration::setApiUrl(std::string url){
    this->apiUrl = url;
}

std::string AppConfiguration::getApiUrl(){
    return this->apiUrl;
}
